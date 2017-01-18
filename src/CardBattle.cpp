// Sample_04_Cardgame_Client_cpp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stormancer.h"
#include <iostream>
#include "Online/AuthenticationPlugin.h"
#include "Online/MatchmakingPlugin.h"
#include "Online/TurnByTurnPlugin.h"
#include "Online/GameSession.h"
#include <time.h> 
#include <vector>
#include "CardBattle/GameManager.h"

static std::string name;
static unsigned int globalSeed;

enum class TransactionCommand : int
{
	Start,
	Connect,
	StartTurn,
	AttackCard,
	PlayCard,
	Wait,
	EndTurn,
	Disconnect,
	Victory,
};

std::string strCmd(TransactionCommand com)
{
	return std::to_string((int)com);
}

int ApplyTransaction(Stormancer::UpdateDto t, int& gameState, GameManager* gameManager)
{
	TransactionCommand command = (TransactionCommand)std::atoi(t.cmd.c_str());
	if (t.cmd == "Start")command = TransactionCommand::Start;
	std::cout << std::endl << "COMMAND: " << t.cmd << std::endl;
	switch (command)
	{
	case TransactionCommand::Start:
		gameManager->CreateGame();
		gameManager->setSeed(globalSeed);
		std::cout << std::endl << "Starting with seed " << globalSeed << std::endl;
		break;
	case TransactionCommand::StartTurn:
		gameManager->startTurn();
		break;
	case TransactionCommand::AttackCard:
		gameManager->playBattle(t.json_args()[L"atk"].as_integer(), t.json_args()[L"def"].as_integer());
		break;
	case TransactionCommand::PlayCard:
		gameManager->playCard(t.json_args()[L"choice"].as_integer());
		break;
	case TransactionCommand::Wait:
		break;
	case TransactionCommand::EndTurn:
		gameManager->endPhase();
		break;
	case TransactionCommand::Connect:
		gameManager->AddPlayer(t.json_args()[L"pseudo"].as_integer());
		break;
	case TransactionCommand::Disconnect:
		
		break;
	case TransactionCommand::Victory:

		break;
	default:
		break;
	}

	return gameState;
}

int main(int argc, char *argv[])
{
	GameManager* gameManager = new GameManager();
	std::cout << "Enter your name :" << std::endl;
	std::cin >> name;
	
	std::string login = name;

	std::hash<std::string> hash_fn;
	size_t str_hash = hash_fn(login);

	#pragma region Connect

	if (argc >= 2)
	{
		login = std::string(argv[1]);
	}
	//Create network client
	auto config = Stormancer::Configuration::create("http://api.stormancer.com", "ad912dff-cec9-0fb6-78f8-652d4c093508", "sample-04-cardgame");
	config->addPlugin(new Stormancer::AuthenticationPlugin()); //Adds Authentication
	config->addPlugin(new Stormancer::MatchmakingPlugin()); //Adds matchmaking & gamesession APIs
	config->addPlugin(new Stormancer::TurnByTurnPlugin());

	auto client = Stormancer::Client::createClient(config);

	//Authenticate using steam (with stub enabled)
	auto auth = client->dependencyResolver()->resolve<Stormancer::IAuthenticationService>();
	std::cout << "Authenticating as '" << login << "'...";
	auto scene = auth->steamLogin(login).get();
	std::cout << "DONE" << std::endl;

	//Connect to the matchmaking scene
	auto matchmakingScene = auth->getPrivateScene("matchmaking-fast").get();
	matchmakingScene.lock()->connect().get();

	auto matchmaking = matchmakingScene.lock()->dependencyResolver()->resolve<Stormancer::MatchmakingService>();

	///Configure a task_completion_event which will fire when a game is found.
	auto tce = pplx::task_completion_event<Stormancer::MatchmakingResponse>{};
	matchmaking->onMatchFound([tce](Stormancer::MatchmakingResponse response)
	{

		tce.set(response);

	});

	matchmaking->findMatch("matchmaking-sample");

	std::cout << "waiting for game...";
	Stormancer::MatchmakingResponse mmResponse = pplx::create_task(tce).get();
	std::cout << "FOUND" << std::endl;

	Stormancer::ScenePtr game_scene = auth->getPrivateScene(mmResponse.gameId).get();
	int gameState = 0;
	auto transactionBroker = game_scene.lock()->dependencyResolver()->resolve<Stormancer::TurnByTurnService>();
	bool running = true;
	transactionBroker->onDesyncErrorCallback([&running](std::string error)
	{
		std::cout << "A desynchronization error occured. Details : " << error << std::endl;
		running = false;
	});
	transactionBroker->onUpdateGameCallback([&gameState, &gameManager](Stormancer::UpdateDto update)
	{
		//****
		// Update game state (display life board hand etc...
		//****


		auto newHash = ApplyTransaction(update, gameState, gameManager);
		//std::cout << "game state updated : " << gameState << std::endl;
		//std::cout << "Random Test: " << rand() % 100 << std::endl;
		return newHash; //Returns the new hash to the server for validation
	});
	transactionBroker->onReplayTLog([&gameState,&running, &gameManager](std::vector<Stormancer::TransactionLogItem> transactions)
	{
		std::cout << "Replay existing transaction log...";
		for (auto t : transactions)
		{
			auto newHash = ApplyTransaction(t.transactionCommand, gameState, gameManager);
			if (t.hashAvailable && t.resultHash != newHash)
			{
				std::cout << "Desynchronization while playing Transaction log. Expected "<<t.resultHash << " obtained "<< newHash << std::endl;
				std::string v;
				std::cin >> v;
				running = false;
				break;
			}
		}

	});


	std::cout << "Connecting to game...";
	auto gameSession = game_scene.lock()->dependencyResolver()->resolve<Stormancer::GameSessionService>();

	gameSession->connect().get();//Connect to the game session

	gameSession->ready();//Inform the server we are ready to play
	gameSession->waitServerReady().get();
	std::cout << "CONNECTED" << std::endl;
#pragma endregion

	#pragma region Game
	
	try
	{
		auto json = web::json::value();
		json[L"pseudo"] = str_hash;
		auto t = transactionBroker->submitTransaction(auth->userId(), strCmd(TransactionCommand::Connect), json);
		t.get();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}

	while (gameManager->player1 == nullptr && gameManager->player2 == nullptr)
	{

	}

	int n;
	while (running)
	{
		gameManager->setupTurn(str_hash);

		try
		{
			web::json::value json;
			auto t = transactionBroker->submitTransaction(auth->userId(), strCmd(TransactionCommand::StartTurn), json);
			t.get();
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what();
		}

		do
		{
			web::json::value json;
			gameManager->mainPhase();
			json[L"choice"] = gameManager->choiceMP();

			try
			{
				auto t = transactionBroker->submitTransaction(auth->userId(), strCmd(TransactionCommand::PlayCard), json);
				t.get();
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what();
			}
		} while (gameManager->playingCard);
		do
		{
			web::json::value json;
			gameManager->battlePhase();
			std::vector<int> result = gameManager->choiceBP();

			json[L"atk"] = result[0];
			json[L"def"] = result[1];

			try
			{
				auto t = transactionBroker->submitTransaction(auth->userId(), strCmd(TransactionCommand::AttackCard), json);
				t.get();
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what();
			}
		} while (gameManager->chooseToAttack);

		try
		{
			web::json::value json;
			auto t = transactionBroker->submitTransaction(auth->userId(), strCmd(TransactionCommand::EndTurn), json);
			t.get();
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what();
		}
		
		running = gameManager->endOfGame;
	}

	if(gameManager->winnerIsYou)
		std::cout << "YOU WIN" << std::endl;
	else
		std::cout << "YOU LOSE" << std::endl;

	system("Pause");
	#pragma endregion

	std::cout << "disconnecting...";
	client->disconnect().get();
	std::cout << "DONE" << std::endl;
	return 0;
}



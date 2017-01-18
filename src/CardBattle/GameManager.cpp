#include "stdafx.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager()
{
	firstPlayerSet = false;
}


GameManager::~GameManager()
{
}


void GameManager::CreateGame()
{
	firstPlayerTurn = true;
	chooseToAttack = false;
	winnerIsYou = false;

	nbCardToDrawEachTurn = 2;
}

void GameManager::setSeed(unsigned int seed)
{
	currentSeed = seed;
}

void GameManager::setupTurn(int id)
{
	endOfGame = false;
	playingCard = false;
	chooseToAttack = false;

	playing = player1;
	enemy = player2;

	if (!firstPlayerTurn)
	{
		playing = player2;
		enemy = player1;
	}

	isYou = false;
	
	if (id == playing.name)
		isYou = true;
}

void GameManager::AddPlayer(int id)
{
	if (firstPlayerSet)
	{
		std::cout << "Player2: " << id << std::endl;
		player2 = Player(id, 20, currentSeed);
	}
	else
	{
		std::cout << "Player1: " << id << std::endl;
		player1 = Player(id, 20, currentSeed);
		firstPlayerSet = true;
	}
	
}

void GameManager::startTurn()
{
	playing.beginTurn(nbCardToDrawEachTurn);
}

void GameManager::mainPhase()
{
	if (!playing.canPlaySpell)
	{
		playingCard = false;
		return;
	}

	playingCard = true;

	if (isYou)
		cout << "----- ENEMY -----" << endl;

	enemy.displayBoard();

	playing.displayBoard();

	if (isYou)
		playing.displayHand();
}

int GameManager::choiceMP()
{
	if (!playingCard)
	{
		return -2;
	}

	if (!isYou)
		return -2;

	int choice = 0;

	cout << "Do you want to: " << endl;
	cout << '/t' << "0 - Play Card" << endl;
	cout << '/t' << "1 - Attack" << endl;
	cin >> choice;

	if (choice == 0)
	{
		cout << "Which Card? (Enter index of card)" << endl;
		cin >> choice;
		return choice;
	}

	if (choice == 1)
	{

	}
	
	return -2;
}

void GameManager::playCard(int indexCard)
{
	if (indexCard == -2)
	{
		chooseToAttack = true;
		playingCard = false;
	}
	else
	{
		playing.castSpell(indexCard);
	}
}

void GameManager::battlePhase()
{

	if (endOfGame)
	{
		chooseToAttack = false;
		return;
	}

	if (isYou)
		cout << "----- ENEMY -----" << endl;

	enemy.displayBoard();

	if (isYou)
		cout << -1 << " - EnemyPlayer";

	playing.displayBoard();
}

vector<int> GameManager::choiceBP()
{
	vector<int> _result = vector<int>();
	_result.push_back(-2);
	_result.push_back(-2);

	if (endOfGame)
	{
		chooseToAttack = false;
		return _result;
	}

	if (!chooseToAttack)
	{
		return _result;
	}

	if (!isYou)
		return _result;

	int choice = 0;
	int choiceAtk = -2;
	int choiceDef = -2;

	cout << "Do you want to: " << endl;
	cout << '/t' << "0 - Continue to Attack" << endl;
	cout << '/t' << "1 - Cease to Attack" << endl;
	cin >> choice;

	if (choice == 0)
	{
		cout << "Which Card must Attack? (Enter index of card)" << endl;
		cin >> choiceAtk;

		cout << "Which Card do you want to Attack?" << endl;
		cin >> choiceDef;
	}

	if (choice == 1)
	{
	}

	_result[0] = choiceAtk;
	_result[1] = choiceDef;

	return _result;
}

void GameManager::playBattle(int _atk, int _def)
{
	if (_atk == -2 && _def == -2)
	{
		chooseToAttack = false;
		return;
	}

	Card* _atkCard = playing.attackWithCreature(_atk);

	if (_atkCard == nullptr)
		return;

	if (_def != -1)
	{
		Card* _defCard = enemy.attackWithCreature(_def);

		if (_defCard == nullptr)
			return;

		BattleOutcome result = Battle(_atkCard, _defCard);

		switch (result)
		{
		case NODEATH:
			break;
		case ATKDEATH:
			playing.creatureDie(_atk);
			break;
		case DEFDEATH:
			enemy.creatureDie(_def);
			break;
		case BOTHDEATH:
			playing.creatureDie(_atk);
			enemy.creatureDie(_def);
			break;
		default:
			break;
		}
	}
	else
	{
		enemy.playerTakeDamage(_atkCard->getAtk());
		EndGame();
	}
}

void GameManager::endPhase()
{
	playing.endTurn();

	cout << "END OF ";

	if (isYou)
		cout << "YOUR ";
	else
		cout << "ENEMY ";

	cout << "TURN" << endl;

	firstPlayerTurn = !firstPlayerTurn;
}


BattleOutcome GameManager::Battle(Card * _atk, Card * _def)
{
	BattleOutcome result = NODEATH;

	if (_atk->getAtk() >= _def->getDef())
	{
		if (_atk->getDef() <= _def->getAtk())
		{
			result = BOTHDEATH;
		}
		else
		{
			result = DEFDEATH;
		}
	}
	else
	{
		if (_atk->getDef() <= _def->getAtk())
		{
			result = ATKDEATH;
		}
	}

	return result;
}

void GameManager::EndGame()
{
	endOfGame =  enemy.isDead;
	winnerIsYou = true;
}



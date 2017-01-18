#include "stdafx.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}


void GameManager::CreateGame(Player p1, Player p2)
{
	player1 = p1;
	player2 = p2;

	firstPlayerTurn = true;
	chooseToAttack = false;

	nbCardToDrawEachTurn = 2;
}

void GameManager::setSeed(unsigned int seed)
{
	currentSeed = seed;
}

void GameManager::turn()
{
	Player _pToPlay = player1;
	Player _enemy = player2;

	if (!firstPlayerTurn)
	{
		_pToPlay = player2;
		_enemy = player1;
	}

	isYou = false;
	// check it's you the player

	startTurn(_pToPlay);
	mainPhase(_pToPlay, _enemy);
	battlePhase(_pToPlay, _enemy);

	endPhase(_pToPlay);
}

void GameManager::startTurn(Player p)
{
	p.beginTurn(nbCardToDrawEachTurn);
}

void GameManager::mainPhase(Player p, Player _enemy)
{
	while (p.canPlaySpell && !chooseToAttack)
	{
		if (isYou)
			cout << "----- ENEMY -----" << endl;

		_enemy.displayBoard();

		p.displayBoard();
		p.displayHand();

		choiceMP(p);
	}
}

void GameManager::choiceMP(Player p)
{
	if (!isYou)
		return;

	int choice = 0;

	cout << "Do you want to: " << endl;
	cout << '/t' << "0 - Play Card" << endl;
	cout << '/t' << "1 - Attack" << endl;
	cin >> choice;

	if (choice == 0)
	{
		cout << "Which Card? (Enter index of card)" << endl;
		cin >> choice;
		p.castSpell(choice);
	}

	if (choice == 1)
	{
		chooseToAttack = true;
	}
	
}

void GameManager::battlePhase(Player p, Player _enemy)
{
	while (chooseToAttack)
	{
		if (isYou)
			cout << "----- ENEMY -----" << endl;

		_enemy.displayBoard();

		if (isYou)
			cout << -1 << " - EnemyPlayer";

		p.displayBoard();

		choiceBP(p, _enemy);
	}
}

void GameManager::choiceBP(Player p, Player _enemy)
{
	if (!isYou)
		return;

	int choice = 0;
	int choiceAtk = 0;
	int choiceDef = 0;

	cout << "Do you want to: " << endl;
	cout << '/t' << "0 - Continue to Attack" << endl;
	cout << '/t' << "1 - Cease to Attack" << endl;
	cin >> choice;

	if (choice == 0)
	{
		cout << "Which Card must Attack? (Enter index of card)" << endl;
		cin >> choiceAtk;
		Card* _atk = p.attackWithCreature(choiceAtk);

		if (_atk == nullptr)
			return;

		cout << "Which Card do you want to Attack?" << endl;
		cin >> choiceDef;

		if (choiceDef != -1)
		{
			Card* _def = _enemy.attackWithCreature(choiceDef);

			if (_def == nullptr)
				return;

			BattleOutcome result = Battle(_atk, _def);

			switch (result)
			{
			case NODEATH:
				break;
			case ATKDEATH:
				p.creatureDie(choiceAtk);
				break;
			case DEFDEATH:
				_enemy.creatureDie(choiceDef);
				break;
			case BOTHDEATH:
				p.creatureDie(choiceAtk);
				_enemy.creatureDie(choiceDef);
				break;
			default:
				break;
			}
		}
		else
		{
			_enemy.playerTakeDamage(_atk->getAtk());

			if (_enemy.isDead)
				EndGame();
		}

	}

	if (choice == 1)
	{
		chooseToAttack = false;
	}

}

void GameManager::endPhase(Player p)
{
	p.endTurn();

	cout << "END OF ";

	if (isYou)
		cout << "YOUR ";
	else
		cout << "ENEMY ";

	cout << "TURN" << endl;
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

}



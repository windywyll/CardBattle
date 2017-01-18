#include "stdafx.h"
#include "GameManager.h"


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

	
}

void GameManager::setSeed(unsigned int seed)
{
	currentSeed = seed;
}

void GameManager::turn()
{
	Player _pToPlay = player1;
}

void GameManager::drawCard(Player p)
{
}

void GameManager::mainPhase(Player p)
{
}

void GameManager::battlePhase(Player p)
{
}

void GameManager::endPhase(Player p)
{
}



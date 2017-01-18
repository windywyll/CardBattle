#pragma once
#include "Player.h"

class GameManager
{
public:
	int currentSeed;
	GameManager();
	~GameManager();

	void CreateGame(Player p1, Player p2);
	void setSeed(unsigned int seed);

};


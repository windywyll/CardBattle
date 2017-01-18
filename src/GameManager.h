#pragma once
#include "CardBattle/Player.h"

class GameManager
{
public:
	int currentSeed;
	bool firstPlayerTurn;
	GameManager();
	~GameManager();

	void CreateGame(Player p1, Player p2);
	void setSeed(unsigned int seed);
	void turn();
	
	void drawCard(Player p);
	void mainPhase(Player p);
	void battlePhase(Player p);
	void endPhase(Player p);

private:
	Player player1, player2;
};


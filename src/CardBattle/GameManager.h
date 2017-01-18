#pragma once
#include "Player.h"

enum BattleOutcome
{
	NODEATH,
	ATKDEATH,
	DEFDEATH,
	BOTHDEATH
};

class GameManager
{
public:
	int currentSeed;
	bool firstPlayerTurn, chooseToAttack, isYou;
	GameManager();
	~GameManager();

	void CreateGame(Player p1, Player p2);
	void setSeed(unsigned int seed);
	void turn();
	
	void startTurn(Player p);
	void mainPhase(Player p, Player _enemy);
	void choiceMP(Player p);
	void battlePhase(Player p, Player _enemy);
	void choiceBP(Player p, Player _enemy);
	void endPhase(Player p);

	BattleOutcome Battle(Card* _atk, Card* _def);

	void EndGame();

private:
	Player player1, player2;
	int nbCardToDrawEachTurn;
};


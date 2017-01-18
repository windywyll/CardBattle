#pragma once
#include "Player.h"
#include <vector>

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
	bool firstPlayerTurn, playingCard, chooseToAttack, isYou, firstPlayerSet, endOfGame, winnerIsYou;
	GameManager();
	~GameManager();

	void CreateGame();
	void setSeed(unsigned int seed);
	void setupTurn(int id);
	void AddPlayer(int id);

	void startTurn();
	void mainPhase();
	int choiceMP();
	void playCard(int indexCard);
	void battlePhase();
	std::vector<int> choiceBP();
	void playBattle(int _atk, int _def);
	void endPhase();

	BattleOutcome Battle(Card* _atk, Card* _def);

	void EndGame();

	Player* player1, *player2;
	Player* playing, *enemy;
	int nbCardToDrawEachTurn;
};


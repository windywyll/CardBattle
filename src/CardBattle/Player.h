#pragma once
#include "Hand.h"
#include "Deck.h"
#include "Board.h"
#include "Cemetery.h"

class Player
{
public:
	int name;
	int health;
	bool canPlaySpell, isDead;

	Player() {};
	Player(int n, int l, unsigned int seed);
	~Player();

	void draw(int _nbCardToDraw);
	void castSpell(int indexCard);

	void playerTakeDamage(int _damage);

	Card* attackWithCreature(int indexCard);
	void creatureDie(int indexCard);

	void beginTurn(int _nbCardToDraw);
	void endTurn();

	void displayHand();
	void displayBoard();

private:
	Hand* playerHand;
	Deck* playerDeck;
	Board* playerBoard;
	Cemetery* playerCemetery;

	int nbSpellMax, nbSpellPlayed;
};
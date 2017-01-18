#pragma once
#include "Hand.h"
#include "Deck.h"
#include "Board.h"

class Player
{
public:
	std::string name;
	int health;
	bool canPlaySpell;
	Player(std::string n, int l);
	Player();
	~Player();

	void CreatePlayer();

	void draw(int _nbCardToDraw);
	void castSpell(int indexCard);

	void displayHand();
	void displayBoard();

private:
	Hand playerHand;
	Deck playerDeck;
	Board playerBoard;

	int nbSpellMax;
};
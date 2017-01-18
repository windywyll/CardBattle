#pragma once

#include <vector>
#include "Card.h"

class Board
{
public:
	Board();
	~Board();

	void displayBoard();
	void castCard(Card* _card);

	Card* creatureAttack(int indexCard);
	Card* creatureDies(int indexCard);

	void untapBoard();

private:
	int maxCreatureOnBoard;
	std::vector<Card*> cardList;
};


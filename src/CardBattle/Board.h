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

private:
	int maxCreatureOnBoard;
	std::vector<Card*> cardList;
};


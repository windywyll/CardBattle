#pragma once

#include <vector>
#include "Card.h"

class Board
{
public:
	Board();
	~Board();

private:
	int maxCreatureOnBoard;
	std::vector<Card*> cardList;
};


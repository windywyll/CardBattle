#pragma once
#include <vector>
#include "Card.h"

class Hand
{
public:
	Hand();
	~Hand();

private:
	std::vector<Card> cardsList;
};


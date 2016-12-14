#pragma once

#include <vector>
#include <stdlib.h>
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();

	Card* getTopCard();

private:
	int nbMaxCard, pointsToDistributeByCardMin, pointsToDistributeByCardMax;
	std::vector<Card*> cardList;

	void fillDeck();
	Card* createCard();
};


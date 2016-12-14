#pragma once
#include <vector>
#include "Card.h"

class Hand
{
public:
	Hand();
	Hand(Card* _hand, int _sizeInitial);
	~Hand();

	void drawCard(Card* _newCard);
	void discardCard();

private:
	std::vector<Card*> cardList;
	int nbMaxCardInHand;
};


#pragma once
#include <vector>
#include "Card.h"

class Hand
{
public:
	Hand();
	Hand(Card* _hand, int _sizeInitial);
	~Hand();

	bool isFull;

	void drawCard(Card* _newCard);
	void discardCard();

	Card* castCard(int _indexCard);

	void displayHand();

private:
	std::vector<Card*>* cardList;
	int nbMaxCardInHand;
};


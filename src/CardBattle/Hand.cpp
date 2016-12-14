#include "Hand.h"

using namespace std;

Hand::Hand()
{
	cardList = vector<Card*>();
	nbMaxCardInHand = 7;
}

Hand::~Hand()
{
	while (cardList.size() != 0)
	{
		Card* temp = *cardList.end();
		cardList.pop_back();
		delete temp;
	}
}

void Hand::drawCard(Card* _newCard)
{
	cardList.push_back(_newCard);
}

void Hand::discardCard()
{
	if (cardList.size() > nbMaxCardInHand)
	{
		for (int i = 0; i < cardList.size() - nbMaxCardInHand; i++)
		{
			cardList.pop_back();
		}
	}
}
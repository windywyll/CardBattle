#include "stdafx.h"
#include "Hand.h"

using namespace std;

Hand::Hand()
{
	cardList = new vector<Card*>();
	nbMaxCardInHand = 7;
	isFull = false;
}

Hand::Hand(Card * _hand, int _sizeInitial)
{
}

Hand::~Hand()
{
	while (cardList->size() != 0)
	{
		Card* temp = cardList->back();
		cardList->pop_back();
		delete temp;
	}
}

void Hand::drawCard(Card* _newCard)
{
	if (_newCard == nullptr)
		return;

	cardList->push_back(_newCard);

	if (cardList->size() >= nbMaxCardInHand)
		isFull = true;
}

void Hand::discardCard()
{
	if (cardList->size() > nbMaxCardInHand)
	{
		for (int i = 0; i < cardList->size() - nbMaxCardInHand; i++)
		{
			cardList->pop_back();
		}
	}
}

Card* Hand::castCard(int _indexCard)
{
	if (_indexCard < 0 || _indexCard >= cardList->size())
	{
		cout << "Card Invalid" << endl;
		return nullptr;
	}

	Card* toReturn = cardList->at(_indexCard);

	cardList->erase(cardList->begin() + _indexCard);

	return toReturn;
}

void Hand::displayHand()
{
	if (cardList->size() == 0)
	{
		cout << "No cards in hand" << endl;
		return;
	}

	for (int i = 0; i < cardList->size(); i++)
	{
		cout << "Card " << i << " : " << endl;
		cout << '/t'; 
		cardList->at(i)->displayCard();
		cout << endl;
	}
}
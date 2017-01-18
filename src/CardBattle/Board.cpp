#include "stdafx.h"
#include "Board.h"

using namespace std;

Board::Board()
{
	maxCreatureOnBoard = 11;
	cardList = new vector<Card*>();
}


Board::~Board()
{
	while (cardList->size() != 0)
	{
		Card* temp = cardList->back();
		cardList->pop_back();
		delete temp;
	}
}

void Board::displayBoard()
{
	if (cardList->size() == 0)
	{
		cout << "No creatures on board" << endl;
		return;
	}

	for (int i = 0; i < cardList->size(); i++)
	{
		cout << "Card " << i << " : " << endl;
		cout << '/t';

		cardList->at(i)->displayCard();

		if (cardList->at(i)->isTapped())
		{
			cout << " - Can't Attack";
		}

		cout << endl;
	}
}

void Board::castCard(Card * _card)
{
	_card->tapCard();
	cardList->push_back(_card);
}

Card * Board::creatureAttack(int indexCard)
{
	if (indexCard < 0 || indexCard > cardList->size())
	{
		cout << "Card Invalid" << endl;
		return nullptr;
	}

	if (cardList->at(indexCard)->isTapped())
	{
		cout << "Creature is exhausted" << endl;
		return nullptr;
	}

	cardList->at(indexCard)->tapCard();
	return cardList->at(indexCard);
}

Card* Board::creatureDies(int indexCard)
{
	Card* toReturn = cardList->at(indexCard);

	cardList->erase(cardList->begin() + indexCard);

	return toReturn;
}

void Board::untapBoard()
{
	for (int i = 0; i < cardList->size(); i++)
	{
		cardList->at(i)->untapCard();
	}
}

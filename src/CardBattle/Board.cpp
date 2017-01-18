#include "stdafx.h"
#include "Board.h"

using namespace std;

Board::Board()
{
	maxCreatureOnBoard = 11;
	cardList = vector<Card*>();
}


Board::~Board()
{
	while (cardList.size() != 0)
	{
		Card* temp = *cardList.end();
		cardList.pop_back();
		delete temp;
	}
}

void Board::displayBoard()
{
	if (cardList.size() == 0)
	{
		cout << "No creatures on board" << endl;
		return;
	}

	for (int i = 0; i < cardList.size(); i++)
	{
		cout << "Card " << i << " : " << endl;
		cout << '/t';
		cardList[i]->displayCard();
		cout << endl;
	}
}

void Board::castCard(Card * _card)
{
}

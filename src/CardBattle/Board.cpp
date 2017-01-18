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

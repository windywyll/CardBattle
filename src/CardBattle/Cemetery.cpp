#include "stdafx.h"
#include "Cemetery.h"

using namespace std;

Cemetery::Cemetery()
{
}


Cemetery::~Cemetery()
{
	while (cardList->size() != 0)
	{
		Card* temp = cardList->back();
		cardList->pop_back();
		delete temp;
	}
}

void Cemetery::death(Card* _card)
{
	cardList->push_back(_card);
}
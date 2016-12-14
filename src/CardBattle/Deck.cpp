#include "Deck.h"

using namespace std;

Deck::Deck()
{
	nbMaxCard = 40;
	pointsToDistributeByCardMin = 5;
	pointsToDistributeByCardMax = 22;
	cardList = vector<Card*>();

	fillDeck();
}


Deck::~Deck()
{
	while (cardList.size() != 0)
	{
		Card* temp = *cardList.end();
		cardList.pop_back();
		delete temp;
	}
}

Card* Deck::getTopCard()
{
	Card* toReturn = *cardList.end();
	cardList.pop_back();
	return toReturn;
}

void Deck::fillDeck()
{
	for (int i = 0; i < nbMaxCard; i++)
	{
		cardList.push_back(createCard());
	}
}

Card* Deck::createCard()
{
	int toDistribute = rand()%(pointsToDistributeByCardMax - pointsToDistributeByCardMin + 1) + pointsToDistributeByCardMin;
	int atkCard = rand() % (toDistribute-1) + 1;
	int defCard = toDistribute - atkCard;

	Card* cardToReturn = new Card(atkCard, defCard);

	return cardToReturn;
}
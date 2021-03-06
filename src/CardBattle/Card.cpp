#include "stdafx.h"
#include "Card.h"


using namespace std;

Card::Card()
{
	atk = 1;
	def = 1;
}

Card::Card(int _atk, int _def)
{
	atk = _atk;
	def = _def;
}

Card::~Card()
{
}

int Card::getAtk() const
{
	return atk;
}

int Card::getDef() const
{
	return def;
}

bool Card::isTapped() const
{
	return tapped;
}

void Card::tapCard()
{
	tapped = true;
}

void Card::untapCard()
{
	tapped = false;
}

void Card::displayCard()
{
	cout << "Creature ATK : " << atk << " - DEF : " << def;
}

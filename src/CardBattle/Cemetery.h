#pragma once

#include <vector>
#include "Card.h"

class Cemetery
{
public:
	Cemetery();
	~Cemetery();

	void death(Card* _card);

private:
	std::vector<Card*>* cardList;
};
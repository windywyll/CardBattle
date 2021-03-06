#pragma once
#include <iostream>

class Card
{
public:
	Card();
	Card(int _atk, int _def);
	~Card();

	int getAtk() const;
	int getDef() const;
	bool isTapped() const;
	void tapCard();
	void untapCard();

	void displayCard();

private:
	int atk, def;
	bool tapped;
};


#pragma once
class Card
{
public:
	Card();
	Card(int _atk, int _def);
	~Card();

	int getAtk() const;
	int getDef() const;
	bool isSummoningSick() const;
	void oneTurnOnBF();
	bool isTapped() const;
	void tapCard();
	void untapCard();

private:
	int atk, def;
	bool summoningSickness, tapped;
};


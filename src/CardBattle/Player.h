#pragma once


class Player
{
public:
	std::string name;
	int health;
	Player(std::string n, int l);
	Player();
	~Player();
};
#include "stdafx.h"
#include "Player.h"


Player::Player(std::string n, int l)
{
	name = n;
	health = l;
	canPlaySpell = false;
	nbSpellMax = 3;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::CreatePlayer()
{
	playerDeck = Deck();
	playerBoard = Board();
	playerHand = Hand();

	while (!playerHand.isFull)
	{
		playerHand.drawCard(playerDeck.getTopCard());
	}
}

void Player::draw(int _nbCardToDraw)
{
	if (_nbCardToDraw == 0)
		return;

	for (int i = 0; i < _nbCardToDraw; i++)
	{
		playerHand.drawCard(playerDeck.getTopCard());
	}
}

void Player::castSpell(int indexCard)
{
	playerBoard.castCard(playerHand.castCard(indexCard));
}

void Player::displayBoard()
{
	playerBoard.displayBoard();
}

void Player::displayHand()
{
	playerHand.displayHand();
}
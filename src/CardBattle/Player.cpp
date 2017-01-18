#include "stdafx.h"
#include "Player.h"

using namespace std;

Player::Player(int n, int l, unsigned int seed)
{
	name = n;
	health = l;
	canPlaySpell = true;
	nbSpellMax = 3;
	nbSpellPlayed = 0;
	isDead = false;

	srand(seed);

	playerDeck = new Deck();
	playerBoard = new Board();
	playerHand = new Hand();
	playerCemetery = new Cemetery();

	while (!playerHand->isFull)
	{
		playerHand->drawCard(playerDeck->getTopCard());
	}
}

Player::~Player()
{
}

void Player::draw(int _nbCardToDraw)
{
	if (_nbCardToDraw == 0)
		return;

	for (int i = 0; i < _nbCardToDraw; i++)
	{
		playerHand->drawCard(playerDeck->getTopCard());
	}
}

void Player::castSpell(int indexCard)
{
	Card* _temp = playerHand->castCard(indexCard);

	if (_temp == nullptr)
		return;

	playerBoard->castCard(_temp);
	nbSpellPlayed++;

	if (nbSpellPlayed == nbSpellMax)
		canPlaySpell = false;
}

void Player::playerTakeDamage(int _damage)
{
	health -= _damage;

	if (health < 0)
		isDead = true;
}

Card * Player::attackWithCreature(int indexCard)
{
	return playerBoard->creatureAttack(indexCard);
}

void Player::creatureDie(int indexCard)
{
	playerCemetery->death(playerBoard->creatureDies(indexCard));
}

void Player::beginTurn(int _nbCardToDraw)
{
	playerBoard->untapBoard();
	draw(_nbCardToDraw);
	nbSpellPlayed = 0;
	canPlaySpell = true;
}

void Player::endTurn()
{
	cout << "----- HAND -----" << endl;
	playerHand->discardCard();
}

void Player::displayBoard()
{
	cout << "----- BOARD -----" << endl;
	playerBoard->displayBoard();
}

void Player::displayHand()
{
	playerHand->displayHand();
}
#include "Player.h"

Player::Player(int n, int m, int id)
{
	N = n;
	ID = id;
	board = new Board(n, m);
	initialHit = initialMiss = secondaryHit = secondaryMiss = numAttacks = numAttacked = numRevives = 0;
}

void Player::Attack(Player* p)
{
	bool success = p->RegisterHit();
	numAttacks++;

	if (success)
		initialHit++;
	else
	{
		initialMiss++;

		success = p->RegisterHit();
		numAttacks++;

		if (success) 
			secondaryHit++;
		else
			secondaryMiss++;
	}
}

bool Player::RegisterHit()
{
	//get free spots
	vector<pair<int, int>> spots;
	board->GetFreeSpots(&spots);
	numAttacked++;

	if ((int)spots.size() == 0)
		return false;
	//choose random spot
	int spot = rand() % (int)spots.size();
	//return hit success(true)
	return board->Hit(spots.at(spot));
}

int Player::getTargetsRemaining()
{
	return board->getTargetsRemaining();
}

bool Player::isDead()
{
	return getTargetsRemaining() == 0;
}

void Player::Revive()
{
	numRevives++;
	
	//place 2 random new markers on board
	board->PlaceReviveMarkers();
}

void Player::PrintBoard()
{
	cout << "Board for Player " << ID << ':'<< endl;
	board->PrintBoard();
}

/*
	The number of this player's targets remaining (i.e., targets that were not hit).
	The number of times this player was revived from a state of suspended animation.
	The number of times this player was attacked.
	The number of attacks this player launched.
	The number of attacks this player launched that:
		were initial hits
		were initial misses
		were secondary hits
		were secondary misses
*/
void Player::Report()
{
	cout << "Player " << ID << " Report:" << endl;
	cout << "\tPlayer targets remaining: " << getTargetsRemaining() << endl;
	cout << "\tTimes revived: " << numRevives << endl;
	cout << "\tTimes attacked: " << numAttacked << endl;
	cout << "\tAttacks launched: " << numAttacks << endl;
	cout << "\t\tInitial hits: " << initialHit << endl;
	cout << "\t\tInitial misses: " << initialMiss << endl;
	cout << "\t\tSecondary hits: " << secondaryHit << endl;
	cout << "\t\tSecondary misses: " << secondaryMiss << endl;
}

Player::~Player()
{
	delete board;
}

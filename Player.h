#pragma once
#include "Board.h"
#include <iostream>
#include <mutex>

using namespace std;
class Player
{
public:
	Player(int n, int m, int id);
	void Attack(Player* p);
	bool RegisterHit();
	int getTargetsRemaining();
	bool isDead();
	void Revive();
	void PrintBoard();
	void Report();
	int getID() { return ID; }
	~Player();

private:
	Board* board;
	int N;
	int ID;
	int initialHit, secondaryHit, initialMiss, secondaryMiss;
	int numAttacks, numAttacked;
	int numRevives;
};


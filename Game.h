#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "Player.h"
#include "PlayerMonitor.h"

using namespace std;
class Game
{
public:
	Game(int p, int n, int m);
	void Fight(Player* p);
	~Game();

	void Run();
private:
	int P, N;
	bool go;
	mutex mtx;
	vector<thread*>* threads = new vector<thread*>;
	PlayerMonitor players;
	PlayerMonitor deadPlayers;
	condition_variable revived;
};
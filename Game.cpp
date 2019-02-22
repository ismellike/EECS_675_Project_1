#include "Game.h"

Game::Game(int p, int n, int m)
{
	P = p;
	N = n;

	//create people
	for (int i = 0; i < P; i++)
		players.put(new Player(n, m, i));
}

void Game::Fight(Player* p)
{
	while (!go);

	while (players.size() > 1)
	{
		if (p->isDead()) //suspended till game ends
		{
			this_thread::sleep_for(chrono::milliseconds(1)); //give time for other thread to pick up lock
			continue;
		}

		//get random player
		Player* enemy;
		while ((enemy = players.get())->getID() == p->getID());

		if (deadPlayers.size() >= P / 2.0 && players.size() >= 2)
		{
			if (rand() % 10 == 0) //10% chance
			{
				Player* rPlayer = deadPlayers.get(); //random player
				//cout << "Revived " << rPlayer->getID() << endl;
				players.put(rPlayer);
				deadPlayers.remove(rPlayer);
				unique_lock<mutex> reviving(mtx);
				rPlayer->Revive();
			}
		}

		//cout << "Attack from: " << p->getID() << " To: " << enemy->getID() << endl;
		p->Attack(enemy);
		if (enemy->isDead())
		{
			//cout << "Died " << enemy->getID()<< endl;
			players.remove(enemy); //protected by methods
			deadPlayers.put(enemy);
		}
		this_thread::sleep_for(chrono::milliseconds(1)); //give time for other thread to pick up lock
	}
}

Game::~Game()
{
	for (int i = 0; i < (int)threads->size(); i++)
		delete threads->at(i);
	delete threads;
}

void Game::Run()
{
	if (P == 2 && N <= 40)
	{
		cout << "BEFORE: " << endl;
		for (int i = 0; i < P; i++)
			players.at(i)->PrintBoard();
	}

	go = false;
	//create P threads
	for (int i = 0; i < P; i++) {
		threads->push_back(new thread(&Game::Fight, this, players.at(i)));
	}
	go = true;

	//thread starts
	for (int i = 0; i < P; i++)
	{
		threads->at(i)->join();
	}


	//end
	players.sortPlayers();
	deadPlayers.sortPlayers();

	if (P == 2 && N <= 40)
	{
		cout << "AFTER: " << endl;
		for (int i = 0; i < players.size(); i++)
			players.at(i)->PrintBoard();
		for (int i = 0; i < deadPlayers.size(); i++)
			deadPlayers.at(i)->PrintBoard();
	}

	cout << "WINNER: " << endl;
	for (int i = 0; i < players.size(); i++)
		players.at(i)->Report();
	cout << "LOSERS: " << endl;
	for (int i = 0; i < deadPlayers.size(); i++)
		deadPlayers.at(i)->Report();
}

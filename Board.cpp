#include "Board.h"

//BOARD LAYOUT:
//2d int array filled with 0's
//on selection simply change to 1
//text generation detects if marker was there

Board::Board(int n, int m)
{
	N = n;
	M = m;

	board = new bool*[N];
	for (int i = 0; i < N; i++)
	{
		board[i] = new bool[N];
		for (int j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}

	PlaceMarkers();
}

void Board::PlaceMarkers()
{
	for (int i = 0; i < M; i++)
	{
		int randx, randy;
		//find unique slot
		while (true)
		{
			randx = rand() % N;
			randy = rand() % N;

			bool unique = true;
			for (int j = 0; j < i; j++)
			{
				if (markers.at(j)->isOccupied(randx, randy))
					unique = false;
			}
			if (unique)
				break;
		}
		markers.push_back(new Marker(randx, randy));
	}
}

void Board::GetFreeSpots(vector<pair<int, int>>* spots)
{
	unique_lock<mutex> lock(methodLock);
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == 0)
				spots->push_back(make_pair(i, j));
		}
}

int Board::getTargetsRemaining()
{
	unique_lock<mutex> lock(methodLock);
	int targets = 0;
	for (int i = 0; i < M; i++)
	{
		int pos[2];
		markers.at(i)->getPosition(pos);
		if (board[pos[0]][pos[1]] == 0)
			targets++;
	}
	return targets;
}

void Board::PlaceReviveMarkers()
{
	unique_lock<mutex> lock(methodLock);
	//increase amount
	int randx, randy;
	int rand2x, rand2y;

	//place first marker
	randx = rand() % N;
	randy = rand() % N;
	board[randx][randy] = 0;
	bool isNew = true;
	for (int i = 0; i < M; i++)
		if (markers.at(i)->isOccupied(randx, randy))
		{
			isNew = false;
			break;
		}

	if (isNew)
	{
		markers.push_back(new Marker(randx, randy));
		M++;
	}

	isNew = true;
	//make sure second is not on first
	do {
		rand2x = rand() % N;
		rand2y = rand() % N;
	} while (randx == rand2x && randy == rand2y);
	//place second marker
	board[rand2x][rand2y] = 0;
	for (int i = 0; i < M; i++)
		if (markers.at(i)->isOccupied(randx, randy))
		{
			isNew = false;
			break;
		}
	if (isNew)
	{
		markers.push_back(new Marker(rand2x, rand2y));
		M++;
	}
}

bool Board::Hit(pair<int, int> location)
{
	unique_lock<mutex> lock(methodLock);
	board[location.first][location.second] = 1;

	for (int i = 0; i < M; i++)
		if (markers.at(i)->isOccupied(location.first, location.second))
			return true;
	return false;
}

//performance for print is bad but easy to work with and only needed at end 1x
void Board::PrintBoard()
{
	for (int i = 0; i < N; i++)
	{
		cout << '\t';
		for (int j = 0; j < N; j++)
		{
			bool marker = false;
			for (int m = 0; m < M; m++)
			{
				if (markers.at(m)->isOccupied(i, j))
				{
					marker = true;
					break;
				}
			}

			if (marker)
			{
				if (board[i][j] == 0)
					cout << 'O';
				else
					cout << '*';
			}
			else
			{
				if (board[i][j] == 0)
					cout << '_';
				else
					cout << '.';
			}
			cout << ' ';
		}
		cout << endl;
	}
}

Board::~Board()
{
	for (int i = 0; i < N; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	for (int i = 0; i < M; i++)
		delete markers.at(i);
}

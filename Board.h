#pragma once
#include "Marker.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class Board
{
public:
	Board(int n, int m);
	void PlaceMarkers();
	void GetFreeSpots(vector<pair<int, int>>* spots);
	int getTargetsRemaining();
	void PlaceReviveMarkers();
	bool Hit(pair<int, int>);
	void PrintBoard();
	~Board();
private:
	mutex methodLock;
	int N, M;
	bool** board;
	vector<Marker*> markers;
};
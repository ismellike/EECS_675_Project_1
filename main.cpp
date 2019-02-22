#include <iostream>
#include "Game.h"

using namespace std;
int main(int argc, char* argv[])
{
	int p, n, m;
	if (argc != 4)
	{
		cout << "Usage: ./battleship P N M" << endl;
		return -1;
	}

	try {
		p = stoi(argv[1]);
		n = stoi(argv[2]);
		m = stoi(argv[3]);
	}
	catch (exception) {
		cout << "Params must be integers" << endl;
		return -1;
	}

	if (p < 2)
	{
		cout << "Number of players must be >= 2" << endl;
		return -1;
	}

	if (m <= 0 || n <= 0)
	{
		cout << "N and M must be greater than 0" << endl;
		return -1;
	}

	if (m > n*n)
	{
		cout << "M must be smaller than N^2" << endl;
		return -1;
	}

	Game game(p, n, m);
	game.Run();
    return 0;
}
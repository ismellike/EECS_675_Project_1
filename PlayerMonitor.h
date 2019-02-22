/*
 THIS IS BASED ON LISTING 3.20

 ============================================================================
 Author        : G. Barlas
 Modified      : J.R. Miller 2015-09-09 and 2017-02-02 to use C++ 11 classes
				 and a few other things like more informative output.
 Version       : 1.0
 Last modified : December 2014
 License       : Released under the GNU GPL 3.0
 Description   :
 To compile    : qmake PlayerMonitor1ProdCons.pro; make
 ============================================================================
 */
#include <condition_variable>
#include <mutex>
#include <vector>
#include <algorithm>
#include "Player.h"

using namespace std;

class PlayerMonitor
{
private:
	mutex methodLock;
	vector<Player*> buffer;
public:
	void put(Player* item);
	Player* get();
	int size();
	void remove(Player* item);
	Player* at(int i);
	void sortPlayers();
	PlayerMonitor();
	~PlayerMonitor();
};

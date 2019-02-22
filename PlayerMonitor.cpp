#include "PlayerMonitor.h"

PlayerMonitor::PlayerMonitor()
{
}

PlayerMonitor::~PlayerMonitor()
{
	for (int i = 0; i < (int)buffer.size(); i++)
		delete buffer.at(i);
}

void PlayerMonitor::put(Player* item)
{
	int index = -1;
	for (int i = 0; i < (int)buffer.size(); i++)
		if (buffer.at(i) == item)
			index = i;

	if(index == -1)//protect
		buffer.push_back(item);
}

Player* PlayerMonitor::get()
{
	std::unique_lock<mutex> ml(methodLock);
	int index = rand() % buffer.size();
	return buffer.at(index);
}

int PlayerMonitor::size()
{
	unique_lock<mutex> lock(methodLock);
	return buffer.size();
}

void PlayerMonitor::remove(Player* item)
{
	int index = -1;

	for (int i = 0; i < (int)buffer.size(); i++)
		if (buffer.at(i) == item)
		{
			index = i;
			break;
		}

	if(index != -1) //protect against multiple access
		buffer.erase(buffer.begin() + index);
}

Player* PlayerMonitor::at(int i)
{
	return buffer.at(i);
}

void PlayerMonitor::sortPlayers()
{
	sort(buffer.begin(), buffer.end(), [](Player* a, Player* b) { return a->getID() < b->getID(); });
}

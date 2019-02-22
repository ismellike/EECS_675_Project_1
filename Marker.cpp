#include "Marker.h"



Marker::Marker()
{
	pos[0] = pos[1] = 0;
}

Marker::Marker(int x, int y)
{
	pos[0] = x;
	pos[1] = y;
}

bool Marker::isOccupied(int x, int y)
{
	return pos[0] == x && pos[1] == y;
}

void Marker::getPosition(int inArray[2])
{
	inArray[0] = pos[0];
	inArray[1] = pos[1];
}


Marker::~Marker()
{
}

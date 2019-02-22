#pragma once
class Marker
{
public:
	Marker();
	Marker(int x, int y);
	bool isOccupied(int x, int y);
	void getPosition(int inArray[2]);
	~Marker();

private:
	int pos[2];
};


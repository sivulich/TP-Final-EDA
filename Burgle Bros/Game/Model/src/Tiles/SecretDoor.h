#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
You may move into this tile through walls adjacent to this tile. This is one-way;
you can't move or peek back out through a wall. Guards will not move through secret doors.
*/

class SecretDoor :
	public Tile
{
public:
	SecretDoor(int floor, int col, int row) : Tile(SECRET_DOOR, floor, col, row) { this->alarmTile = false; };
	~SecretDoor();
	void addSecretDoor(Tile * t) { secretDoors.push_back(t); };



	/**
	Executes the tile's special actions, if any...
	@param p player who is moving
	*/
	virtual void turnUp() override;
private:
	vector<Tile *> secretDoors;
};



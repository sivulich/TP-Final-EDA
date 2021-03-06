#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"


//If this tile is revealed by moving into it, that player falls 1 floor. When falling,
//it does not count as entering that tile. If you are on the bottom floor, nothing happens.
//Any players that enters after it is revealed do not fall, but can move downstairs for an action
//(this does not count as entering).
//This is one-way; you cannot move up to this tile from below.


class Walkway :
	public Tile
{
public:
	Walkway(int floor, int col, int row) : Tile(WALKWAY,floor, col, row) { this->alarmTile = false; };
	~Walkway();

	//Executes the tile's special actions, if any...
	//@param p player who is moving
	virtual void enter(PlayerInterface * player) override;

	//Makes the player fall to the tile beneath him, if possible
	//@param p player
	bool fallDown(PlayerInterface * p);

private:
};


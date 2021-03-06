#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

//Stairs allow you to move directrly up one floor. Put a Downstair token
//on the corresponding tile one floor up (I.e. 2nd row, 3rd column). 
//You can also peek up stairs and come back downstairs. 
//It takes 1 action to take the stairs to the roof at the end of the game.

class Stair :
	public Tile
{
public:
	Stair(int floor, int col, int row) : Tile(STAIR, floor, col, row) { this->alarmTile = false; };
	~Stair();
	vector<Coord> whereCanIPeek()override;
};



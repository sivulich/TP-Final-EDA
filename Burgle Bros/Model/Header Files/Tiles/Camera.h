#pragma once
#include "Tile.h"

/*
Guards on a Camera tile see all the other revealed tiles that are cameras, on any floor.
You do not lose Stealth, but they remotely trigger an Alarm on your tile (by calling on their
radio). Note thar Guards can see through Cameras when moving through a Camera Tile on their turn.
*/
class Camera :
	public Tile
{
public:
	Camera(int floor, int col, int row) : Tile(floor, col, row) {};
	~Camera();

};


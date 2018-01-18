#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
	If a player (or Guard) is not on this tile, it takes 3 actions to enter. 
	If you can't pay the extra actions, you stay in the tile you came from.
 */

// SI UN PLAYER QUIERE MOVERSE ACA, EL MODELO DEBE ACTUALIZAR isOccupied CON "true" SI EL GUARDIA O SU COMPA�ERO ESTAN EN EL DEADBOLT
// Y PONERLO EN "false" SI NO HAY NADIE.
// ADEMAS, SI ESTA EL GUARDIA LE TIENE QUE SACAR UN STEALTH TOKEN

class Deadbolt :
	public Tile
{
public:
	Deadbolt(int floor, int col, int row) : Tile(DEADBOLT,floor, col, row) {};
	~Deadbolt();



	/**
	Applies the action given to the player
	@param action Action to execute
	@param p Player who wants to do the action
	*/
	virtual bool doAction(string action, PlayerInterface * player) override;

private:
	bool isOccupied;
};


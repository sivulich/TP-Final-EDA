#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Motion tile,
they can spend one of these tokens to prevent an Alarm from triggering.
*/

class ComputerRoomM : public Tile
{
public:
	ComputerRoomM(int floor, int col, int row) : Tile(COMPUTER_ROOM_M, floor, col, row) {};
	~ComputerRoomM();


	virtual vector<string> getActions(PlayerInterface * player) override;
	virtual bool doAction(string action, PlayerInterface * player) override;

	/**
	Returns the amount of hack tokens in the tile
	*/
	int getHackTokens() { return hackToken; };
	/**
	Removes 1 hack token from the tile
	*/
	void removeToken() { --hackToken; };

	void addToken() {if(hackToken<6) ++hackToken; };

private:
	
	int hackToken;
};

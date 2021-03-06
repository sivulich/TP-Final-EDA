#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
/*
When moving into a Keypad tile, you must guess the code. Take a die and toll it. If it is a 6, you enter 
the tile. If not, you will have to stay in the tile you came from. Once you roll a 6, put an open marker 
on the tile - any team member can enter freely now that code is known. For each on the fourth attempt in 
a single turn you would roll 4 dice, but the next turn you would start back at 1 die. If you start the game 
or fall into this room, you may leave but must open it to get back in.
*/

class Keypad : public Tile
{
public:
	Keypad(int floor, int col, int row) : Tile(KEYPAD, floor, col, row) { keyKnown = false; attemptsThisTurn = 0; attemptsThisAction = 0; currentPlayer = -1; currentTurn = -1; this->alarmTile = false; };
	~Keypad();
	/**
	Return true if the player can move to the tile	(Always true except on special cases where function will be overwritten)
	@param p player who is moving
	*/
	virtual bool canMove(PlayerInterface * player) override;
	bool tryToOpen(int dice, PlayerInterface * player);
	void clearAttempts() { attemptsThisTurn = 0; notify(); };
	bool keyDecoded() { return keyKnown; };
	unsigned int getAttempts() { return attemptsThisTurn; };

private:
	void addAttempt() { ++attemptsThisTurn; notify(); };

	bool keyKnown;
	unsigned int attemptsThisTurn;
	unsigned int attemptsThisAction;

	int currentPlayer, currentTurn;
};


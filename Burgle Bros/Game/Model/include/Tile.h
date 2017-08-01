#pragma once
#include "../src/BaseCard.h"
#include <Enumerations.h>
#include <Configs.h>
#include <BaseModel.h>
#include "../src/PlayerInterface.h"
#include "../src/Loots/Loot.h"



/**
	
*/

class Tile : public BaseCard
{
public:
	/**
		Default constructor.
	*/
	Tile();

	/**
		Construct a tile with a position in the floor and a tileType.

		@param floor floor of the tile
		@param col column of the tile
		@param row row of the tile
	*/
	Tile(tileType t, unsigned floor, unsigned col, unsigned row);

	/**
		Peek the tile
	*/
	void peek();

	/**
		Return true if the player can move to the tile, checking adjacency. On child classes check specific conditions.
		@param p player who is moving
	*/
	virtual bool canMove(PlayerInterface * player);

	/**
		Executes the tile's special actions, if any...
		@param p player who is moving
	*/
	virtual void enter(PlayerInterface * player);
	/**
		Executes any special action when leaving the tile
	*/
	virtual void exit(PlayerInterface * player) {};

	/**
		Apart from turning up the card, sort the safe number
	*/
	virtual void turnUp()override;

	/**
		Returns the position of the tile in the floor.
	*/
	Coord getPos();

	/**
	Return the floor number
	*/
	int floor();

	/**
	Return the column number
	*/
	int col();

	/**
	Return the row number
	*/
	int row();

	/**
		Returns the type of the tile.
	*/
	tileType getType();

	/**
		Return true if the tile is from the given type
	*/
	bool is(tileType t);

	/**
		Checks if there is an alarm activated in the tile.
	*/
	bool hasAlarm();

	/**
		Checks if there is a loop on tile.
	*/
	bool hasLoot();

	/**
		Activate an alarm in the tile.
	*/
	void setAlarm(bool b);

	/**

	*/
	void setLoot(Loot * l);

	/**
		Returns a vector of strings with the actions the player can do on the tile they are on.
		Actions PEEK and MOVE are always valid. On each tileType overload the function
		@param p Player who wants to check the actions
	*/
	virtual vector<string> getActions(PlayerInterface * player);

	/**
		Applies the action given to the player
		@param action Action to execute
		@param p Player who wants to do the action
	*/
	virtual bool doAction(string action, PlayerInterface * player);

	/**
		If tile is flipped returns the safe number, else returns 0.
	*/
	int getSafeNumber();

	/**
		Return a vector of Coords where player can moove
	*/
	virtual vector<Coord> whereCanIMove();

	/**
		Return a vector of Coords where player can Peek
	*/
	virtual vector<Coord> whereCanIPeek();

	/**
		Add a coord to the adjacent list
	*/
	void addAdjacent(Coord c);

	/**
		Delete a coord from the adjacent list
	*/
	void deleteAdjacent(Coord b);

	/**
		Returns true if the tile given is adjacent
	*/
	bool isAdjacent(Coord t);

	bool hasCrackToken(){ return crackToken; };
	void crackTile() { crackToken = true; };
	bool hasStairToken() { return stairToken; };
	bool hasCrowToken() { return crowToken; };
	void setCrowToken(bool b) { crowToken = b; };
	void setStairToken(bool b) { stairToken = b; };

	/**
		Returns true if you could hide from the guard. Used for Lavatory.
	*/
	virtual bool tryToHide() { return false; };

	/**
	Clears visible from and adds the current tile to visibleFrom
	*/
	virtual void updateVisibleFrom(PlayerInterface * player);

protected:
	// Coord containing floor, column and row of the tile
	Coord coord;
	// Type of tile
	tileType type;
	// Number to crack the safe
	int safeNumber;
	// Vector with adjacent tiles (coords)
	vector<Coord> adjacent;
	// A tile can have a loot (a safe tile or a loot has been dropped)
	vector<Loot*> loot;

	bool crackToken, crowToken, stairToken, alarmToken;

};
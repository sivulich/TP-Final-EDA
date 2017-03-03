#pragma once
#include "./Configs.h"
#include "./actionNode.h"
#include "./Loots/Loot.h"
#include "./Tiles/Tile.h"
#include "./Characters/Character.h"
#include "./PlayerInterface.h"
#include "./Board.h"
#include "./BaseModel.h"

class Player : public PlayerInterface, public BaseModel
{
public:
#ifdef DEBUG
	/**
		Add the amount of action tokens you want
	*/
	void setActionTokens(int i) { actionTokens = i; };
#endif

	/**
		Construct a player (with access to the board)
	*/
	Player(Board * b);
	/**
		Hay que destruir el caracter... algo mas?
	*/
	~Player() {};

	/**
		Sets the name of the player
	*/
	void setName(string & playerName);
	/**
		Get player name
	*/
	virtual string getName()override;
	/**
		Print player in console;
	*/
	void print();
	/**
		Returns the player's positions
	*/
	virtual Coord getPosition()override;
	/**
		Return true if the player is on the roof of the building 
	*/
	bool isOnRoof();
	/**
	
	*/
	vector<string> getActions();
	/**
		Set player position with a coord
	*/
	virtual void setPosition(Coord c)override;
	/**
		Sets the player's position with a tile pointer
	*/
	void setPosition(Tile* c);

	/**
		Sets the character the player will use
	*/
	void setCharacter(characterType type);
	/**
		Get character type
	*/
	characterType getCharacterType();

	/**
	
	*/
	bool needConfirmationToMove(Coord c);
	/**
		Reset the player action tokens
	*/
	virtual void resetActionTokens()override;
	/**
		Move the player to the tile
		@params newTile pointer to the tile the player wants to move to
	*/
	bool move(Tile * newTile);
	bool move(Coord c);
	/**
		Peek the tile in exchange of an action token
	*/
	void peek(Tile * newTile);
	void peek(Coord c);
	/**
		Appends a new action to the action history
		@params action the string of the action that occured
		@params tile coordinate to the tile where the action happened
	*/
	virtual void newAction(string action, Coord tile)override;
	
	/**
		Removes 1 stealth token if possible
	*/
	virtual void removeStealthToken()override;
	
	/**
		Removes 1 action token if possible
	*/
	virtual void removeActionToken()override;
	/**
		Returns the amount of stealth tokens
	*/
	virtual int getStealthTokens()override;

	/**
		Returns the amount of action tokens
	*/
	virtual int getActionTokens()override;

	/**
		Simulates a die being thrown
	*/
	virtual  int throwDice()override;
	/**
	
	*/
	void addLoot(Loot * l);
	/**

	*/
	virtual bool has(lootType l)override;
	/**
		Returns true if the player has at least one loot.
	*/
	virtual bool hasLoot()override;

	/**
		Retrun true if the guard can see the player from that position
	*/
	virtual bool isVisibleFrom(Coord c)override;
	/**
		Adds a coordinate to the list of coordinates the player is visible from
	*/
	virtual void addVisibleTile(Coord tile)override;
	/**
		Returns the vector with the coordinates the player is visible from
	*/
	virtual vector <Coord> getVisibleFrom()override;
	/**
		Clears the visibleFrom list
	*/
	virtual void clearVisibleFrom() override;


	vector<Loot*>& getLoots() { return loots; };

	/**
		Tells the tile the player wants to add a token
	*/
	void wantsToAddToken() { currentTile->doAction(toString(ADD_TOKEN), this); };

	/**
		Tells the tile the player wants use an action to throw the dice
	*/
	void wantsToThrowDice() { currentTile->doAction(toString(THROW_DICE), this); };

	/**
		Tells the tile the player wants use a token
	*/
	void wantsToUseToken() { currentTile->doAction(toString(USE_TOKEN), this); };

private:
	string name;
	Character * character;
	Tile * currentTile;
	Board * board;
	int actionTokens;
	int stealthTokens;
	vector<actionNode> actions;
	vector <Loot*> loots;

	
	// Coord from where the guard can see the player (player position normally, unless special cases)
	vector <Coord> visibleFrom;
	vector <unsigned int> dice;	
};
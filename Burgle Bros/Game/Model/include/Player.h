#pragma once
#include "./Configs.h"
#include "../src/actionNode.h"
#include "../src/Loots/Loot.h"
#include <Tile.h>
#include "../src/Characters/Character.h"
#include "../src/PlayerInterface.h"
#include "./Board.h"
#include "./BaseModel.h"

class Player : public PlayerInterface, public BaseModel
{
public:
	/**
		Construct a player
	*/
	Player(Board * b, Player * p);

	/**
		Hay que destruir el caracter... algo mas?
	*/
	~Player() {};

	
	
	// SETTERS


	/**
		Sets the name of the player
	*/
	void setName(string & playerName);

	/**
		Set player position to a coord, only moves player to this position and turn up the tile
	*/
	virtual void setPosition(Coord c)override;

	/**
		Sets the character the player will use
	*/
	void setCharacter(characterType type);

	/**
		Add the amount of action tokens you want
	*/
	void setActionTokens(int i) { actionTokens = i; };

	/**
		Add the amount of stealth tokens you want
	*/
	void setStealthTokens(int i) { stealthTokens = i; };


	
	// GETTERS
	


	/**
		Get player name
	*/
	virtual string getName()override;

	/**
		Returns the player's positions
	*/
	virtual Coord getPosition()override;

	/**
		Return a vector of strings with the actions the player can do
	*/
	vector<string> getActions();

	/**
	Get character type
	*/
	characterType getCharacterType();

	/**
		Returns the amount of stealth tokens
	*/
	virtual int getStealthTokens()override;

	/**
		Returns the amount of action tokens
	*/
	virtual int getActionTokens()override;

	/**
	Returns the vector with the coordinates the player is visible from
	*/
	virtual vector <Coord> getVisibleFrom()override;

	/**

	*/
	vector<Loot*>& getLoots() { return loots; };

	/**

	*/
	int getTurn() { return turn; };





	// MISC

	/**
		Print player in console;
	*/
	void print();
	
	/**
		Return true if the player is on the roof of the building 
	*/
	bool isOnRoof();

	/**

	*/
	bool needConfirmationToMove(Coord c);
	
	/**
		Removes 1 stealth token if possible
	*/
	virtual void removeStealthToken()override;

	/**
		Removes 1 action token if possible
	*/
	virtual void removeActionToken()override;

	/**
	
	*/
	void addTurn() { turn++; };

	/**
		Reset the player action tokens
	*/
	virtual void resetActionTokens()override;

	/**

	*/
	vector<Coord> whereCanIMove();

	/**

	*/
	vector<Coord> whereCanIPeek();

	/**
		Move the player to the tile
	*/
	
	bool move(Coord c);
	
	/**
		Peek the tile
	*/
	bool peek(Coord c);
	
	/**
		Use a token from a Computer Room or
	*/
	void useToken();

	/**
		Add a token to a Computer Room
	*/
	void addToken();

	/**
		Add a die to a Safe
	*/
	void addDie();

	/**
		Simulates a die being thrown
	*/
	virtual  int throwDice();
	
	/**

	*/
	virtual void addLoot(lootType l)override;

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
		Clears the visibleFrom list
	*/
	virtual void clearVisibleFrom() override;

	/**
		Clears the visibleFrom list
	*/
	void setVisibleFrom(vector<Coord> v) { if (!v.empty()) this->visibleFrom = v; };




	// REVISAR DE ACA PA BAJO

	/**
		Creates an alarm in the specified coord (if player is ________)
	*/
	bool createAlarm(Coord c);
	
	/**
		Place a crow token in the specified coord (if player is ________)
	*/
	void placeCrow(Coord c);
	
	/**
	Appends a new action to the action history
	*/
	virtual void newAction(string action, Coord tile)override;

	
	/////////// ??????????????? :O FUNCIONES WHAT THE ACTUAL FAK
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
	
	/**
	
	*/
	void useAbility(bool b) { character->useAbility(b); };
	//////////////////////////////////////////
	

	

	
	

private:
	// Name of the player
	string name;
	// 
	Character * character;
	// Tile where character token is placed on the board
	Tile * currentTile;
	// Pointer to other player (needed to know position of other player, to offer or request loot)
	Player * otherPlayer;
	// Pointer to the board (access tiles)
	Board * board;
	// Number of action tokens
	int actionTokens;
	// Number of stealth tokens
	int stealthTokens;
	// Number of turns the player has played
	int turn;
	// History of actions
	vector<actionNode> actions;
	// Loots the player carries 
	vector <Loot*> loots;
	// Coords from where the guard can see the player (only player current position normally, unless special cases)
	vector <Coord> visibleFrom;
	// Vector containing strings with possible actions player can do at the moment
	// VER SI HACE FALTA TENER EL VECTOR GUARDADO, O SOLO GENERARLO CUANDO SE LLAMA LA FUNCION
	vector <string> possibleActions;
	// ???
	vector <unsigned int> dice;


	////////// PRIVATE FUNCS
	/**
		Move to a tile
	*/
	bool move(Tile * newTile);

	/**
		Peek a tile
	*/
	bool peek(Tile * newTile);

	/**
		Sets the player's position with a tile pointer
	*/
	void setPosition(Tile* c);
};
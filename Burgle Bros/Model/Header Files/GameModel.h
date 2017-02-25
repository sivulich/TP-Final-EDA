#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Configs.h"

DEFINE_ENUM_WITH_CONVERSIONS(state, (INPUT_1, 0)(INPUT_2, 1)(INPUT_3, 2)(RUN, 3));
DEFINE_ENUM_WITH_CONVERSIONS(turn, (LOOT_1, 0)(PLAYER_1, 1)(GUARD_1, 2)(LOOT_2, 3)(PLAYER_2, 4)(GUARD_2, 5));
class GameModel : public BaseModel
{
public:
	GameModel() : player1(&board), player2(&board)
	{
		for (int i = 0; i < 3; i++)
			board[i]->getGuard()->setPlayers(&player1, &player2);
		
	};

	/**
		Returns true if game is over
	*/
	bool gameOver();
	
	
	/**
		Debug funcion to test in console
	*/
	pair<action_ID, string> getInput();
	/**

	*/
	void input(string& in);
	/**

	*/
	void setPlayer1Name(string& name);
	/**

	*/
	void setPlayer2Name(string& name);
	/**

	*/


	Board board;
	/*Player info*/
	Player player1;
	Player player2;

private:
	Player* currentPlayer;
	/*Input params*/
	void resetInput() { command = parameter = confirmation = ""; currState = INPUT_1; };
	string command;
	string parameter;
	string confirmation;

	/*Fsm for input*/
	state currState;
	turn  currTurn;
	Player* otherPlayer;
};


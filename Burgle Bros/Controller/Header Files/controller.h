#pragma once

#include "../../Model/Header Files/GameModel.h"
#include "../../ConsoleView/ConsoleView.h"
#include "../GameFSM.h"

DEFINE_ENUM_WITH_CONVERSIONS(gameState,
(ROLL_FOR_LOOT)
(PLAYER_TURN)
(GUARD_TURN)
(GAMEOVER)
(EXIT))

DEFINE_ENUM_WITH_CONVERSIONS(gameEvent,
(Move)
(Peek)
(Add_token)
(Use_token)
(Throw_dice)
(A_action)
(R_action)
(R_stealth)
(Move_guard)
(Createalarm)
(Place_Crow)
(No_event))


/**
	Controller class which relates the model with the view.
	It has an event dispatcher and a finite state machine with the game logic
	whick modifies the model and renders the view
*/
class Controller
{
public:
	Controller(GameModel * m, ConsoleView * v)// : FSM(m)
	{
		model = m;
		view = v;
	}

	void startGame()
	{
		void startGame();
		gameState status = PLAYER_TURN;

		while (status != EXIT)
		//FSM.start();
		//while (FSM.isRunning())
		{

			if (status == PLAYER_TURN)
			{
				cout << model->currentPlayer()->getName() << "'s turn." << endl;
				cout << "Available actions: ";
				vector<string> actions = model->currentPlayer()->getActions();
				for (auto& s : actions)
					cout << s << " ";
				cout << endl;
			}
			string command,coord;
			cin >> command;
			gameEvent event = toEnum_gameEvent(command.c_str());

			bool move;
			switch (status)
			{
				case PLAYER_TURN:
				{
					switch (event)
					{
					case Move:
					{
						cin >> coord;
						Coord c(coord[0] - '0' - 1, coord[1] - 'A', coord[2] - '0' - 1);

						move = true;
						if (model->currentPlayer()->needConfirmationToMove(c))
						{
							cout << "Are you sure you want to move? (YES/NO)" << endl;
							string g;
							cin >> g;
							if (g == "NO")
								move = false;
						}

						if (move)
						{
							model->currentPlayer()->move(c);

							if (model->gameOver() == true)
								status = GAMEOVER;
							else if (model->currentPlayer()->getActionTokens() == 0)
							{
								status = GUARD_TURN;
								model->currentPlayer()->useAbility(false);
							}
							else if (model->win())
								cout << "YOU WIN" << endl;
						}
					}
					break;

					case Peek:
					{
						cin >> coord;
						Coord c(coord[0] - '1', coord[1] - 'A', coord[2] - '1');

						model->currentPlayer()->peek(c);
						if (model->currentPlayer()->getActionTokens() == 0)
						{
							status = GUARD_TURN;
							model->currentPlayer()->useAbility(false);
						}
					}
					break;

					case Add_token:
					{
						model->currentPlayer()->wantsToAddToken();
					}
					break;

					case Throw_dice:
					{
						model->currentPlayer()->wantsToThrowDice();
					}
					break;
					case Use_token:
					{
						model->currentPlayer()->wantsToUseToken();
					}
					break;
					case A_action:
					{
						model->currentPlayer()->setActionTokens(model->currentPlayer()->getActionTokens()+4);
					}
					break;
					case R_action:
					{
						model->currentPlayer()->removeActionToken();
					}
					break;

					case R_stealth:
					{
						model->currentPlayer()->removeStealthToken();
					}
					break;
					}
					case Createalarm:
					{
						cin >> coord;
						Coord c(coord[0] - '0' - 1, coord[1] - 'A', coord[2] - '0' - 1);
						if (model->currentPlayer()->createAlarm(c))
							model->currentPlayer()->useAbility(true);
					}
					break;
					case Place_Crow:
					{

					}
					break;
				}
				break;

				case GUARD_TURN:
				{
					DEBUG_MSG("Guard turn:");
					switch (event)
					{
					case Move_guard:
					{
						model->moveGuard();

						if (model->gameOver())
							status = GAMEOVER;
						else if (!model->guardIsMoving())
						{
							model->changeTurn();
							status = PLAYER_TURN;
						}
					}
					break;
					}
				}
				break;

				case EXIT:
				{

				}
				break;
			}
			model->print();
			//getInput();
			//FSM.processEvent(new movee());
 		}
		
	//	FSM.stop();		
 	}
		/*FSM.start();
		while (FSM.isRunning())
		{
			getInput();
			FSM.processEvent(new movee());
		}
		FSM.stop();*/


private:
	void getInput()
	{
		// Si se movio el mouse, hoverear botones
		// Si se hizo click preguntar a la vista en que y traducir a evento
		// Si se apreto una tecla, traducir a evento 
		// Si sono algun timer (para dibujar, o el del movimiento del guardia), traducir a evento
		// Si llego paquete de jugador remoto, traducir a evento :)))))))))) MIERDA
		std::cin >> input;
	};

	gameEvent ev;
	string input;

	//GameFSM FSM;
	GameModel * model;
	ConsoleView * view;
	
};
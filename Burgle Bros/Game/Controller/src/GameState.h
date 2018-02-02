#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 50 //or whatever you need 

#include <iostream>
// Back-end:
#include <boost/msm/back/state_machine.hpp>
// Front-end:
#include <boost/msm/front/state_machine_def.hpp>
// Functors:
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/euml.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <Configs.h>
#include "./events.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;


struct GameState_ : public msm::front::state_machine_def<GameState_>
{
	// INICIALIZAR PUNTEROS!

	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	//BurgleNetwork * network;
	int gameMode;
	Timer * guardTimer;
	action_ID currentAction; // Stores current action chosen by player

	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		fsm.model->currentPlayer()->setCharacter(HACKER);
		fsm.model->otherPlayer()->setCharacter(RAVEN);
		fsm.model->currentPlayer()->setName(string("Prueba"));
		fsm.model->otherPlayer()->setName(string("Resto"));
		std::cout << "Entering Burgle Bros Finite State Machine" << std::endl;
		fsm.model->setBoard();
		
		fsm.graphics->showGameScreen();

	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "Leaving Burgle Bros Finite State Machine" << std::endl;
	}

	//----------------------- STATES -----------------------------//

	struct chooseInitialPos : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Choose initial pos: ";
			vector<Coord> v;
			v.push_back(Coord(0, 0, 0));
			v.push_back(Coord(0, 0, 1));
			v.push_back(Coord(0, 0, 2));
			v.push_back(Coord(0, 0, 3));
			v.push_back(Coord(0, 1, 0));
			v.push_back(Coord(0, 1, 1));
			v.push_back(Coord(0, 1, 2));
			v.push_back(Coord(0, 1, 3));
			v.push_back(Coord(0, 2, 0));
			v.push_back(Coord(0, 2, 1));
			v.push_back(Coord(0, 2, 2));
			v.push_back(Coord(0, 2, 3));
			v.push_back(Coord(0, 3, 0));
			v.push_back(Coord(0, 3, 1));
			v.push_back(Coord(0, 3, 2));
			v.push_back(Coord(0, 3, 3));

			fsm.graphics->setTilesClickable(v);
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};

	struct chooseAction : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Choose action: ";
			fsm.model->currentPlayer()->setDest(NPOS);
			vector<string> v = fsm.model->currentPlayer()->gettActions();
			for (auto& s : v)
				std::cout << s << " ";
			std::cout << std::endl;

			//fsm.graphics->showActions(v);
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};

	struct chooseLoot : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{

		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};

	struct placingCrow : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct offeringLoot : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct requestingLoot : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};
	
	struct chekActionTokens : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Action tokens left: " << fsm.model->currentPlayer()->getActionTokens() << std::endl;
			if (fsm.model->currentPlayer()->getActionTokens() == 0)
			{
				fsm.process_event(ev::no());
				std::cout << "Your turn ends" << std::endl;
			}
			else
			{
				fsm.process_event(ev::yes());
				std::cout << "Keep playing" << std::endl;
			}

		}
	};

	struct askConfirmation : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Are you sure? Yes/No" << std::endl;
		}


		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Okay..." << std::endl;
		}

	};

	struct askConfirmationMove : public msm::front::state<>
	{
		bool wasFlipped;
		Tile * destinationTile;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			// Show the user the tile in question
			destinationTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getDest());
			wasFlipped = destinationTile->isFlipped();
			destinationTile->turnUp();
			if (fsm.model->currentPlayer()->needConfirmationToMove(destinationTile->getPos()) == _DICE)
				std::cout << "Prepare to throw Dice" << std::endl;
			else
			std::cout << "Are you sure? Yes/No" << std::endl;
		}


		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			//Leave everything like before...
			if (wasFlipped == false)
				destinationTile->turnDown();
			std::cout << "Okay..." << std::endl;
		}

	};

	struct throw_Dice : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
			fsm.model->currentPlayer()->dicesLeft2Throw(true);
			fsm.model->currentPlayer()->gettActions();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;

			fsm.model->currentPlayer()->dicesLeft2Throw(false);
			fsm.model->currentPlayer()->gettActions();
		}
	};

	struct beginTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct guardTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Its the guards turn" << std::endl;
			fsm.guardTimer->start();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving guard turn" << std::endl;
			fsm.guardTimer->stop();
		}

	};
	
	struct gameEnded : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (typeid(EVT) == typeid(ev::burglarsWin))
				std::cout << "You win!" << std::endl;
			else if (typeid(EVT) == typeid(ev::gameOver))
				std::cout << "You loose!" << std::endl;
		}
	};


	//----------------------- ACTIONS -----------------------------//
	
	struct doSetInitialPos
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Setting initial position to  " << event.c << std::endl;
			fsm.model->setInitialPosition(event.c);
		}
	};

	struct askb4Move
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to move to " << event.c << std::endl;
			fsm.model->currentPlayer()->setDest(event.c);

			confirmation needInput = fsm.model->currentPlayer()->needConfirmationToMove(event.c);
			if (needInput != _DICE)
			{
				if (needInput == _MOVE)
					fsm.process_event(ev::done());
				else if (needInput == _CANT_MOVE)
					fsm.process_event(ev::no());

				fsm.currentAction = MOVE;
			}
			else
			{
				fsm.currentAction = THROW_DICE;
				fsm.model->currentPlayer()->gettActions();
			}
		}
	};

	struct doNormal	
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			cout << "DO NORMAL" << endl;
			// Move the player
			bool b = fsm.model->currentPlayer()->move(fsm.model->currentPlayer()->getDest());

			if (b == false)
				std::cout << "Cant move!" << std::endl;
			else if (fsm.model->currentPlayer()->getCharacter() != toEnum_characterType("ACROBAT"))
				fsm.model->getBoard()->checkOnePlayer(fsm.model->currentPlayer(), fsm.model->currentPlayer()->getPosition().floor);
			fsm.model->check4Cameras();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			// Move the player
			cout << "DO MOVE" << endl;
			bool b = fsm.model->currentPlayer()->move(fsm.model->currentPlayer()->getDest());

			tileType currentTileType = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getDest())->getType();
			if ( currentTileType == LASER || currentTileType == DEADBOLT )
				fsm.model->currentPlayer()->spentOK();

			if (b == false)
				std::cout << "Cant move!" << std::endl;
			else if (fsm.model->currentPlayer()->getCharacter() != toEnum_characterType("ACROBAT"))
				fsm.model->getBoard()->checkOnePlayer(fsm.model->currentPlayer(), fsm.model->currentPlayer()->getPosition().floor);
			fsm.model->check4Cameras();
			fsm.model->getBoard()->getFloor(fsm.model->currentPlayer()->getPosition().floor)->getGuard()->positionGuard();
			fsm.currentAction = NO_TYPE;
			fsm.model->currentPlayer()->setDest(NPOS);
			fsm.model->currentPlayer()->gettActions();
		}
	};

	struct dontMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			tileType destTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getDest())->getType();
			if (destTile == DEADBOLT) {
				cout << "DONT MOVE" << endl;
				fsm.model->currentPlayer()->removeActionToken();
				fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getDest())->turnUp();
			}
			else	// LASER ROOM
				fsm.model->currentPlayer()->move(fsm.model->currentPlayer()->getDest());

		}
	};

	struct doPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Peeking" << std::endl;
			bool b = fsm.model->currentPlayer()->peek(event.c);
			if (b == false)
				std::cout << "Cant peek!" << std::endl;

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doUseToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.model->currentPlayer()->useToken();

		}
	};

	struct doAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Adding token" << std::endl;
			fsm.model->currentPlayer()->addToken();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct dontAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Throwing dice" << std::endl;
			//fsm.model->currentPlayer()->throwDice();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doCrackSafe
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Tile * currTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getPosition());
			bool b = false;
			if (currTile->is(SAFE))
			{
				std::cout << "Throwing dice" << std::endl;
				b = fsm.model->currentPlayer()->throwDice(event.number);
				if (b)
				{
					fsm.process_event(ev::finishThrow());
					cout << "ended throwing for current action" << endl;
				}
				else
				{
					cout << "can continue throwing dice this action" << endl;
				}
				fsm.currentAction = ROLL_DICE_FOR_LOOT;
			}
		}
	};

	struct dontThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Throwing dice" << std::endl;
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doOpenKeypad
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Trying to open Keypad" << std::endl;
			Tile * destTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getDest());
			bool b = false;
			b =((Keypad *)destTile)->tryToOpen(event.number, fsm.model->currentPlayer());
			if (b)
			{
				fsm.process_event(ev::finishThrow());
				cout << "ended throwing for current action" << endl;
			}
			else
			{

				cout << "can continue throwing dice this action" << endl;
			}
			fsm.currentAction = THROW_DICE;
		}
	};

	struct doFinishThrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.process_event(ev::done());
			fsm.currentAction = MOVE;
		}
	};

	struct doCreateAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Creating Alarm" << std::endl;
			bool b = fsm.model->currentPlayer()->createAlarm(event.c);
			if (b == false)
				std::cout << "Cant create Alarm!" << std::endl;
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doSpyPatrol
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Spying patrol deck" << std::endl;
			fsm.model->spyPatrol(fsm.model->currentPlayer()->getPosition().floor);
				fsm.currentAction = SPY_PATROL;
		}
	};

	struct doStayTop
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Card staying on top of deck" << std::endl;
			fsm.model->stopSpying(fsm.model->currentPlayer()->getPosition().floor);
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doSendBottom
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Spying patrol deck" << std::endl;
			fsm.model->sendBottom(fsm.model->currentPlayer()->getPosition().floor);
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPlaceCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Placing crow token" << std::endl;
			bool b = fsm.model->currentPlayer()->placeCrow(event.c);
			if (b == false)
				std::cout << "Cant place crow token!" << std::endl;
			fsm.currentAction = NO_TYPE;

		}
	};

	struct doPickUpGoldBar
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Pick up loot" << std::endl;
			fsm.model->currentPlayer()->pickUpLoot(GOLD_BAR);
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPickUpKitty
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Pick up loot" << std::endl;
			fsm.model->currentPlayer()->pickUpLoot(PERSIAN_KITTY);
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doAsk
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Ask confirmation" << std::endl;
		}
	};

	struct  doOfferLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Offer loot" << std::endl;
		}
	};

	struct doRequestLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Request loot" << std::endl;
		}
	};

	struct chooseLoot1
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Set loot 1" << std::endl;
			fsm.model->currentPlayer()->setLoot2bTraded(1);
		}
	};

	struct chooseLoot2
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Set loot 2" << std::endl;
			fsm.model->currentPlayer()->setLoot2bTraded(2);
		}
	};

	struct doGetLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Get loot" << std::endl;
			fsm.model->currentPlayer()->receiveLoot(fsm.model->currentPlayer()->getLoot2bTraded());
		}
	};

	struct doGiveLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Get loot" << std::endl;
			fsm.model->currentPlayer()->giveLoot(fsm.model->currentPlayer()->getLoot2bTraded());
		}
	};

	struct doEndTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Player turn ended" << std::endl;
			fsm.model->endTurn();
			fsm.currentAction = NO_TYPE;
		}
	};


	struct needsConfirmation
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			return false;
		}
	};

	struct changeTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Changing turns" << std::endl;
			fsm.model->changeTurn();
			fsm.process_event(ev::passGuard());
			fsm.currentAction = NO_TYPE;

		}
	};

	struct doStartTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Starting Turn" << std::endl;
			if (fsm.model->currentPlayer()->has(PERSIAN_KITTY) || fsm.model->currentPlayer()->has(CHIHUAHUA))
			{
				fsm.currentAction = THROW_DICE;
				fsm.model->currentPlayer()->dicesLeft2Throw(true);
				fsm.model->currentPlayer()->gettActions();
				fsm.model->currentPlayer()->dicesLeft2Throw(false);
			}
			else fsm.process_event(ev::done());
		}
	};

	struct doInitialAction
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Doing initial action" << std::endl;
			if (fsm.model->doInitialAction(event.number))
			{
				fsm.currentAction = THROW_DICE;
				fsm.model->currentPlayer()->gettActions();
			}
			else fsm.process_event(ev::done());
		}
	};

	struct doReallyStartTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Really Starting turn" << std::endl;
			fsm.currentAction = NO_TYPE;
		}
	};

	struct moveGuard
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Moving guard" << std::endl;
			fsm.model->moveGuard();
			if (fsm.model->guardIsMoving() == false)
			{
				fsm.process_event(ev::passGuard());
				fsm.guardTimer->stop();
			}
		}
	};

	struct resetGame
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Reset game" << std::endl;
		}
	};


	struct showMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to move: ";
			vector<Coord> v = fsm.model->currentPlayer()->whereCanIMove();
			Coord::printVec(v);
			std::cout << std::endl;

			fsm.currentAction = MOVE;
			// Distinguir las tiles disponibles para moverse
			fsm.graphics->setTilesClickable(v);
		}
	};

	struct showPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to peek: ";
			vector<Coord> v = fsm.model->currentPlayer()->whereCanIPeek();
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = PEEK;
			// Distinguir las tiles disponibles para moverse
			fsm.graphics->setTilesClickable(v);

		}
	};
	
	struct showAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Alarm can be created on the following tiles: ";
			vector<Coord> v = fsm.model->currentPlayer()->getAdjacentJuicer();
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = CREATE_ALARM;
			// Distinguir las tiles disponibles para crear la alarma
			fsm.graphics->setTilesClickable(v);

		}
	};

	struct showCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Crow token can placed in following tiles: ";
			vector<Coord> v = fsm.model->getTilesXDist(2, fsm.model->currentPlayer());
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = PLACE_CROW;
			// Distinguir las tiles disponibles para poner el Crow token
			fsm.graphics->setTilesClickable(v);

		}
	};

	struct showPickUpLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = PICK_UP_LOOT;
		}
	};

	struct prepAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to add token: ";
			fsm.currentAction = ADD_TOKEN;

		}
	};

	struct prepThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to throw dice: ";
			fsm.currentAction = THROW_DICE;

		}
	};

	struct prepOffer
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to offer loot: ";
			fsm.currentAction = OFFER_LOOT;
			// ACA HAY Q HACER Q SE PUEDAN CLICKEAR LOS LOOTS Q SE PUEDEN OFRECER, PARA HACER ESO HAY Q FIJARSE Q SU BOOL READY SEA TRUE, ( EL UNICO CASO Q TIENE EL BOOL FALSE ES EL PERSIAN KITTY Q NO LO PODES CAMBIAR HASTA Q PASE UN TURNO, PERO DE ESO SE ENCARGA EL MODELO SOLO)

		}
	};

	struct prepRequest
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to request loot: ";
			fsm.currentAction = REQUEST_LOOT;

		}
	};

	///////////// GUARDSSSSS
	struct isMoving
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return 	fsm.currentAction == MOVE;
		}
	};

	struct isPeeking
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PEEK;
		}
	};

	struct isCreatingAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == CREATE_ALARM;
		}
	};

	struct isSpying
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == SPY_PATROL;
		}
	};

	struct isPlacingCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PLACE_CROW;
		}
	};

	struct isAddingToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == ADD_TOKEN;
		}
	};

	struct isThrowingDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == THROW_DICE;
		}
	};

	struct isCrackingSafe
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == ROLL_DICE_FOR_LOOT;
		}
	};

	struct isPickingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PICK_UP_LOOT;
		}
	};

	struct isOfferingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == OFFER_LOOT;
		}
	};

	struct isRequestingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == REQUEST_LOOT;
		}
	};

	// Transition table
	struct transition_table : mpl::vector<
		//       Start					Event					Next				Action            Guard
		//  +-----------+-------------+------------+--------------+--------------+-----------------+-----------+
		
		Row < chooseInitialPos		, ev::coord			, chooseAction			, doSetInitialPos	, none				>,
		Row < chooseAction			, ev::pass			, guardTurn				, doEndTurn			, none				>,
		Row < chooseAction			, ev::movee			, none					, showMove			, none				>,
		Row < chooseAction			, ev::peek			, none					, showPeek			, none				>,
		Row < chooseAction			, ev::coord			, askConfirmationMove	, askb4Move			, isMoving			>,
		Row < chooseAction			, ev::coord			, chekActionTokens		, doPeek			, isPeeking			>,
		Row	< chooseAction			, ev::coord			, chekActionTokens		, doCreateAlarm		, isCreatingAlarm   >,
		Row	< chooseAction			, ev::coord			, chooseAction			, doPlaceCrow		, isPlacingCrow		>,
		Row < chooseAction			, ev::addToken		, chekActionTokens		, doAddToken		, none				>,
		Row < chooseAction			, ev::throwDice		, throw_Dice			, doCrackSafe		, none				>,
		Row < chooseAction			, ev::useToken		, chooseAction			, doUseToken		, none				>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < chooseAction			, ev::offerLoot		, chooseLoot			, prepOffer			, none				>,
		Row < chooseAction			, ev::requestLoot	, chooseLoot			, prepRequest		, none				>,
		Row	< chooseAction			, ev::createAlarm	, none					, showAlarm			, none				>,
		Row < chooseAction			, ev::placeCrow		, none					, showCrow			, none				>,
		Row < chooseAction			, ev::spyPatrol		, askConfirmation		, doSpyPatrol		, none				>,
		Row < chooseAction			, ev::pickUpLoot	, chooseLoot			, showPickUpLoot	, none				>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < askConfirmation		, ev::yes			, chekActionTokens		, doStayTop			, isSpying			>,
		Row < askConfirmation		, ev::no			, chekActionTokens		, doSendBottom		, isSpying			>,
		Row < askConfirmation		, ev::yes			, chekActionTokens		, doThrowDice		, isThrowingDice	>,
		Row < askConfirmation		, ev::no			, chekActionTokens		, dontThrowDice		, isThrowingDice	>,
		Row < askConfirmation		, ev::yes			, chooseAction			, doGiveLoot		, isOfferingLoot	>,
		Row < askConfirmation		, ev::no			, chooseAction			, none				, isOfferingLoot	>,
		Row < askConfirmation		, ev::yes			, chooseAction			, doGetLoot			, isRequestingLoot	>,
		Row < askConfirmation		, ev::no			, chooseAction			, none				, isRequestingLoot	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < askConfirmationMove	, ev::yes			, chekActionTokens		, doMove			, isMoving			>,
		Row < askConfirmationMove	, ev::no			, chekActionTokens		, dontMove			, isMoving			>,
		Row < askConfirmationMove	, ev::done			, chekActionTokens		, doMove			, isMoving			>,
		Row < askConfirmationMove	, ev::throwDice		, throw_Dice			, doOpenKeypad		, isThrowingDice	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < throw_Dice			, ev::throwDice		, throw_Dice			, doOpenKeypad		, isThrowingDice	>,
		Row < throw_Dice			, ev::throwDice		, throw_Dice			, doCrackSafe		, isCrackingSafe	>,
		Row < throw_Dice			, ev::finishThrow	, askConfirmationMove	, doFinishThrow		, isThrowingDice	>,
		Row < throw_Dice			, ev::finishThrow	, chekActionTokens		, none				, isCrackingSafe	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < chooseLoot			, ev::firstLoot		, askConfirmation		, chooseLoot1		, isOfferingLoot	>,
		Row < chooseLoot			, ev::secondLoot	, askConfirmation		, chooseLoot2		, isOfferingLoot	>,
		Row < chooseLoot			, ev::firstLoot		, askConfirmation		, chooseLoot1		, none				>,
		Row < chooseLoot			, ev::secondLoot	, askConfirmation		, chooseLoot2		, none				>,
		Row < chooseLoot			, ev::goldBar		, chooseAction			, doPickUpGoldBar	, isPickingLoot		>,
		Row < chooseLoot			, ev::persianKitty	, chooseAction			, doPickUpKitty		, isPickingLoot		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < chekActionTokens		, ev::no			, guardTurn				, doEndTurn			, none				>,
		Row < chekActionTokens		, ev::yes			, chooseAction			, none				, none				>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn				, ev::movee			, none					, moveGuard			, none				>,
		Row < guardTurn				, ev::passGuard		, beginTurn				, changeTurn		, none				>,
		Row < guardTurn				, ev::gameOver		, gameEnded				, none				, none				>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < beginTurn				, ev::passGuard		, beginTurn				, doStartTurn		, none				>,
		Row < beginTurn				, ev::throwDice		, beginTurn				, doInitialAction	, isThrowingDice	>,
		Row < beginTurn				, ev::done			, chooseAction			, doReallyStartTurn	, none				>,

		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded				, ev::playAgain		, chooseAction			, resetGame			, none				>
		//  +------------+-------------+------------+--------------+--------------+

	> {};
	
	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		std::cout << "no transition from state " << state
			<< " on event " << typeid(event).name() << std::endl;
	}

typedef chooseInitialPos initial_state;
};
// Pick a back-end
typedef msm::back::state_machine<GameState_> GameState;
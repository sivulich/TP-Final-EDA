#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 30 //or whatever you need 

#include <iostream>
// Back-end:
#include <boost/msm/back/state_machine.hpp>
// Front-end:
#include <boost/msm/front/state_machine_def.hpp>
// Functors:
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/euml.hpp>

#include "../Controller/FSM(jullio).h"
#include "../Model/Header Files/Configs.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;


struct GameFSM_ : public msm::front::state_machine_def<GameFSM_>
{
	// Default constructor
	GameFSM_() { };

	// Constructor which receives a pointer to the model
	GameFSM_(GameModel * m)
	{
		model = m;
	};

	// FSM variables
	GameModel * model;
	action_ID currentAction; // Stores current action chosen by player
							 //-------------------------------------------------------------

	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		std::cout << "Entering Burgle Bros Finite State Machine" << std::endl;
		fsm.model->setBoard();

		fsm.model->currentPlayer()->setPosition(Coord(0, 0, 0));
		fsm.model->currentPlayer()->setName(string("Roma"));
		fsm.model->currentPlayer()->setCharacter(RAVEN);

		fsm.model->otherPlayer()->setPosition(Coord(0, 0, 0));
		fsm.model->otherPlayer()->setName(string("Tisan"));
		fsm.model->otherPlayer()->setCharacter(PETERMAN);
	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "Leaving Burgle Bros Finite State Machine" << std::endl;
	}

	// Flags
	struct gameClosed {};


	struct exitState : public exit_pseudo_state<none> {};

	//----------------------- STATES -----------------------------//

	struct chooseAction : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Choose action: ";
			vector<string> v = fsm.model->currentPlayer()->getActions();
			for (auto& s : v)
				std::cout << s << " ";
			std::cout << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{

		}
	};

	
	

	struct creatingAlarm : public msm::front::state<>
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
			std::cout << "Action tokens left: " << fsm.model->currentPlayer()->getActionTokens()<< std::endl;
			if (fsm.model->currentPlayer()->getActionTokens()==0)
			{
				fsm.process_event(no());
				std::cout << "Your turn ends" << std::endl;
			}
			else
			{
				fsm.process_event(yes());
				std::cout << "Keep playing" << std::endl;
			}

		}
	};

	struct askConfirmation : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Are you sure? yes/no" << std::endl;
		}


		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Okay..." << std::endl;
		}

	};
	struct guardTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Its guards turn" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving guard turn" << std::endl;
		}

	};

	struct gameEnded : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (typeid(EVT) == typeid(burglarsWin))
				std::cout << "You win!" << std::endl;
			else if (typeid(EVT) == typeid(gameOver))
				std::cout << "You loose!" << std::endl;
		}
	};





	// Playing state is always active, unless game is paused or there is an error
	struct playing : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Start playing" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Stop playing" << std::endl;
		}

	};

	struct paused : public msm::front::interrupt_state<mpl::vector<resume, close>>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Paused" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Resuming" << std::endl;
		}

	};

	struct error : public msm::front::interrupt_state<errorHandled>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Entering Error" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving Error" << std::endl;
		}

	};

	struct exit : public msm::front::terminate_state<>
	{
		typedef mpl::vector1<gameClosed> flag_list;
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Entering exit" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving exit" << std::endl;
		}

	};


	//----------------------- ACTIONS -----------------------------//

	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Moving to  " << event.c << std::endl;
			bool b = fsm.model->currentPlayer()->move(event.c);
			if(b==false)
				std::cout << "Cant move!" << std::endl;
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
			
		}
	};

	struct doUseToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Using token" << std::endl;
		}
	};

	struct doAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Adding token" << std::endl;
		}
	};

	struct doThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Throwing dice" << std::endl;
		}
	};

	struct doCreateAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Creating alarm" << std::endl;
		}
	};

	struct doSpyPatrol
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Spying patrol deck" << std::endl;
		}
	};

	struct doPlaceCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Placing crow token" << std::endl;
		}
	};

	struct doPickUpLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Pick up loot" << std::endl;
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
			fsm.model->currentPlayer()->resetActionTokens();
			fsm.model->changeTurn();
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
				fsm.process_event(pass());
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

	struct doRender
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.model->print();
		}

	};

	struct showMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to move: ";
			Coord::printVec(fsm.model->currentPlayer()->whereCanIMove());
			std::cout << std::endl;
			
			fsm.currentAction = MOVE;
			//
		}
	};


	struct showPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to peek: ";
			Coord::printVec(fsm.model->currentPlayer()->whereCanIPeek());
			std::cout << std::endl;
			fsm.currentAction = PEEK;
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

	
	// Transition table for main FSM
	struct transition_table : mpl::vector<
		//       Start        Event         Next         Action         Guard
		//  +------------+-------------+------------+--------------+--------------+
		Row < chooseAction, pass, guardTurn, none, none       >,
		Row < chooseAction, movee, none, showMove, none       >,
		Row < chooseAction, peek, none, showPeek, none       >,
		Row < chooseAction, coord, chekActionTokens, doMove, isMoving       >,
		Row < chooseAction, coord, chekActionTokens, doPeek, isPeeking       >,

		Row < chekActionTokens, no, guardTurn,none , none     >,
		Row < chekActionTokens, yes, chooseAction, none, none     >,
		//Row < chooseAction,   throwDice   , throwingDice,    none,        none       >,
		//Row < chooseAction,   useToken    , usingToken,      none,        none       >,
		//Row < chooseAction,   addToken    , addingToken,     none,        none       >,
		//Row < chooseAction,   offerLoot   , offeringLoot,    none,        none       >,
		//Row < chooseAction,   requestLoot , requestingLoots , none,        none       >,
		//Row < chooseAction,   createAlarm , creatingAlarm   ,   none,        none       >,
		//Row < chooseAction,   spyPatrol   , guardTurn,       none,        none       >,
		//Row < chooseAction,   placeCrow   , guardTurn,       none,        none       >,
		//Row < chooseAction,   pickUpLoot  , guardTurn,       none,        none       >,


		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn, movee, none, moveGuard, none     >,
		Row < guardTurn, pass, chooseAction, changeTurn, none     >,
		Row < guardTurn, gameOver, gameEnded, none, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded, playAgain, chooseAction, resetGame, none     >,
		//  +------------+-------------+------------+--------------+--------------+




		//--------------------------Orthogonal region-----------------------------//
		//  +------------+-------------+------------+--------------+--------------+
		Row <   playing, close, exit, none, none     >,
		Row <   playing, errorReceived, error, none, none     >,
		Row <   playing, pause, paused, none, none     >,
		Row <   playing, render, none, doRender, none     >,

		//  +------------+-------------+------------+--------------+--------------+
		Row <   paused, resume, playing, none, none     >,
		Row <   paused, close, exit, none, none     >,
		Row <   paused, render, paused, doRender, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row <   error, errorHandled, playing, none, none     >,
		Row <   error, close, exit, none, none     >,
		Row <   error	 , render, none, doRender, none     >
		//  +------------+-------------+------------+--------------+--------------+
	> {};

	typedef mpl::vector<playing, chooseAction> initial_state;

	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		std::cout << "no transition from state " << state
			<< " on event " << typeid(event).name() << std::endl;
	}
};
// Pick a back-end
typedef msm::back::state_machine<GameFSM_> GameFSM_imp;


GameController::GameController(GameModel * m) : FSM(new GameFSM_imp(m))
{

}

void GameController::start()
{
	static_pointer_cast<GameFSM_imp>(FSM)->start();
	// HACER TODAS LAS OTRAS COSAS NECESARIAS AL COMENZAR EL JUEGO
};


void GameController::stop()
{
	static_pointer_cast<GameFSM_imp>(FSM)->stop();
	// HACER TODAS LAS OTRAS COSAS NECESARIAS AL TERMINAR EL JUEGO
};

bool GameController::isRunning()
{
	return static_pointer_cast<GameFSM_imp>(FSM)->is_flag_active<GameFSM_imp::gameClosed>() == false;
};


void GameController::getInput()
{
	// EN LA VERSION CON GRAFICOS ACA HAY QUE RECIBIR EVENTOS DE MOUSE, TECLADO, Y TIMERS 
	// (TIMERS DE RENDER, PARA MOVER EL GUADRIA, ETC...)
	// 
	// LOS CLICKS SE MANDAN A LA VISTA QUE DEVUELVE LO QUE SE APRETO Y ESTO SE INTERPRETA COMO 
	// UN EVENTO
	cin >> s;
}

void GameController::processEvent()
{
	


	if (s == "MOVE")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(movee());
	else if (s == "PEEK")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(peek());
	else if (s == "TROW_DICE")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(throwDice());
	else if (s == "ADD_TOKEN")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(addToken());
	else if (s == "UDE_TOKEN")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(useToken());
	else if (s == "PASS")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(pass());
	else if (s == "PAUSE")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(pause());
	else if (s == "RESUME")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(resume());
	else if (s == "GAME_OVER")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(gameOver());
	else if (s == "BURGLARS_WIN")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(burglarsWin());
	else if (s == "PLAY_AGAIN")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(playAgain());
	else if (s == "CLOSE")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(close());
	else if (s == "ERROR_RECEIVED")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(errorReceived());
	else if (s == "ERROR_HANDLED")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(errorHandled());
	else if (s == "YES")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(yes());
	else if (s == "NO")
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(no());
	else if (s.substr(0, 5) == "COORD" && s.length()==8)
	static_pointer_cast<GameFSM_imp>(FSM)->process_event(coord(Coord(s[5]-'0'-1, s[6]-'A', s[7]-'0'-1)));
	else if (s=="PRINT")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(render());

}
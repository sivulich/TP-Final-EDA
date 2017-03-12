#include "../../Header Files/Tiles/Motion.h"
#include "../../Header Files/Tiles/ComputerRoomM.h"


Motion::~Motion()
{
}


void Motion::enter(PlayerInterface * player) {
	Tile::enter(player);
	arm();
}

void Motion::exit(PlayerInterface * player) {
	if (isArmed())
	{
		setAlarm(true);
		disarm();
	}
}

vector<string> Motion::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));

	if (isArmed() && computerRoom->getHackTokens() > 0)
		actions.push_back("USE_TOKEN");		// if you have an action, you can use a token to disarm the system
	return actions;
}

void Motion::doAction(string action, PlayerInterface * player) {
	
	if (action == "USE_TOKEN")
	{
		computerRoom->removeToken();
		disarm();
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
	}
}

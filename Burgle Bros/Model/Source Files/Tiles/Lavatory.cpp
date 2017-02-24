#include "../../Header Files/Tiles/Lavatory.h"

Lavatory::~Lavatory()
{
}

bool Lavatory::hide() {
	if (stealthTokens > 0) {
		stealthTokens--;
		DEBUG_MSG("You managed to hide in the stalls.");
		return true;
	}
	else {
		DEBUG_MSG("No more stealth tokens.");
		return false;
	}
}
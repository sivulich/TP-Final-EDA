#pragma once
#include "./Observer.h"
#include <Player.h>
#include <Configs.h>

#include "./BoardObserver.h"
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Text.h"

class PlayerObserver :public Observer
{
public:
	PlayerObserver(Player* p, Container * c, Container* hudCont);
	virtual void update()override;
private:
	// Observed object
	Player* player;
	Coord lastPos;
	bool isPlaying;

	pair<int, int> positions[3][4][4];
	// Graphic objects
	Container* parentCont;
	Container* hudCont;
	Image* playerCard;
	Image * infoButton;
	Image* characterFigure;
	Image* characterFigurePlaying;
	Image * passButton;
	Text * actionTokens;
	Image* token;
	Text * stealthTokens;
	Text * name;
};
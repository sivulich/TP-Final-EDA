#pragma once
#include <GameModel.h>
#include <alx.hpp>
#include "../src/Graphic Objects/Screen.h"
#include "../src/Graphic Objects/Container.h"
#include "../src/Observers/Observer.h"
#include "../src/Observers/BoardObserver.h"
#include "../src/Observers/LocalPlayerObserver.h"
#include "../src/Observers/RemotePlayerObserver.h"

// HEREDA DE OBSERVER??
class GameGraphics : public Observer
{
public:
	GameGraphics(GameModel * model);
	~GameGraphics();

	// Check Allegro initialization
	bool initOK() { return initOK_; };

	// Render objects on screen
	void render();

	// Called by game model when something is modified
	//IMPLEMENTAR
	void update();

	// Interacts upon a mouse movement, returns objet name
	bool hover(int y, int x);

	// Interacts upon a click down, returns objet name
	string click(int y, int x);

	// Interacts upon a click up, returns objet name
	void unclick(int y, int x);


	// Set as clickable the given tiles (and illuminate them), and not clickable the other ones.
	void setTilesClickable(vector<Coord> tiles);

	// Return screen event source (for controller)
	EventSource getScreenEventSource() { return screen->getDisplay()->getEventSource(); }

private:
	bool initOK_;
	GameModel * model;
	// Window, allegro display
	Screen* screen;
	Container* cont;
	BoardObserver* board;
	LocalPlayerObserver * pl;
	RemotePlayerObserver* pl2;
};


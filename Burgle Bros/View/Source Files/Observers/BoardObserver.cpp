#include "../../Header Files/Observers/BoardObserver.h"

BoardObserver::BoardObserver(Board* b, Container* c)
{
	parent = c;
	board = b;
	toDraw = new Container(parent->getHeight() * 2.0 / 3.0, parent->getHeight() * 4.0 / 3.0);
	toDraw->setName(string("Board"));
	toDraw->setPosition(parent->getHeight() / 12.0, 0);
	for (int i = 0; i < 3; i++)
	{
		floors[i] = new FloorObserver((*b)[i], toDraw);
	}
	parent->addObject(toDraw);
	board->attach(this);
}

void
BoardObserver::update()
{
	
}
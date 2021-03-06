#include "./GuardObserver.h"

#include "../Animations/MoveAnimation.h"
#include "../Animations/FadeAnimation.h"
#include "../Animations/FadeInOutAnimation.h"
#include "../Animations/DelayAnimation.h"
GuardObserver::GuardObserver(Guard* g, Container* board, int floorNumber)
{
	boardCont = board;
	guard = g;
	this->floorNumber = floorNumber;
	guardIm = new Image(string("./Graphics/Images/Guard.png"));
	guardIm->setSize(GUARD_SIZE, GUARD_SIZE);
	guardIm->setPosition(GUARD_DECK_YPOS, GUARD_DECK_XPOS[floorNumber] - TILE_SIZE);
	guardIm->setClickable(false);
	guardIm->setHoverable(false);
	boardCont->addObject(guardIm);

	dices.resize(7);
	for (int i = 1; i <= 6; i++)
	{
		dices[i] = new Image(string("./Graphics/Images/Dices/White ") + to_string(i) + string(".png"));
		dices[i]->setSize(DICE_SIZE, DICE_SIZE);
		dices[i]->setHoverable(false);
		dices[i]->setClickable(false);
		dices[i]->setVisible(false);
		boardCont->addObject(dices[i]);
	}

	lastSpeed = g->getSpeed();
	lastPos = NPOS;
	guard->attach(this);
}

GuardObserver::~GuardObserver()
{
	DEBUG_MSG("DELETING FLOOR" << floorNumber);
	//delete guardIm;

	for (int i = 1; i <= 6; i++)
		delete dices[i];
}

void GuardObserver::update()
{
	// Update position
	Coord pos = guard->getPos();
	if (pos != lastPos)
	{
		std::pair<int, int> target = std::pair<int, int>((int)(FLOOR_YPOS + TILE_YPOS[pos.row][pos.col] + (TILE_SIZE - GUARD_SIZE) / 2), (int)(FLOOR_XPOS[pos.floor] + TILE_XPOS[pos.row][pos.col] + (TILE_SIZE - GUARD_SIZE) / 2));
		if (lastPos == NPOS)
		{
			guardIm->addAnimation(new FadeInOutAnimation(target, GUARD_MOVE_SPEED * 3));
			//guardIm->addAnimation(new DelayAnimation(1));
			boardCont->addObject(dices[guard->getSpeed()]);
			lastTarget = guard->getTarget();
			int i = guard->getTarget().row;
			int j = guard->getTarget().col;
			dices[lastSpeed]->setVisible(false);
			dices[lastSpeed]->setPosition((int)(FLOOR_YPOS + TILE_YPOS[i][j] + (TILE_SIZE - DICE_SIZE) / 2),(int) (FLOOR_XPOS[pos.floor] + TILE_XPOS[i][j] + (TILE_SIZE - DICE_SIZE) / 2));
		}
		else
			guardIm->addAnimation(new MoveAnimation(target, GUARD_MOVE_SPEED));
		lastPos = pos;
	}

	// Update dice
	//if (lastSpeed != guard->getSpeed() || lastTarget != guard->getTarget())
	{
		//for (int i = 1; i <= 6; i++)
			//dices[i]->setVisible(false);
		dices[lastSpeed]->setVisible(false);
		lastSpeed = guard->getSpeed();
		lastTarget = guard->getTarget();
		dices[lastSpeed]->setVisible(true);
		int i = guard->getTarget().row;
		int j = guard->getTarget().col;
		dices[lastSpeed]->setPosition((int)(TILE_YPOS[i][j] + (TILE_SIZE - DICE_SIZE) / 2), (int)(FLOOR_XPOS[pos.floor] + TILE_XPOS[i][j] + (TILE_SIZE - DICE_SIZE) / 2));

		
	}
}

void GuardObserver::reset()
{
	if (guardIm != nullptr)
	{
		boardCont->removeObject(guardIm);
		boardCont->addObject(guardIm);
	}
};
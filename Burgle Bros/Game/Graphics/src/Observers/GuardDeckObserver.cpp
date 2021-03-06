#include "./GuardDeckObserver.h"
#include "../Animations/MoveAnimation.h"
#include "../Animations/FlipAnimation.h"
#include "../Animations/FadeAnimation.h"
GuardDeckObserver::GuardDeckObserver(Floor* f, Container* board)
{
	deck = f->getPatrolDeck();
	floor = f;
	boardCont = board;
	deckClicked = false;
	discardedCount = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			string des = string("A") + to_string(i + 1);
			des[0] += j;
			cards[i][j] = new Image(string("./Graphics/Images/Patrol/PC ") + des + string(".png"));
			cards[i][j]->setSize(TILE_SIZE, TILE_SIZE);
			//cards[i][j]->setHoverable(false);
			cards[i][j]->setPosition(GUARD_DECK_YPOS, GUARD_DECK_XPOS[floor->number()] + TILE_SIZE + TILE_SEPARATION);
			cards[i][j]->setName(string("PC") + des + string("F") + to_string(floor->number()));
			cards[i][j]->setObserver(this);
		}
	}
	back = new Image(string("./Graphics/Images/Patrol/PC R.png"));
	back->setSize(TILE_SIZE, TILE_SIZE);
	back->setPosition(GUARD_DECK_YPOS, GUARD_DECK_XPOS[floor->number()]);
	back->setHoverable(false);
	back->setClickable(false);
	boardCont->addObject(back);
	lastCard = "";
	deck->attach(this);
	slide = new alx::Sample("../Game/Sound/SLIDE.wav");
}

GuardDeckObserver::~GuardDeckObserver()
{
	DEBUG_MSG("DELETING GUARD DECK");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			delete cards[i][j];

	delete back;
	delete slide;
}

void GuardDeckObserver::showTop()
{
	int i = deck->topCard()->getDescription()[1] - '1';
	int j = deck->topCard()->getDescription()[0] - 'A';
	cards[i][j]->setPosition(GUARD_DECK_YPOS, GUARD_DECK_XPOS[floor->number()]);
	//cards[i][j]->setAlpha(0.0);
	//cards[i][j]->addAnimation(new FadeAnimation(0.0, 1.0, 1.0));
	//cards[i][j]->addAnimation(new DelayAnimation(1.0));
	cards[i][j]->addAnimation(new FlipAnimation(cards[i][j],0.2));
	boardCont->addObject(cards[i][j]);
}

void GuardDeckObserver::hideTop()
{
	int i = deck->topCard()->getDescription()[1] - '1';
	int j = deck->topCard()->getDescription()[0] - 'A';
	boardCont->removeObject(cards[i][j]);
	cards[i][j]->setPosition(GUARD_DECK_YPOS, GUARD_DECK_XPOS[floor->number()] + TILE_SIZE + TILE_SEPARATION);
}

void GuardDeckObserver::update()
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	if ((unsigned)discardedCount > deck->getDiscarded().size())
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				boardCont->removeObject(cards[i][j]);
		discardedCount = deck->getDiscarded().size();

	}

	// Update the top card of the deck
	else if (deck->getDiscarded().empty() == false && lastCard != deck->getDiscarded().back()->getDescription())
	{
		lastCard = deck->getDiscarded().back()->getDescription();

		if (deck->getDiscarded().size() == 1)
		{
			cards[lastCard[1] - '1'][lastCard[0] - 'A']->setAlpha(0.0);
			cards[lastCard[1] - '1'][lastCard[0] - 'A']->addAnimation(new FadeAnimation(0.0, 1.0, 1.0));
			cards[lastCard[1] - '1'][lastCard[0] - 'A']->addAnimation(new DelayAnimation(1.0));
		}

		boardCont->addObject(cards[lastCard[1] - '1'][lastCard[0] - 'A']);
		discardedCount++;

		// Update the reverse image of the deck
		if (deck->getDeck().empty() == true)
			boardCont->removeObject(back);
		else if (boardCont->contains(back) == false)
			boardCont->addObject(back);
	}

	// Add animation if deck is clicked
	if ((lastCard.size()>0) && (state.buttons&1) != deckClicked &&  cards[lastCard[1] - '1'][lastCard[0] - 'A']->isClicked() != deckClicked) //&& state.buttons & 1 != deckClicked) //viewDeck->isClicked())//
	{
		deckClicked = !deckClicked;
		slide->play(1, 0, 3, ALLEGRO_PLAYMODE_ONCE);
		if (deckClicked == true)
		{
			//boardCont->removeObject(cards[lastCard[0] - 'A'][lastCard[1] - '1']);
			for (auto& card : deck->getDiscarded())
			{
				int i = card->getDescription()[1] - '1';
				int j = card->getDescription()[0] - 'A';
				std::pair<int, int>target = std::pair<int, int>((int)TILE_YPOS[i][j] + FLOOR_YPOS, (int)(TILE_XPOS[i][j] + FLOOR_XPOS[floor->number()]));
				cards[i][j]->deleteAnimation();
				cards[i][j]->addAnimation(new MoveAnimation(target, 0.3));
				//		boardCont->addObject(cards[i][j]);
			}
		}
		else
		{
			for (auto& card : deck->getDiscarded())
			{
				int i = card->getDescription()[1] - '1';
				int j = card->getDescription()[0] - 'A';
				std::pair<int, int>target = std::pair<int, int>((int)GUARD_DECK_YPOS, (int)(GUARD_DECK_XPOS[floor->number()] + TILE_SIZE + TILE_SEPARATION));
				cards[i][j]->deleteAnimation();
				cards[i][j]->addAnimation(new MoveAnimation(target, 0.3));
			}
		}
	}
}
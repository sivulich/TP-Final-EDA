#include "../../Header Files/Observers/GameObserver.h"

GameObserver::GameObserver(GameModel* g, int sHeight)
{
	game = g;
	screen= new Screen(sHeight, sHeight * 1280.0 / 720.0, string("../View/Images/BackGround.jpg"), false);
	screen->backgroundProperties(0, 0, double(sHeight) / 1080.0);
	cont= new Container(sHeight, sHeight * 1280.0 / 720.0);
	board= new BoardObserver(&game->getBoard(), cont);
	
	pl=new LocalPlayerObserver(game->getPlayer1(), board, cont);
	pl2 = new RemotePlayerObserver(game->getPlayer2(), board, cont);
	screen->addObject(cont);
	cont->setPosition(0, 0);
	game->attach(this);
	al_install_keyboard();
	al_install_mouse();
	events << Keyboard::getEventSource() << Mouse::getEventSource() << screen->getDisplay()->getEventSource();
}

string
GameObserver::input()
{
	if (events.isEmpty()==false)
	{
		Event event = events.getEvent();
		switch (event.getType())
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				return "exit";
			}
			case ALLEGRO_EVENT_MOUSE_AXES:
			{
				screen->overYou(event.getMouseY(), event.getMouseX());
				return "";
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			{
				return screen->click(event.getMouseY(), event.getMouseX());
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			{
				screen->unClick(event.getMouseY(), event.getMouseX());
				return "";
			}
			case ALLEGRO_EVENT_KEY_DOWN:
			{
				if (event.getKeyboardKeycode() == ALLEGRO_KEY_ESCAPE)
					return "exit";
				// Si se aprieta otra tecla no se la tiene que pasar a la screen??
			}
		}
	}
	return "";
}

void
GameObserver::update()
{
	board->update();
	screen->draw();
}
GameObserver::~GameObserver()
{
	screen->removeObject(cont);
	cont->clear();
	delete board;
	delete pl;
	delete screen;
	delete cont;
}
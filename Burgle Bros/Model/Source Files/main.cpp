#include "../Header Files/GameModel.h"

#include "../../Model/Header Files/Coord.h"
int main(void)
{/*
	GameModel model;
	string s1;

	model.print();
	while (1)
	{

		cin >> s1;
		model.input(s1);
		model.runStep();
	}
	return 0;*/
	int hola;
	Board b;
	b[1]->addAlarm(Coord(1, 2, 2));
	b[1]->getGuard()->Move();
	while (1);
}
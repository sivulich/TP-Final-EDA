

#include "../Header Files/Screen.h"
#include "../Header Files/Image.h"
#include "../Header Files/Container.h"
#include "../Header Files/Button.h"
#include "../../Controller/Header Files/localControler.h"
#include "../Header Files/Textbox.h"
#include "../../Model/Header Files/Board.h"
#include "../Header Files/Allegro.h"
#include "../Header Files/Observers/BoardObserver.h"
int main(void)
{
	Allegro al;
	if (al.wasInitOk() == true)
	{
		Screen screen(720, 1280, string("../View/Images/BackGround.jpg"));
		screen.backgroundProperties(0, 0, 720.0 / 1080.0);
		Container cont(720, 1280);
		Board board;
		localControler control(&screen);
		board.setBoard();
		board.setWalls();
		for (int i = 0; i < 3; i++)
		{
			board[i].setNumber(i);
			board[i].getPatrolDeck()->createDeck(i);
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
					board.getTile(Coord(i, j, k))->flip();
			}
		}
		
		BoardObserver obs(&board, &cont);
		screen.addObject(&cont);
		string in;
		Timer time(1.0 / 30.0);
		time.start();
		long long c=time.getCount();
		while (in != "exit")
		{
			in = control.input();
			if (in != "")
			{
				cout << "Input " << in << endl;
				if(in == "PC R")
					board[0].getPatrolDeck()->discardTop();
			}
			if (c < time.getCount())
			{
				c = time.getCount();
				obs.update();
				screen.draw();
			}
		}
			
	}
		
	return 0;
}
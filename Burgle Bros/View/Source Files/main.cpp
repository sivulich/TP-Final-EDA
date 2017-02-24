
#include "../Header Files/Screen.h"
#include "../Header Files/Image.h"
#include "../Header Files/Container.h"
#include "../Header Files/Button.h"
#include "../Controller/Header Files/localControler.h"
#include "../Header Files/Textbox.h"
#include "../Model/Header Files/Board.h"
#include "../Header Files/Allegro.h"

int main(void)
{
	Allegro al;
	if (al.wasInitOk() == true)
	{
		string background = "background.jpg";
		string hud = "hudTest.png";
		string name = "testChar";
		string peek = "peek";
		string move = "move";
		string font = "Raleway-Black.ttf";
		Screen mainScreen(720, 1280, background);
		Container testCont(hud);
		Image testImage(name + ".jpg");
		Image peekImage(peek + ".png");
		Image moveImage(move + ".png");

		Textbox tbox(10, 10, font, 50, 20);


		Timer draw(1.0 / 60.0);
		moveImage.setScale(0.7);
		moveImage.setPosition(185, 420);
		moveImage.setBorderVisible(true);
		testCont.addObject(&moveImage);
		peekImage.setScale(0.3);
		peekImage.setPosition(170, 600);
		testCont.addObject(&peekImage);
		testCont.addObject(&testImage);
		testCont.setBorderVisible(true);
		testImage.setPosition(100, 30);
		testImage.setScale(0.51);
		testCont.setScale(0.666);
		testCont.setPosition(473, 0);
		mainScreen.addObject(&testCont);
		mainScreen.backgroundProperties(0, 0, 0.66666);
		mainScreen.addObject(&tbox);
		testCont.setDragable(true);
		
		Board b;
		localControler control(&mainScreen);
		string in;
		Image* test = nullptr;
		int count = 0;
		draw.start();
		while ((in = control.input()) != "exit")
		{
			if (in != "")
				cout << "Input was " << in << endl;
			if (in == (name + "zoom"))
			{
				mainScreen.removeObject(test);
				delete test;
				test = nullptr;
			}
			if (in == name && test == nullptr)
			{

				test = new Image(name + ".jpg");
				test->setPosition(50, 350);
				test->setName(name + "zoom");
				mainScreen.addObject(test);
			}
			if (count < draw.getCount())
			{
				mainScreen.draw();
				count = draw.getCount();
			}
		}
	}
	
		
	return 0;
}
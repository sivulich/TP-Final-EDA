
#include "Screen.h"
#include "Image.h"
#include "Container.h"
#include "Button.h"
#include "localControler.h"

int main(void)
{
	string background = "background.jpg";
	string name = "Button";
	Screen mainScreen(720, 1280, background);
	Container testCont(400, 400);
	testCont.setPosition(400, 400);
	vector<string> names = { "button.png","button_pressed.png" };
	Button testButton(name);
	Button testButton2(name);
	testButton.setImages(names);
	testButton2.setImages(names);
	testCont.addObject(&testButton);
	testButton2.setPosition(100, 100);
	mainScreen.addObject(&testCont);
	mainScreen.addObject(&testButton2);
	mainScreen.backgroundProperties(0, 0, 0.66666);



	localControler control(&mainScreen);
	while (control.input()!="exit")
	{
		mainScreen.draw();
	}
		
	return 0;
}
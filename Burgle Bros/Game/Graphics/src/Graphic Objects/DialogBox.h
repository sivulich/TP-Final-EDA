#pragma once

#include <object.h>
#include "Image.h"
#include "Text.h"
#include "Container.h"
#include "../../Model/include/Configs.h"
#include <string>
#include <Font.hpp>
#include <alx.hpp>

class DialogBox : public Object
{
public:
	enum type { OK_MSG, YES_NO_MSG, ERR_MSG, CANCEL_MSG,TEMPORAL_INFO,DICE_MSG };
	enum position { TOP, MIDDLE, BOTTOM };
	DialogBox(type t, std::string content, Container * c, bool blur = true, int position = MIDDLE);
	DialogBox(std::string content, Container * c, bool bl = true, int position = MIDDLE, vector<unsigned int>& d = vector<unsigned int>());
	DialogBox(std::string content, Container * c, bool bl = true, int position = MIDDLE, vector<lootType>& d = vector<lootType>());
	void draw(Bitmap* target);
	std::string click(int y, int x);
	void unClick(int y, int x);
	bool overYou(int y, int x);
	void remove();

private:
	//Sound
	alx::Sample * dice;
	bool played;
	bool diceBox;

	Object * blur;
	Container * box;
	Object * button1;
	Object * button2;
	Object * text1;
	Object* text2;
	Object * message;
	Container * parent;
	Container * dices;
};

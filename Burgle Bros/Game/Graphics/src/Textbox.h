#pragma once
#include "Object.h"

class Textbox :public Object {
public:
	/** Initializes the textbox
	    @param x X coordinate in the parent
	    @param y Y coordinate in the parent
	    @param path Path to the font to load
	    @param fSize Font size in pixels
	    @param max Max letters to input in this textbox
	*/
	Textbox(int x, int y, string& path, int fSize,int max);
	/** Draws the textbox to the target
		@param target Target to draw the textbox in
	*/
	void draw(Bitmap* target);
	/** If the textbox is clicked it will return its name
		@param y Mouse y coordinate
		@param x Mouse x coordinate
	*/
	string click(int y, int x);
	/** Tests whether to unclick or not
		@param y Mouse y coordinate
		@param x Mouse x coordinate
	*/
	void unClick(int y, int x);
	/** If over the textbox return true
		@param y Mouse y coordinate
		@param x Mouse x coordinate
	*/
	bool overYou(int y, int x);
	/** If true, lets you input text until the textbox is full
	*/
	void fitText(bool b) { fitToBox = b; };
	~Textbox() { delete font; delete titilate; };
private:
	EventQueue queue;
	Event event;
	Font* font;
	string buffer;
	unsigned long long count;
	bool fitToBox;
	Timer* titilate;
	int size;
};
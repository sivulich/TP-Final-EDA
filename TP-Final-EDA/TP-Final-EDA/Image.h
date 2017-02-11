#pragma once

#include "object.h"
/*Class used to draw an image, it mantains the original aspect ratio*/
class Image :public object {
public:
	/*Draws the image to the given bitmap*/
	void draw(ALLEGRO_BITMAP* target);
	/*Set image to draw*/
	void setImage(string& path) { this->im = al_load_bitmap(path.c_str()); h = al_get_bitmap_height(im);w = al_get_bitmap_width(im);};
	/*Sets scale for the image to be drawn, it mantains aspect ratio*/
	void setScale(double s) { this->scale = s; };
private:
	ALLEGRO_BITMAP* im;
};
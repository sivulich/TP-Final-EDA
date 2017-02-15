#include "object.h"

object::object()
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	clicked = false;
	hover = false;
	scale = 1;
	h = 0;
	w = 0;
	x = 0;
	y = 0;
}
object::object(string name, int x, int y, int h, int w, double scale)
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	clicked = false;
	hover = false;
	this->scale = scale;
	this->h = h;
	this->w = w;
	this->x = x;
	this->y = y;
	this->name = name;
}
string
object::click(int y, int x)
{
	if ( clickable == true )
	{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + scale*this->w))
		{
			//check for y
			if (this->y <= y && y <= (this->y + scale* this->h))
			{
				clicked = true;
				return this->name;
			}
		}
	}
	return "";
}

void
object::unClick()
{
	clicked = false;
}

bool
object::overYou(int y, int x)
{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
		{
			if(hoverable == true)
				hover = true;
			return true;
		}
		else
		{
			clicked = false;
			hover = false;
			return false;
		}
}
void
object::drag(int y, int x)
{
	if (dragable == true)
	{
		this->x = x;
		this->y = y;
	}
}



void
object::draw(Bitmap* target)
{
	target->setTarget();
	al_draw_rectangle(x, y, x + w*scale, y + h*scale, al_map_rgb(255, 0, 0), 10);
}
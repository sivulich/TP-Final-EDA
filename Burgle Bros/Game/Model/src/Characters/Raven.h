#pragma once
#include "Character.h"
class Raven :
	public Character
{
public:
	Raven() : Character(RAVEN) {};
	~Raven();
	virtual string getAction(PlayerInterface * player)override;
private:
};


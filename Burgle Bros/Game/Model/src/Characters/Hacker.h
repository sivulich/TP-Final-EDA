#pragma once
#include "Character.h"
class Hacker :	public Character
{
public:
	Hacker() : Character(HACKER) {};
	~Hacker();
	virtual string getAction(PlayerInterface * player) override;
};


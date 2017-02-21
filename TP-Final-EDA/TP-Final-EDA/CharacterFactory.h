#pragma once
#include "Character.h"
#include "Acrobat.h"
#include "Juicer.h"
#include "Hacker.h"
#include "Spotter.h"
#include "Hawk.h"
#include "Raven.h"
#include "Peterman.h"

class CharacterFactory
{
public:
	CharacterFactory();
	~CharacterFactory();
	static Character * newCharacter(characterType type);
};


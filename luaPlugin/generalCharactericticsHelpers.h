#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace generalCharactericticsHelpers
{
	anchillary* getAnchillary(generalCharacterictics* character, int index);
	int addAnchillary(generalCharacterictics* character, std::string anchName);
	void removeAnchillary(generalCharacterictics* character, anchillary* anch);



	int getAge(generalCharacterictics* character);
	void setAge(generalCharacterictics* character,int age);

	bool isAlive(generalCharacterictics* character);
	void setAsHeir(generalCharacterictics* character,bool isJustSet);
};


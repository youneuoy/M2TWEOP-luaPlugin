#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace gameHelpers
{
	UINT32 getFactionsCount();
	factionStruct* getFaction(int index);

	general* createCharacter(const char* type, factionStruct* fac, int age, const char* name, const char* name2, int subFaction, const char* portrait, int x, int y);
	stackStruct* createArmy(general* character);
	unit* createUnitN(const char* type, int facNum, int exp, int arm, int weap);
	unit* createUnitIdx(int eduIdx, int facNum, int exp, int arm, int weap);
};


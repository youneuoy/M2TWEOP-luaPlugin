#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace stackStructHelpers
{
	unit* getUnit(const stackStruct* army, int index);
	general* getCharacter(const stackStruct* army, int index);
	settlementStruct* findInSettlement(const stackStruct* army);
	fortStruct* findInFort(const stackStruct* army);
	int addUnitToArmy(stackStruct* army, unit*un);
};


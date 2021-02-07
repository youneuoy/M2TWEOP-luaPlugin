#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace generalHelpers
{
	void moveToTile(general* gen, int x, int y);
	void reposition(general* gen, int x, int y);
	void siegeSettlement(general* gen, settlementStruct* sett);

	void killGeneral(general* gen);
	void setBodyguard(general* gen,unit*un);
	void setMovepoints(general* gen, float movepoints);
	float getMovepoints(const general* gen);
};


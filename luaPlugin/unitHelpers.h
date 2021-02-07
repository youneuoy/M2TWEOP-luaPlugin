#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace unitHelpers
{
	void setMovepoints(unit* un,float movepoints);
	void setSoldiersCount(unit* un,int number);
	void killUnit(unit* un);
	void setUnitParams(unit* un, int exp, int armor, int weap);
	float getMovepoints(const unit* un);
};


#include "unitHelpers.h"
#include "plugData.h"
namespace unitHelpers
{
	void setMovepoints(unit* un, float movepoints)
	{
		un->movePoints = movepoints;
		if (un->general == nullptr)return;

		un->general->movepoints1 = movepoints;
		un->general->movepoints2 = movepoints;
	}
	void setSoldiersCount(unit* un, int number)
	{
		(*(*plugData::data.funcs.setSoldiersCount))(un, number);
	}
	void killUnit(unit* un)
	{
		(*(*plugData::data.funcs.killUnit))(un);
	}
	void setUnitParams(unit* un, int exp, int armor, int weap)
	{
		(*(*plugData::data.funcs.setUnitParams))(un, un->number, exp, armor, weap);
	}
	float getMovepoints(const unit* un)
	{
		return un->movePoints;
	}
}
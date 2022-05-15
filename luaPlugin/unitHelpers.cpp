#include "unitHelpers.h"
#include "plugData.h"
namespace unitHelpers
{
	int getExp(unit* un)
	{
		return un->expScreen;
	}
	void setExp(unit* un, int exp)
	{
		(*(*plugData::data.funcs.setUnitParams))(un, un->number, exp, getarmourLVL(un), getweaponLVL(un));
	}
	int getarmourLVL(unit* un)
	{
		return un->stats >> 0xd & 0x1f;
	}
	void setarmourLVL(unit* un, int lvl)
	{
		(*(*plugData::data.funcs.setUnitParams))(un, un->number, un->expScreen, lvl, getweaponLVL(un));
	}
	int getweaponLVL(unit* un)
	{
		return un->stats >> 0x8 & 0x1f;
	}
	void setweaponLVL(unit* un, int lvl)
	{
		(*(*plugData::data.funcs.setUnitParams))(un, un->number, un->expScreen, getarmourLVL(un), lvl);
	}
	void setMovepoints(unit* un, float movepoints)
	{
		(*(*plugData::data.funcs.setUnitMovepoints))(un, movepoints);

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
	int getsoldierCountStratMap(const unit* un)
	{
		return un->number;
	}
}
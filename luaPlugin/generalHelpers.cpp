#include "generalHelpers.h"
#include "plugData.h"

namespace generalHelpers
{

	void moveToTile(general* gen, int x, int y)
	{
		(*(*plugData::data.funcs.moveNormal))(gen,x, y);
	}

	void reposition(general* gen, int x, int y)
	{
		(*(*plugData::data.funcs.teleportCharacter))(gen, x, y);
	}

	void siegeSettlement(general* gen, settlementStruct* sett)
	{
		(*(*plugData::data.funcs.siegeSettlement))(gen, sett);
	}

	void killGeneral(general* gen)
	{
		(*(*plugData::data.funcs.killCharacter))(gen);
	}

	void setBodyguard(general* gen, unit* un)
	{
		(*(*plugData::data.funcs.setBodyguard))(gen, un);
	}

	void setMovepoints(general* gen, float movepoints)
	{
		gen->movepoints1 = movepoints;
		gen->movepoints2 = movepoints;

		if (gen->bodyguards == nullptr)return;

		gen->bodyguards->movePoints = movepoints;
	}

	float getMovepoints(const general* gen)
	{
		return gen->movepoints2;
	}

}
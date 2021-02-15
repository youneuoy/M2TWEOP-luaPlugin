#include "stackStructHelpers.h"
#include "plugData.h"
namespace stackStructHelpers
{
	unit* getUnit(const stackStruct* army, int index)
	{
		return army->units[index];
	}
	general* getCharacter(const stackStruct* army, int index)
	{
		return army->characters[index];
	}
	int attackArmy(stackStruct* army, stackStruct* defender)
	{
		general* atkGen = army->gen;
		general* defGen = army->gen;
		if (atkGen == nullptr
			|| defGen == nullptr
			)return 0;

		(*(*plugData::data.funcs.attackCharacter))(atkGen, defGen);

		return 1;
	}
	settlementStruct* findInSettlement(const stackStruct* army)
	{
		if (army->settlement == nullptr)
		{
			return nullptr;
		}

		for (int i = 0; i < army->faction->settlementsNum; i++)
		{
			settlementStruct* sett = army->faction->settlements[i];
			if (sett->army == army)return sett;
		}

		return nullptr;
	}
	fortStruct* findInFort(const stackStruct* army)
	{
		if (army->settlement == nullptr)
		{
			return nullptr;
		}

		for (int i = 0; i < army->faction->fortsNum; i++)
		{
			fortStruct* frt = army->faction->forts[i];
			if (frt->army == army)return frt;
		}

		return nullptr;
	}


	int addUnitToArmy(stackStruct* army, unit* un)
	{
		return (*(*plugData::data.funcs.addUnitToArmy))(army, un);
	}
}
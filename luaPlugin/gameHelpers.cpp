#include "gameHelpers.h"
#include "plugData.h"

UINT32 gameHelpers::getFactionsCount()
{
	return (*(*plugData::data.funcs.getFactionsCount))();
}

factionStruct* gameHelpers::getFaction(int index)
{
	return (*(*plugData::data.funcs.getFactionsList))()[index];
}

general* gameHelpers::createCharacter(const char* type, factionStruct* fac, int age, const char* name, const char* name2, int subFaction, const char* portrait, int x, int y)
{
	return (*(*plugData::data.funcs.createCharacter))(type, fac, age, name, name2, subFaction, portrait, x, y);
}

stackStruct* gameHelpers::createArmy(general* character)
{
	return (*(*plugData::data.funcs.createArmy))(character);
}

unit* gameHelpers::createUnitN(const char* type, int facNum, int exp, int arm, int weap)
{
	return (*(*plugData::data.funcs.createUnitN))(type, facNum, exp, arm, weap);
}

unit* gameHelpers::createUnitIdx(int eduIdx, int facNum, int exp, int arm, int weap)
{
	return (*(*plugData::data.funcs.createUnitIdx))(eduIdx, facNum, exp, arm, weap);
}

std::tuple<bool, int> gameHelpers::getScriptCounter(const char* type)
{
	bool isExist = false;
	int counterValue=(*(*plugData::data.funcs.getScriptCounter))(type,isExist);

	return std::make_tuple(isExist, counterValue);
}

void gameHelpers::setScriptCounter(const char* type, int value)
{
	(*(*plugData::data.funcs.setScriptCounter))(type, value);
}

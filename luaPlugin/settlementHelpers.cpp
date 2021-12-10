#include "settlementHelpers.h"

#include "plugData.h"
resStrat* settlementHelpers::getResource(const settlementStruct* sett, int index)
{
	return sett->resources[index];
}

building* settlementHelpers::getBuilding(const settlementStruct* sett, int index)
{
	return sett->buildings[index];
}

void settlementHelpers::destroyBuilding(settlementStruct* sett, const char* typeName, bool isReturnMoney)
{
	(*(*plugData::data.funcs.destroyBuilding))(sett, typeName, isReturnMoney);
}

void settlementHelpers::createBuilding(settlementStruct* sett, const char* building_level_id)
{
	(*(*plugData::data.funcs.createBuilding))(sett, building_level_id);
}

int settlementHelpers::getGuildStanding(settlementStruct* sett, int index)
{
	return *(int*)((sett->guildStandings) + 0x4 * index);
}
void settlementHelpers::setGuildStanding(settlementStruct* sett, int index, int amount)
{
	*(int*)((sett->guildStandings) + 0x4 * index) = amount;
}

#include "settlementHelpers.h"

resStrat* settlementHelpers::getResource(const settlementStruct* sett, int index)
{
	return sett->resources[index];
}

building* settlementHelpers::getBuilding(const settlementStruct* sett, int index)
{
	return sett->buildings[index];
}

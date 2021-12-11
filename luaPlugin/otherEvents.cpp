#include "otherEvents.h"

void onMultiTurnMove(generalCharacterictics* gen)
{
	plugData::data.luaAll.onMultiTurnMove(gen);
}

void onSettlementSelected(settlementStruct* sett)
{
	plugData::data.luaAll.onSettlementSelected(sett);
}

void onSettlementUpgraded(settlementStruct* sett)
{
	plugData::data.luaAll.onSettlementUpgraded(sett);
}

void onSettlementConverted(settlementStruct* sett)
{
	plugData::data.luaAll.onSettlementConverted(sett);
}

void onCityRiots(settlementStruct* sett)
{
	if (plugData::data.luaAll.onCityRiotsFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onCityRiotsFunc)(sett));
	}
}

void onUngarrisonedSettlement(settlementStruct* sett)
{
	if (plugData::data.luaAll.onUngarrisonedSettlementFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onUngarrisonedSettlementFunc)(sett));
	}
}

void onUngarrisonedFort(fortStruct* frt)
{
	if (plugData::data.luaAll.onUngarrisonedFortFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onUngarrisonedFortFunc)(frt));
	}
}

void onGiveSettlement(settlementStruct* sett, factionStruct* fac, factionStruct* fac2)
{
	if (plugData::data.luaAll.onGiveSettlementFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onGiveSettlementFunc)(sett,fac,fac2));
	}
}

void onOccupySettlement(generalCharacterictics* gen, factionStruct* fac)
{
	if (plugData::data.luaAll.onOccupySettlementFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onOccupySettlementFunc)(fac));
	}
}

void onExterminatePopulation(generalCharacterictics* gen, factionStruct* fac)
{
	if (plugData::data.luaAll.onExterminatePopulationFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onExterminatePopulationFunc)(gen,fac));
	}
}

void onSackSettlement(generalCharacterictics* gen, factionStruct* fac)
{
	if (plugData::data.luaAll.onSackSettlementFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onSackSettlementFunc)(gen, fac));
	}
}

void onAddedToBuildingQueue(settlementStruct* sett, const char* build)
{
	if (plugData::data.luaAll.onAddedToBuildingQueueFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onAddedToBuildingQueueFunc)(sett, build));
	}
}

void onBuildingDestroyed(settlementStruct* sett, const char* build)
{
	if (plugData::data.luaAll.onBuildingDestroyedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onBuildingDestroyedFunc)(sett, build));
	}
}

void onBuildingCompleted(factionStruct* fac, settlementStruct* sett)
{
	if (plugData::data.luaAll.onBuildingCompletedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onBuildingCompletedFunc)(fac, sett));
	}
}

void onEventCounter(const char* str)
{
	if (plugData::data.luaAll.onEventCounterFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onEventCounterFunc)(str));
	}
}

void onFactionExcommunicated(factionStruct* fac)
{
	if (plugData::data.luaAll.onFactionExcommunicatedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onFactionExcommunicatedFunc)(fac));
	}
}

void onDisaster(int eventType)
{
	if (plugData::data.luaAll.onDisasterFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onDisasterFunc)(eventType));
	}
}

void onHordeFormed(factionStruct* fac)
{
	if (plugData::data.luaAll.onHordeFormedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onHordeFormedFunc)(fac));
	}
}

void onAddedToTrainingQueue(settlementStruct* sett, const char* unitName)
{
	if (plugData::data.luaAll.onAddedToTrainingQueueFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onAddedToTrainingQueueFunc)(sett, unitName));
	}
}

void onUnitDisbanded(factionStruct* fac, unit* un)
{
	if (plugData::data.luaAll.onUnitDisbandedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onUnitDisbandedFunc)(fac, un));
	}
}

void onUnitTrained(factionStruct* fac, settlementStruct* sett, unit* un)
{
	if (plugData::data.luaAll.onUnitTrainedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onUnitTrainedFunc)(fac, sett,un));
	}
}

void onAgentCreated(generalCharacterictics* pers, int type, settlementStruct* sett)
{
	if (plugData::data.luaAll.onAgentCreatedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onAgentCreatedFunc)(pers, type, sett));
	}
}

void onObjSeen(factionStruct* fac, factionStruct* fac2, int x, int y)
{
	if (plugData::data.luaAll.onObjSeenFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onObjSeenFunc)(fac, fac2, x, y));
	}
}

void onTileSeen(factionStruct* fac, int x, int y)
{
	if (plugData::data.luaAll.onTileSeenFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onTileSeenFunc)(fac, x, y));
	}
}

void onGameReloaded(int something)
{
	if (plugData::data.luaAll.onGameReloadedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onGameReloadedFunc)(something));
	}
}

void onTransgression(factionStruct* fac, const char* str, factionStruct* fac2)
{
	if (plugData::data.luaAll.onTransgressionFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onTransgressionFunc)(fac,str,fac2));
	}
}

void onGuildUpgraded(settlementStruct* sett, const char* resourceDescription)
{
	if (plugData::data.luaAll.onGuildUpgradedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onGuildUpgradedFunc)(sett, resourceDescription))
	}
}

void onGuildDestroyed(settlementStruct* sett, unsigned char guildID)
{
	if (plugData::data.luaAll.onGuildDestroyedFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.onGuildDestroyedFunc)(sett, guildID))
	}
}
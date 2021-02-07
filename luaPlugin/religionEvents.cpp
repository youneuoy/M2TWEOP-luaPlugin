#include "religionEvents.h"

void onPopeAcceptsCrusadeTarget(void* crusade, settlementStruct* sett)
{
	if (plugData::data.luaAll.onPopeAcceptsCrusadeTargetFunc != nullptr)
	{
		(*plugData::data.luaAll.onPopeAcceptsCrusadeTargetFunc)((int)crusade, sett);
	}
}

void onCrusadeCalled(void* crusade, settlementStruct* sett)
{
	if (plugData::data.luaAll.onCrusadeCalledFunc != nullptr)
	{
		(*plugData::data.luaAll.onCrusadeCalledFunc)((int)crusade, sett);
	}
}

void onCrusadeEnds(void* crusade, settlementStruct* sett)
{
	if (plugData::data.luaAll.onCrusadeEndsFunc != nullptr)
	{
		(*plugData::data.luaAll.onCrusadeEndsFunc)((int)crusade, sett);
	}
}

void onPopeRejectsCrusadeTarget(void* crusade, settlementStruct* sett)
{
	if (plugData::data.luaAll.onPopeRejectsCrusadeTargetFunc != nullptr)
	{
		(*plugData::data.luaAll.onPopeRejectsCrusadeTargetFunc)((int)crusade, sett);
	}
}

void onArmyTakesCrusadeTarget(void* crusade, settlementStruct* sett, stackStruct* army)
{
	if (plugData::data.luaAll.onArmyTakesCrusadeTargetFunc != nullptr)
	{
		(*plugData::data.luaAll.onArmyTakesCrusadeTargetFunc)((int)crusade, sett, army);
	}
}

void onUnitsDesertCrusade(void* crusade, settlementStruct* sett, factionStruct* fac)
{
	if (plugData::data.luaAll.onUnitsDesertCrusadeFunc != nullptr)
	{
		(*plugData::data.luaAll.onUnitsDesertCrusadeFunc)((int)crusade, sett, fac);
	}
}

void onPopeElected(factionStruct* fac, factionStruct* fac2)
{
	if (plugData::data.luaAll.onPopeElectedFunc != nullptr)
	{
		(*plugData::data.luaAll.onPopeElectedFunc)(fac,fac2);
	}
}

void onVotedForPope(factionStruct* fac)
{
	if (plugData::data.luaAll.onVotedForPopeFunc != nullptr)
	{
		(*plugData::data.luaAll.onVotedForPopeFunc)(fac);
	}
}

void onAssassinCaughtAttackingPope(factionStruct* fac)
{
	if (plugData::data.luaAll.onAssassinCaughtAttackingPopeFunc != nullptr)
	{
		(*plugData::data.luaAll.onAssassinCaughtAttackingPopeFunc)(fac);
	}
}

void onInquisitorAppointed(factionStruct* fac, settlementStruct* sett)
{
	if (plugData::data.luaAll.onInquisitorAppointedFunc != nullptr)
	{
		(*plugData::data.luaAll.onInquisitorAppointedFunc)(fac,sett);
	}
}

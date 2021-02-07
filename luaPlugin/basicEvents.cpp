#include "basicEvents.h"

void onChangeTurnNum(int num)
{
	plugData::data.luaAll.onChangeTurnNum(num);
}

void onPreFactionTurnStart(factionStruct* fac)
{
	plugData::data.luaAll.onPreFactionTurnStart(fac);
}

void onFactionTurnStart(factionStruct* fac)
{
	plugData::data.luaAll.onFactionTurnStart(fac);
}

void onFactionTurnEnd(factionStruct* fac)
{
	plugData::data.luaAll.onFactionTurnEnd(fac);
}

void onFactionNewCapital(factionStruct* fac)
{
	plugData::data.luaAll.onFactionNewCapital(fac);
}

void onFactionWarDeclared(factionStruct* fac, factionStruct* fac2)
{
	plugData::data.luaAll.onFactionWarDeclared(fac,fac2);
}

void onFactionAllianceDeclared(factionStruct* fac, factionStruct* fac2)
{
	plugData::data.luaAll.onFactionWarDeclared(fac, fac2);
}

void onFactionTradeAgreementMade(factionStruct* fac, factionStruct* fac2)
{
	plugData::data.luaAll.onFactionTradeAgreementMade(fac, fac2);
}

void onFactionBreakAlliance(factionStruct* fac, factionStruct* fac2)
{
	plugData::data.luaAll.onFactionBreakAlliance(fac, fac2);
}

void onGiveMoney(factionStruct* fac, factionStruct* fac2, float amount)
{
	plugData::data.luaAll.onGiveMoney(fac, fac2, amount);
}

void onUpdateAttitude(factionStruct* fac, factionStruct* fac2)
{
	plugData::data.luaAll.onUpdateAttitude(fac, fac2);
}

void onDemeanour(factionStruct* fac, factionStruct* fac2, float amount)
{
	plugData::data.luaAll.onDemeanour(fac, fac2, amount);

}

void onCharacterSelected(generalCharacterictics* gen)
{
	plugData::data.luaAll.onCharacterSelected(gen);
}

void onGeneralAssaultsGeneral(generalCharacterictics* gen, generalCharacterictics* gen2)
{
	plugData::data.luaAll.onGeneralAssaultsGeneral(gen, gen2);

}

void onGeneralAssaultsResidence(generalCharacterictics* gen, settlementStruct* sett, fortStruct* frt)
{
	plugData::data.luaAll.onGeneralAssaultsResidence(gen, sett,frt);
}

void onGeneralCaptureSettlement(generalCharacterictics* gen, settlementStruct* sett)
{
	plugData::data.luaAll.onGeneralCaptureSettlement(gen, sett);
}

void onGeneralCaptureResidence(generalCharacterictics* gen)
{
	plugData::data.luaAll.onGeneralCaptureResidence(gen);
}

void onSiegeEquipmentCompleted(settlementStruct* sett, fortStruct* frt)
{
	plugData::data.luaAll.onSiegeEquipmentCompleted(sett,frt);
}

void onPostBattle(generalCharacterictics* gen)
{
	plugData::data.luaAll.onPostBattle(gen);
}

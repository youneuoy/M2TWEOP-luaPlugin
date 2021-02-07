#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "lua/LuaBridge.h"
#include <string>
#include "realGameTypes.h"
#include <windows.h>
#include "luaGetSetFuncs.h"
#include "factionHelpers.h"
#include "settlementHelpers.h"
#include "resourcesHelpers.h"
#include "objectsHelpers.h"
#include "gameHelpers.h"
#include "stackStructHelpers.h"
#include "buildingStructHelpers.h"
#include "generalHelpers.h"
#include "unitHelpers.h"
#include "cameraHelpers.h"
#include "generalCharactericticsHelpers.h"
using namespace luabridge;

class luaP
{
public:
	bool init(std::string& luaFilePath,std::string& modPath);


	//lua functions and events controllers
	void onPluginLoadF();
	void onChangeTurnNum(int num);
	void onCharacterSelected(generalCharacterictics* gen);
	void onPreFactionTurnStart(factionStruct* fac);
	void onFactionTurnStart(factionStruct* fac);
	void onFactionTurnEnd(factionStruct* fac);
	void onFactionNewCapital(factionStruct* fac);
	void onFactionWarDeclared(factionStruct* fac, factionStruct* fac2);
	void onFactionAllianceDeclared(factionStruct* fac, factionStruct* fac2);
	void onFactionTradeAgreementMade(factionStruct* fac, factionStruct* fac2);
	void onFactionBreakAlliance(factionStruct* fac, factionStruct* fac2);

	void onGiveMoney(factionStruct* fac, factionStruct* fac2, float amount);
	void onUpdateAttitude(factionStruct* fac, factionStruct* fac2);
	void onDemeanour(factionStruct* fac, factionStruct* fac2, float amount);

	void onGeneralAssaultsGeneral(generalCharacterictics* gen, generalCharacterictics* gen2);
	void onGeneralAssaultsResidence(generalCharacterictics* gen, settlementStruct* sett, fortStruct* frt);
	void onGeneralCaptureSettlement(generalCharacterictics* gen, settlementStruct* sett);

	void onGeneralCaptureResidence(generalCharacterictics* gen);
	void onSiegeEquipmentCompleted(settlementStruct* sett, fortStruct* frt);
	void onPostBattle(generalCharacterictics* gen);
	


	void onMultiTurnMove(generalCharacterictics* gen);
	void onSettlementSelected(settlementStruct* sett);
	void onSettlementUpgraded(settlementStruct* sett);
	void onSettlementConverted(settlementStruct* sett);


	lua_State* L = nullptr;


	LuaRef* onPluginLoad = nullptr;
	LuaRef* onChangeTurnNumFunc = nullptr;
	LuaRef* onCharacterSelectedFunc = nullptr;
	LuaRef* onPreFactionTurnStartFunc = nullptr;
	LuaRef* onFactionTurnStartFunc = nullptr;
	LuaRef* onFactionTurnEndFunc = nullptr;
	LuaRef* onFactionNewCapitalFunc = nullptr;
	LuaRef* onFactionWarDeclaredFunc = nullptr;
	LuaRef* onFactionAllianceDeclaredFunc = nullptr;
	LuaRef* onFactionTradeAgreementMadeFunc = nullptr;
	LuaRef* onFactionBreakAllianceFunc = nullptr;

	LuaRef* onGiveMoneyFunc = nullptr;
	LuaRef* onUpdateAttitudeFunc = nullptr;
	LuaRef* onDemeanourFunc = nullptr;

	LuaRef* onGeneralAssaultsGeneralFunc = nullptr;
	LuaRef* onGeneralAssaultsResidenceFunc = nullptr;
	LuaRef* onGeneralCaptureSettlementFunc = nullptr;

	LuaRef* onGeneralCaptureResidenceFunc = nullptr;
	LuaRef* onSiegeEquipmentCompletedFunc = nullptr;
	LuaRef* onPostBattleFunc = nullptr;


	LuaRef* onMultiTurnMoveFunc = nullptr;
	LuaRef* onSettlementSelectedFunc = nullptr;
	LuaRef* onSettlementUpgradedFunc = nullptr;
	LuaRef* onSettlementConvertedFunc = nullptr;
	LuaRef* onCityRiotsFunc = nullptr;
	LuaRef* onUngarrisonedSettlementFunc = nullptr;

	LuaRef* onUngarrisonedFortFunc = nullptr;
	LuaRef* onGiveSettlementFunc = nullptr;
	LuaRef* onOccupySettlementFunc = nullptr;
	LuaRef* onExterminatePopulationFunc = nullptr;

	LuaRef* onSackSettlementFunc = nullptr;
	LuaRef* onAddedToBuildingQueueFunc = nullptr;
	LuaRef* onBuildingDestroyedFunc = nullptr;
	LuaRef* onBuildingCompletedFunc = nullptr;
	LuaRef* onEventCounterFunc = nullptr;

	LuaRef* onFactionExcommunicatedFunc = nullptr;
	LuaRef* onDisasterFunc = nullptr;
	LuaRef* onHordeFormedFunc = nullptr;
	LuaRef* onAddedToTrainingQueueFunc = nullptr;

	LuaRef* onUnitDisbandedFunc = nullptr;
	LuaRef* onUnitTrainedFunc = nullptr;
	LuaRef* onAgentCreatedFunc = nullptr;

	LuaRef* onObjSeenFunc = nullptr;
	LuaRef* onTileSeenFunc = nullptr;
	LuaRef* onGameReloadedFunc = nullptr;
	LuaRef* onTransgressionFunc = nullptr;


	LuaRef* onPopeAcceptsCrusadeTargetFunc = nullptr;
	LuaRef* onCrusadeCalledFunc = nullptr;
	LuaRef* onCrusadeEndsFunc = nullptr;
	LuaRef* onPopeRejectsCrusadeTargetFunc = nullptr;
	LuaRef* onArmyTakesCrusadeTargetFunc = nullptr;

	LuaRef* onUnitsDesertCrusadeFunc = nullptr;
	LuaRef* onPopeElectedFunc = nullptr;
	LuaRef* onVotedForPopeFunc = nullptr;
	LuaRef* onAssassinCaughtAttackingPopeFunc = nullptr;
	LuaRef* onInquisitorAppointedFunc = nullptr;



	LuaRef* onSettlementPanelOpenFunc = nullptr;
	LuaRef* onFinancesPanelOpenFunc = nullptr;
	LuaRef* onFactionSummaryPanelOpenFunc = nullptr;
	LuaRef* onFamilyTreePanelOpenFunc = nullptr;
	LuaRef* onDiplomaticStandingPanelOpenFunc = nullptr;
	LuaRef* onDiplomacyPanelOpenFunc = nullptr;
	LuaRef* onPreBattlePanelOpenFunc = nullptr;
	LuaRef* onNavalAutoResolvePanelOpenFunc = nullptr;

	LuaRef* onCharacterPanelOpenFunc = nullptr;
	LuaRef* onTradePanelOpenFunc = nullptr;
	LuaRef* onRequestBuildingAdviceFunc = nullptr;
	LuaRef* onRequestTrainingAdviceFunc = nullptr;
	LuaRef* onMessageOpenFunc = nullptr;
	LuaRef* onIncomingMessageFunc = nullptr;
	LuaRef* onMessageClosedFunc = nullptr;

	LuaRef* onButtonPressedFunc = nullptr;
	LuaRef* onScrollClosedFunc = nullptr;
	LuaRef* onScrollOpenedFunc = nullptr;
	LuaRef* onUIElementVisibleFunc = nullptr;
	LuaRef* onScrollAdviceRequestedFunc = nullptr;
	LuaRef* onSettlementScrollAdviceRequestedFunc = nullptr;
	LuaRef* onPreBattleScrollAdviceRequestedFunc = nullptr;
	LuaRef* onNavalPreBattleScrollAdviceRequestedFunc = nullptr;
	LuaRef* onCollegeOfCardinalsPanelOpenFunc = nullptr;



};


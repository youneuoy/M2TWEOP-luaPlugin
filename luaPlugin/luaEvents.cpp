///
//![Lua logo](_static/Lua.png)
//M2TWEOP structures and functions. There are not many examples and descriptions here. Also note that the examples do not include many of the checks that would be required when creating modifications.
//@module LuaPlugin
//@author youneuoy
//@license GPL-3.0
#include "luaP.h"
#include "plugData.h"
void luaP::onPluginLoadF()
{
	///EVENTS TABLE SECTION
	//@section eventsList

	/***
	Events functions list.
	Just list, use it without EventsFunctionsList.!!!

	@tfield draw draw
	@tfield onNewGameStart onNewGameStart
	@tfield onCampaignMapLoaded onCampaignMapLoaded
	@tfield onCreateSaveFile onCreateSaveFile
	@tfield onLoadSaveFile onLoadSaveFile
	@tfield onPluginLoad onPluginLoad
	@tfield onChangeTurnNum onChangeTurnNum
	@tfield onCharacterSelected onCharacterSelected
	@tfield onPreFactionTurnStart onPreFactionTurnStart
	@tfield onFactionTurnStart onFactionTurnStart
	@tfield onFactionTurnEnd onFactionTurnEnd
	@tfield onFactionNewCapital onFactionNewCapital
	@tfield onFactionWarDeclared onFactionWarDeclared
	@tfield onFactionAllianceDeclared onFactionAllianceDeclared
	@tfield onFactionTradeAgreementMade onFactionTradeAgreementMade
	@tfield onFactionBreakAlliance onFactionBreakAlliance
	@tfield onGiveMoney onGiveMoney
	@tfield onUpdateAttitude onUpdateAttitude
	@tfield onDemeanour onDemeanour
	@tfield onGeneralAssaultsGeneral onGeneralAssaultsGeneral
	@tfield onGeneralAssaultsResidence onGeneralAssaultsResidence
	@tfield onGeneralCaptureSettlement onGeneralCaptureSettlement
	@tfield onGeneralCaptureResidence onGeneralCaptureResidence
	@tfield onSiegeEquipmentCompleted onSiegeEquipmentCompleted
	@tfield onPostBattle onPostBattle
	@tfield onMultiTurnMove onMultiTurnMove
	@tfield onSettlementSelected onSettlementSelected
	@tfield onSettlementUpgraded onSettlementUpgraded
	@tfield onSettlementConverted onSettlementConverted
	@tfield onCityRiots onCityRiots
	@tfield onUngarrisonedSettlement onUngarrisonedSettlement
	@tfield onUngarrisonedFort onUngarrisonedFort
	@tfield onGiveSettlement onGiveSettlement
	@tfield onOccupySettlement onOccupySettlement
	@tfield onExterminatePopulation onExterminatePopulation
	@tfield onSackSettlement onSackSettlement
	@tfield onAddedToBuildingQueue onAddedToBuildingQueue
	@tfield onBuildingDestroyed onBuildingDestroyed
	@tfield onBuildingCompleted onBuildingCompleted
	@tfield onEventCounter onEventCounter
	@tfield onFactionExcommunicated onFactionExcommunicated
	@tfield onDisaster onDisaster
	@tfield onHordeFormed onHordeFormed
	@tfield onAddedToTrainingQueue onAddedToTrainingQueue
	@tfield onUnitDisbanded onUnitDisbanded
	@tfield onUnitTrained onUnitTrained
	@tfield onAgentCreated onAgentCreated
	@tfield onObjSeen onObjSeen
	@tfield onTileSeen onTileSeen
	@tfield onGameReloaded onGameReloaded
	@tfield onTransgression onTransgression
	@tfield onPopeAcceptsCrusadeTarget onPopeAcceptsCrusadeTarget
	@tfield onCrusadeCalled onCrusadeCalled
	@tfield onCrusadeEnds onCrusadeEnds
	@tfield onPopeRejectsCrusadeTarget onPopeRejectsCrusadeTarget
	@tfield onArmyTakesCrusadeTarget onArmyTakesCrusadeTarget
	@tfield onUnitsDesertCrusade onUnitsDesertCrusade
	@tfield onPopeElected onPopeElected
	@tfield onVotedForPope onVotedForPope
	@tfield onAssassinCaughtAttackingPope onAssassinCaughtAttackingPope
	@tfield onInquisitorAppointed onInquisitorAppointed
	@tfield onSettlementPanelOpen onSettlementPanelOpen
	@tfield onFinancesPanelOpen onFinancesPanelOpen
	@tfield onFactionSummaryPanelOpen onFactionSummaryPanelOpen
	@tfield onFamilyTreePanelOpenFunc onFamilyTreePanelOpenFunc
	@tfield onDiplomaticStandingPanelOpen onDiplomaticStandingPanelOpen
	@tfield onDiplomacyPanelOpen onDiplomacyPanelOpen
	@tfield onPreBattlePanelOpen onPreBattlePanelOpen
	@tfield onNavalAutoResolvePanelOpen onNavalAutoResolvePanelOpen
	@tfield onCharacterPanelOpen onCharacterPanelOpen
	@tfield onTradePanelOpen onTradePanelOpen
	@tfield onRequestBuildingAdvice onRequestBuildingAdvice
	@tfield onRequestTrainingAdvice onRequestTrainingAdvice
	@tfield onMessageOpen onMessageOpen
	@tfield onIncomingMessage onIncomingMessage
	@tfield onMessageClosed onMessageClosed
	@tfield onButtonPressed onButtonPressed
	@tfield onScrollClosed onScrollClosed
	@tfield onScrollOpened onScrollOpened
	@tfield onUIElementVisible onUIElementVisible
	@tfield onScrollAdviceRequested onScrollAdviceRequested
	@tfield onSettlementScrollAdviceRequested onSettlementScrollAdviceRequested
	@tfield onPreBattleScrollAdviceRequested onPreBattleScrollAdviceRequested
	@tfield onNavalPreBattleScrollAdviceRequested onNavalPreBattleScrollAdviceRequested
	@tfield onCollegeOfCardinalsPanelOpen onCollegeOfCardinalsPanelOpen




	@table EventsFunctionsList
	*/




	/***
	Called every time an image is rendered for display

	@function draw
	@tparam LPDIRECT3DDEVICE9 pDevice

	@usage
	function draw(device)
		ImGui.Begin("test");

		ImGui.Text("Some test text")

		ImGui.End();
	end
	*/
	drawLuaFunc = new sol::function(luaState["draw"]);
	checkLuaFunc(&drawLuaFunc);

	resetDXFunc = new sol::function(luaState["deinitDX"]);
	checkLuaFunc(&resetDXFunc);

	initDXFunc = new sol::function(luaState["initDX"]);
	checkLuaFunc(&initDXFunc);

	/***
	Called on new campaign start

	@function onNewGameStart

	@usage
	function onNewGameStart()
	--something here
	end
	*/



	onNewGameStart = new sol::function(luaState["onNewGameStart"]);
	checkLuaFunc(&onNewGameStart);

	/***
	Called after loading of campaign map

	@function onCampaignMapLoaded

	@usage
	function onCampaignMapLoaded()
	--something here
	end
	*/



	onCampaignMapLoaded = new sol::function(luaState["onCampaignMapLoaded"]);
	checkLuaFunc(&onCampaignMapLoaded);

	/***
	Called on plugin load(at game start)

	@function onPluginLoad

	@usage
	--An example of using this event to perform actions at the beginning of a campaign once:

	isCampaignLoadedFirstTime=false;
	function onNewGameStart()
	  isCampaignLoadedFirstTime=true;
	end

	function onCampaignMapLoaded()
	  if(isCampaignLoadedFirstTime==false)
		then
		  do return end
		end


	  --here we do our stuff, what works only one time for each campaign
	  isCampaignLoadedFirstTime=false;
	end
	*/



	onPluginLoad = new sol::function(luaState["onPluginLoad"]);
	checkLuaFunc(&onPluginLoad);


	/***
	Called on creating save file

	@function onCreateSaveFile

	@usage
		savefiles = {};
		currentPath=M2TWEOP.getPluginPath();

		savefiles[1]=currentPath.."\\testSaveFile1.ourSave";
		savefiles[2]=currentPath.."\\testSaveFile2.ourSave";

		file1 = io.open(savefiles[1], "w")
		file1:write("This is save file 1!!!")
		file1:close()

		file2 = io.open(savefiles[2], "w")
		file2:write("This is save file 2!!!")
		file2:close()

		return savefiles;
	*/
	onCreateSaveFile = new sol::function(luaState["onCreateSaveFile"]);
	checkLuaFunc(&onCreateSaveFile);

	/***
	Called on loading save file

	@function onLoadSaveFile

	@usage
	function onLoadSaveFile(paths)
		lastSaveFiles={};
		for key, value in pairs(paths) do

		print(key, " -- ", value);

		lastSaveFiles[key]={};
		lastSaveFiles[key][1]=value;
		lastSaveFiles[key][2]=readFile(value);

		end
	end


	--read file and return it`s content
	local function readFile(path)
		local file = io.open(path, "r") ;
		if (not file) then return nil end
		local content = file:read "*a";
		file:close();
		return content;
	end
	*/
	onLoadSaveFile = new sol::function(luaState["onLoadSaveFile"]);
	checkLuaFunc(&onLoadSaveFile);


	/***
	Called on every turn

	@function onChangeTurnNum
	@tparam int turnNumber

	@usage
	function onChangeTurnNum(turnNum)
	--something here
	end
	*/
	onChangeTurnNumFunc = new sol::function(luaState["onChangeTurnNum"]);
	checkLuaFunc(&onChangeTurnNumFunc);

	/***
	Called on character selection

	@function onCharacterSelected
	@tparam namedCharacter selectedChar

	@usage
	function onChangeTurnNum(onCharacterSelected)
	--something here
	end
	*/
	onCharacterSelectedFunc = new sol::function(luaState["onCharacterSelected"]);
	checkLuaFunc(&onCharacterSelectedFunc);

	/***
	Called before faction turn start

	@function onPreFactionTurnStart
	@tparam factionStruct faction

	@usage
	function onPreFactionTurnStart(fac)
	--something here
	end
	*/
	onPreFactionTurnStartFunc = new sol::function(luaState["onPreFactionTurnStart"]);
	checkLuaFunc(&onPreFactionTurnStartFunc);

	/***
	Called at faction turn start

	@function onFactionTurnStart
	@tparam factionStruct faction

	@usage
	function onFactionTurnStart(fac)
	--something here
	end
	*/
	onFactionTurnStartFunc = new sol::function(luaState["onFactionTurnStart"]);
	checkLuaFunc(&onFactionTurnStartFunc);

	/***
	Called at faction turn end

	@function onFactionTurnEnd
	@tparam factionStruct faction

	@usage
	function onFactionTurnEnd(fac)
	--something here
	end
	*/
	onFactionTurnEndFunc = new sol::function(luaState["onFactionTurnEnd"]);
	checkLuaFunc(&onFactionTurnEndFunc);

	/***
	Called after faction has new capital

	@function onFactionNewCapital
	@tparam factionStruct faction

	@usage
	function onFactionNewCapital(fac)
	newCapital=fac.capital();
	end
	*/
	onFactionNewCapitalFunc = new sol::function(luaState["onFactionNewCapital"]);
	checkLuaFunc(&onFactionNewCapitalFunc);

	/***
	Called after declaring war

	@function onFactionWarDeclared
	@tparam factionStruct faction
	@tparam factionStruct targetFaction

	@usage
	function onFactionWarDeclared(faction,targetFaction)
	-something
	end
	*/
	onFactionWarDeclaredFunc = new sol::function(luaState["onFactionWarDeclared"]);
	checkLuaFunc(&onFactionWarDeclaredFunc);

	/***
	Called after declaring alliance

	@function onFactionAllianceDeclared
	@tparam factionStruct faction
	@tparam factionStruct targetFaction

	@usage
	function onFactionAllianceDeclared(faction,targetFaction)
	-something
	end
	*/

	onFactionAllianceDeclaredFunc = new sol::function(luaState["onFactionAllianceDeclared"]);
	checkLuaFunc(&onFactionAllianceDeclaredFunc);

	/***
	Called after declaring trade agreement

	@function onFactionTradeAgreementMade
	@tparam factionStruct faction
	@tparam factionStruct targetFaction

	@usage
	function onFactionTradeAgreementMade(faction,targetFaction)
	-something
	end
	*/

	onFactionTradeAgreementMadeFunc = new sol::function(luaState["onFactionTradeAgreementMade"]);
	checkLuaFunc(&onFactionTradeAgreementMadeFunc);

	/***
	Called after break alliance

	@function onFactionBreakAlliance
	@tparam factionStruct faction
	@tparam factionStruct targetFaction

	@usage
	function onFactionBreakAlliance(faction,targetFaction)
	-something
	end
	*/


	onFactionBreakAllianceFunc = new sol::function(luaState["onFactionBreakAlliance"]);
	checkLuaFunc(&onFactionBreakAllianceFunc);


	/***
	Called after giving money

	@function onGiveMoney
	@tparam factionStruct faction
	@tparam factionStruct targetFaction
	@tparam int amount

	@usage
	function onGiveMoney(faction,targetFaction,amount)
	-something
	end
	*/


	onGiveMoneyFunc = new sol::function(luaState["onGiveMoney"]);
	checkLuaFunc(&onGiveMoneyFunc);


	/***
	Called after update attitude

	@function onUpdateAttitude
	@tparam factionStruct faction
	@tparam factionStruct targetFaction

	@usage
	function onUpdateAttitude(faction,targetFaction)
	-something
	end
	*/


	onUpdateAttitudeFunc = new sol::function(luaState["onUpdateAttitude"]);
	checkLuaFunc(&onUpdateAttitudeFunc);


	/***
	A demeanour response has occured in diplomacy talks

	@function onDemeanour
	@tparam factionStruct faction
	@tparam factionStruct targetFaction
	@tparam float amount

	@usage
	function onDemeanour(faction,targetFaction,amount)
	-something
	end
	*/

	onDemeanourFunc = new sol::function(luaState["onDemeanour"]);
	checkLuaFunc(&onDemeanourFunc);

	/***
	A general has attacked another general

	@function onGeneralAssaultsGeneral
	@tparam namedCharacter attacker
	@tparam namedCharacter defender

	@usage
	function onGeneralAssaultsGeneral(attacker,defender)
	-something
	end
	*/
	onGeneralAssaultsGeneralFunc = new sol::function(luaState["onGeneralAssaultsGeneral"]);
	checkLuaFunc(&onGeneralAssaultsGeneralFunc);

	/***
	An assault has taken place

	@function onGeneralAssaultsResidence
	@tparam namedCharacter attacker
	@tparam settlementStruct settlement nil if it is fort
	@tparam fortStruct fort nil if it is settlement

	@usage
	function onGeneralAssaultsResidence(attacker,settlement,fort)
		if(settlement~=nil)
		then
			-settlement
		else
			-fort
		end

	end
	*/
	onGeneralAssaultsResidenceFunc = new sol::function(luaState["onGeneralAssaultsResidence"]);
	checkLuaFunc(&onGeneralAssaultsResidenceFunc);

	/***
	Settlement captured

	@function onGeneralCaptureSettlement
	@tparam namedCharacter attacker
	@tparam settlementStruct settlement

	@usage
	function onGeneralCaptureSettlement(attacker,settlement)
	--something
	end
	*/
	onGeneralCaptureSettlementFunc = new sol::function(luaState["onGeneralCaptureSettlement"]);
	checkLuaFunc(&onGeneralCaptureSettlementFunc);


	/***
	A General has captured a residence(fort, watchtower, check it yourself)

	@function onGeneralCaptureResidence
	@tparam namedCharacter attacker

	@usage
	function onGeneralCaptureResidence(attacker)
	--something
	end
	*/
	onGeneralCaptureResidenceFunc = new sol::function(luaState["onGeneralCaptureResidence"]);
	checkLuaFunc(&onGeneralCaptureResidenceFunc);


	/***
	@function onSiegeEquipmentCompleted
	@tparam settlementStruct settlement nil if it is fort
	@tparam fortStruct fort nil if it is settlement

	@usage
	--something
	*/

	onSiegeEquipmentCompletedFunc = new sol::function(luaState["onSiegeEquipmentCompleted"]);
	checkLuaFunc(&onSiegeEquipmentCompletedFunc);

	/***
	@function onPostBattle
	@tparam namedCharacter character

	@usage
	--something
	*/

	onPostBattleFunc = new sol::function(luaState["onPostBattle"]);
	checkLuaFunc(&onPostBattleFunc);

	/***
	@function onMultiTurnMove
	@tparam namedCharacter character

	@usage
	--something
	*/
	onMultiTurnMoveFunc = new sol::function(luaState["onMultiTurnMove"]);
	checkLuaFunc(&onMultiTurnMoveFunc);

	/***
	@function onSettlementSelected
	@tparam settlementStruct settlement

	@usage
	--something
	*/
	onSettlementSelectedFunc = new sol::function(luaState["onSettlementSelected"]);
	checkLuaFunc(&onSettlementSelectedFunc);

	/***
	@function onSettlementUpgraded
	@tparam settlementStruct settlement

	@usage
	--something
	*/

	onSettlementUpgradedFunc = new sol::function(luaState["onSettlementUpgraded"]);
	checkLuaFunc(&onSettlementUpgradedFunc);

	/***
	@function onSettlementConverted
	@tparam settlementStruct settlement

	@usage
	--something
	*/
	onSettlementConvertedFunc = new sol::function(luaState["onSettlementConverted"]);
	checkLuaFunc(&onSettlementConvertedFunc);

	/***
	@function onCityRiots
	@tparam settlementStruct settlement

	@usage
	--something
	*/

	onCityRiotsFunc = new sol::function(luaState["onCityRiots"]);
	checkLuaFunc(&onCityRiotsFunc);

	/***
	@function onUngarrisonedSettlement
	@tparam settlementStruct settlement

	@usage
	--something
	*/

	onUngarrisonedSettlementFunc = new sol::function(luaState["onUngarrisonedSettlement"]);
	checkLuaFunc(&onUngarrisonedSettlementFunc);

	/***
	@function onUngarrisonedFort
	@tparam forttruct settlement

	@usage
	--something
	*/
	onUngarrisonedFortFunc = new sol::function(luaState["onUngarrisonedFort"]);
	checkLuaFunc(&onUngarrisonedFortFunc);

	/***
	@function onGiveSettlement
	@tparam settlementStruct settlement
	@tparam factionStruct fac1
	@tparam factionStruct fac2


	@usage
	--something
	*/
	onGiveSettlementFunc = new sol::function(luaState["onGiveSettlement"]);
	checkLuaFunc(&onGiveSettlementFunc);

	/***
	@function onOccupySettlement
	@tparam namedharacter char1
	@tparam settlementStruct settlement


	@usage
	--something
	*/
	onOccupySettlementFunc = new sol::function(luaState["onOccupySettlement"]);
	checkLuaFunc(&onOccupySettlementFunc);

	/***
	@function onExterminatePopulation
	@tparam namedharacter char1
	@tparam settlementStruct settlement


	@usage
	--something
	*/
	onExterminatePopulationFunc = new sol::function(luaState["onExterminatePopulation"]);
	checkLuaFunc(&onExterminatePopulationFunc);

	/***
	@function onSackSettlement
	@tparam namedharacter char1
	@tparam settlementStruct settlement


	@usage
	--something
	*/

	onSackSettlementFunc = new sol::function(luaState["onSackSettlement"]);
	checkLuaFunc(&onSackSettlementFunc);


	/***
	@function onAddedToBuildingQueue
	@tparam settlementStruct settlement
	@tparam string buildNme


	@usage
	--something
	*/
	onAddedToBuildingQueueFunc = new sol::function(luaState["onAddedToBuildingQueue"]);
	checkLuaFunc(&onAddedToBuildingQueueFunc);

	/***
	@function onBuildingDestroyed
	@tparam settlementStruct settlement
	@tparam string buildNme


	@usage
	--something
	*/
	onBuildingDestroyedFunc = new sol::function(luaState["onBuildingDestroyed"]);
	checkLuaFunc(&onBuildingDestroyedFunc);

	/***
	@function onBuildingCompleted
	@tparam factionStruct fac
	@tparam settlementStruct settlement


	@usage
	--something
	*/

	onBuildingCompletedFunc = new sol::function(luaState["onBuildingCompleted"]);
	checkLuaFunc(&onBuildingCompletedFunc);

	/***
	@function onEventCounter
	@tparam string counter

	@usage
	--something
	*/
	onEventCounterFunc = new sol::function(luaState["onEventCounter"]);
	checkLuaFunc(&onEventCounterFunc);

	/***
	@function onFactionExcommunicated
	@tparam factionStruct fac

	@usage
	--something
	*/
	onFactionExcommunicatedFunc = new sol::function(luaState["onFactionExcommunicated"]);
	checkLuaFunc(&onFactionExcommunicatedFunc);

	/***
	@function onDisaster
	@tparam int eventType

	@usage
	--something
	*/
	onDisasterFunc = new sol::function(luaState["onDisaster"]);
	checkLuaFunc(&onDisasterFunc);

	/***
	@function onHordeFormed
	@tparam factionStruct fac

	@usage
	--something
	*/

	onHordeFormedFunc = new sol::function(luaState["onHordeFormed"]);
	checkLuaFunc(&onHordeFormedFunc);

	/***
	@function onAddedToTrainingQueue
	@tparam settlementStruct sett
	@tparam string unitName

	@usage
	--something
	*/
	onAddedToTrainingQueueFunc = new sol::function(luaState["onAddedToTrainingQueue"]);
	checkLuaFunc(&onAddedToTrainingQueueFunc);


	/***
	@function onUnitDisbanded
	@tparam factionStruct fac
	@tparam unit unit

	@usage
	--something
	*/
	onUnitDisbandedFunc = new sol::function(luaState["onUnitDisbanded"]);
	checkLuaFunc(&onUnitDisbandedFunc);

	/***
	@function onUnitTrained
	@tparam factionStruct fac
	@tparam settlementStruct sett
	@tparam unit unit

	@usage
	--something
	*/
	onUnitTrainedFunc = new sol::function(luaState["onUnitTrained"]);
	checkLuaFunc(&onUnitTrainedFunc);

	/***
	@function onAgentCreated
	@tparam factionStruct fac
	@tparam int agentType
	@tparam settlementStruct sett

	@usage
	--something
	*/
	onAgentCreatedFunc = new sol::function(luaState["onAgentCreated"]);
	checkLuaFunc(&onAgentCreatedFunc);

	/***
	@function onObjSeen
	@tparam factionStruct fac
	@tparam factionStruct fac2
	@tparam int xCoord
	@tparam int yCoord

	@usage
	--something
	*/
	onObjSeenFunc = new sol::function(luaState["onObjSeen"]);
	checkLuaFunc(&onObjSeenFunc);

	/***
	@function onTileSeen
	@tparam factionStruct fac
	@tparam int xCoord
	@tparam int yCoord

	@usage
	--something
	*/

	onTileSeenFunc = new sol::function(luaState["onTileSeen"]);
	checkLuaFunc(&onTileSeenFunc);


	/***
	@function onGameReloaded
	@tparam int something

	@usage
	--something
	*/
	onGameReloadedFunc = new sol::function(luaState["onGameReloaded"]);
	checkLuaFunc(&onGameReloadedFunc);

	/***
	@function onTransgression
	@tparam factionStruct fac1
	@tparam string description
	@tparam factionStruct fac2

	@usage
	--something
	*/
	onTransgressionFunc = new sol::function(luaState["onTransgression"]);
	checkLuaFunc(&onTransgressionFunc);



	/***
	@function onPopeAcceptsCrusadeTarget
	@tparam crusadeStruct crusade
	@tparam settlementStruct target

	@usage
	--something
	*/
	onPopeAcceptsCrusadeTargetFunc = new sol::function(luaState["onPopeAcceptsCrusadeTarget"]);
	checkLuaFunc(&onPopeAcceptsCrusadeTargetFunc);

	/***
	@function onCrusadeCalled
	@tparam crusadeStruct crusade
	@tparam settlementStruct target

	@usage
	--something
	*/
	onCrusadeCalledFunc = new sol::function(luaState["onCrusadeCalled"]);
	checkLuaFunc(&onCrusadeCalledFunc);

	/***
	@function onCrusadeEnds
	@tparam crusadeStruct crusade
	@tparam settlementStruct target

	@usage
	--something
	*/
	onCrusadeEndsFunc = new sol::function(luaState["onCrusadeEnds"]);
	checkLuaFunc(&onCrusadeEndsFunc);


	/***
	@function onPopeRejectsCrusadeTarget
	@tparam crusadeStruct crusade
	@tparam settlementStruct target

	@usage
	--something
	*/
	onPopeRejectsCrusadeTargetFunc = new sol::function(luaState["onPopeRejectsCrusadeTarget"]);
	checkLuaFunc(&onPopeRejectsCrusadeTargetFunc);

	/***
	@function onArmyTakesCrusadeTarget
	@tparam crusadeStruct crusade
	@tparam settlementStruct target
	@tparam stackStruct army

	@usage
	--something
	*/
	onArmyTakesCrusadeTargetFunc = new sol::function(luaState["onArmyTakesCrusadeTarget"]);
	checkLuaFunc(&onArmyTakesCrusadeTargetFunc);

	/***
	@function onUnitsDesertCrusade
	@tparam crusadeStruct crusade
	@tparam settlementStruct target
	@tparam factionStruct fac

	@usage
	--something
	*/

	onUnitsDesertCrusadeFunc = new sol::function(luaState["onUnitsDesertCrusade"]);
	checkLuaFunc(&onUnitsDesertCrusadeFunc);


	/***
	@function onPopeElected
	@tparam factionStruct fac
	@tparam factionStruct fac2

	@usage
	--something
	*/

	onPopeElectedFunc = new sol::function(luaState["onPopeElected"]);
	checkLuaFunc(&onPopeElectedFunc);

	/***
	@function onVotedForPope
	@tparam factionStruct fac

	@usage
	--something
	*/


	onVotedForPopeFunc = new sol::function(luaState["onVotedForPope"]);
	checkLuaFunc(&onVotedForPopeFunc);

	/***
	@function onAssassinCaughtAttackingPope
	@tparam factionStruct fac

	@usage
	--something
	*/


	onAssassinCaughtAttackingPopeFunc = new sol::function(luaState["onAssassinCaughtAttackingPope"]);
	checkLuaFunc(&onAssassinCaughtAttackingPopeFunc);

	/***
	@function onInquisitorAppointed
	@tparam factionStruct fac
	@tparam settlementStruct sett

	@usage
	--something
	*/

	onInquisitorAppointedFunc = new sol::function(luaState["onInquisitorAppointed"]);
	checkLuaFunc(&onInquisitorAppointedFunc);



	/***
	@function onSettlementPanelOpen
	@tparam settlementStruct sett

	@usage
	--something
	*/

	onSettlementPanelOpenFunc = new sol::function(luaState["onSettlementPanelOpen"]);
	checkLuaFunc(&onSettlementPanelOpenFunc);


	/***
	@function onFinancesPanelOpen
	@tparam factionStruct fac

	@usage
	--something
	*/

	onFinancesPanelOpenFunc = new sol::function(luaState["onFinancesPanelOpen"]);
	checkLuaFunc(&onFinancesPanelOpenFunc);

	/***
	@function onFactionSummaryPanelOpen
	@tparam factionStruct fac

	@usage
	--something
	*/

	onFactionSummaryPanelOpenFunc = new sol::function(luaState["onFactionSummaryPanelOpen"]);
	checkLuaFunc(&onFactionSummaryPanelOpenFunc);

	/***
	@function onFamilyTreePanelOpenFunc
	@tparam factionStruct fac

	@usage
	--something
	*/


	onFamilyTreePanelOpenFunc = new sol::function(luaState["onFamilyTreePanelOpenFunc"]);
	checkLuaFunc(&onFamilyTreePanelOpenFunc);

	/***
	@function onDiplomaticStandingPanelOpen
	@tparam factionStruct fac

	@usage
	--something
	*/


	onDiplomaticStandingPanelOpenFunc = new sol::function(luaState["onDiplomaticStandingPanelOpen"]);
	checkLuaFunc(&onDiplomaticStandingPanelOpenFunc);

	/***
	@function onDiplomacyPanelOpen
	@tparam factionStruct fac

	@usage
	--something
	*/

	onDiplomacyPanelOpenFunc = new sol::function(luaState["onDiplomacyPanelOpen"]);
	checkLuaFunc(&onDiplomacyPanelOpenFunc);

	/***
	@function onPreBattlePanelOpen
	@tparam factionStruct fac

	@usage
	--something
	*/

	onPreBattlePanelOpenFunc = new sol::function(luaState["onPreBattlePanelOpen"]);
	checkLuaFunc(&onPreBattlePanelOpenFunc);

	/***
	@function onNavalAutoResolvePanelOpen

	@usage
	--something
	*/

	onNavalAutoResolvePanelOpenFunc = new sol::function(luaState["onNavalAutoResolvePanelOpen"]);
	checkLuaFunc(&onNavalAutoResolvePanelOpenFunc);

	/***
	@function onCharacterPanelOpen
	@tparam namedCharacter selectedChar

	@usage
	--something
	*/


	onCharacterPanelOpenFunc = new sol::function(luaState["onCharacterPanelOpen"]);
	checkLuaFunc(&onCharacterPanelOpenFunc);


	/***
	@function onTradePanelOpen
	@tparam settlementStruct sett

	@usage
	--something
	*/


	onTradePanelOpenFunc = new sol::function(luaState["onTradePanelOpen"]);
	checkLuaFunc(&onTradePanelOpenFunc);

	/***
	@function onRequestBuildingAdvice
	@tparam settlementStruct sett

	@usage
	--something
	*/



	onRequestBuildingAdviceFunc = new sol::function(luaState["onRequestBuildingAdvice"]);
	checkLuaFunc(&onRequestBuildingAdviceFunc);

	/***
	@function onRequestTrainingAdvice
	@tparam settlementStruct sett
	@tparam eduEntry recommendedUnitEntry

	@usage
	--something
	*/


	onRequestTrainingAdviceFunc = new sol::function(luaState["onRequestTrainingAdvice"]);
	checkLuaFunc(&onRequestTrainingAdviceFunc);

	/***
	@function onMessageOpen
	@tparam factionStruct fac
	@tparam int msgType

	@usage
	--something
	*/


	onMessageOpenFunc = new sol::function(luaState["onMessageOpen"]);
	checkLuaFunc(&onMessageOpenFunc);

	/***
	@function onIncomingMessage
	@tparam factionStruct fac
	@tparam int msgType

	@usage
	--something
	*/


	onIncomingMessageFunc = new sol::function(luaState["onIncomingMessage"]);
	checkLuaFunc(&onIncomingMessageFunc);

	/***
	@function onMessageClosed
	@tparam int msgType

	@usage
	--something
	*/

	onMessageClosedFunc = new sol::function(luaState["onMessageClosed"]);
	checkLuaFunc(&onMessageClosedFunc);

	/***
	@function onButtonPressed
	@tparam string buttonName

	@usage
	--something
	*/


	onButtonPressedFunc = new sol::function(luaState["onButtonPressed"]);
	checkLuaFunc(&onButtonPressedFunc);

	/***
	@function onScrollClosed
	@tparam string scrollName

	@usage
	--something
	*/

	onScrollClosedFunc = new sol::function(luaState["onScrollClosed"]);
	checkLuaFunc(&onScrollClosedFunc);

	/***
	@function onScrollOpened
	@tparam string scrollName

	@usage
	--something
	*/


	onScrollOpenedFunc = new sol::function(luaState["onScrollOpened"]);
	checkLuaFunc(&onScrollOpenedFunc);

	/***
	@function onUIElementVisible
	@tparam string elementName

	@usage
	--something
	*/


	onUIElementVisibleFunc = new sol::function(luaState["onUIElementVisible"]);
	checkLuaFunc(&onUIElementVisibleFunc);

	/***
	@function onScrollAdviceRequested
	@tparam string scrollName

	@usage
	--something
	*/


	onScrollAdviceRequestedFunc = new sol::function(luaState["onScrollAdviceRequested"]);
	checkLuaFunc(&onScrollAdviceRequestedFunc);

	/***
	@function onSettlementScrollAdviceRequested
	@tparam settlementStruct sett
	@tparam string scrollName

	@usage
	--something
	*/

	onSettlementScrollAdviceRequestedFunc = new sol::function(luaState["onSettlementScrollAdviceRequested"]);
	checkLuaFunc(&onSettlementScrollAdviceRequestedFunc);

	/***
	@function onPreBattleScrollAdviceRequested

	@usage
	--something
	*/


	onPreBattleScrollAdviceRequestedFunc = new sol::function(luaState["onPreBattleScrollAdviceRequested"]);
	checkLuaFunc(&onPreBattleScrollAdviceRequestedFunc);

	/***
	@function onNavalPreBattleScrollAdviceRequested

	@usage
	--something
	*/

	onNavalPreBattleScrollAdviceRequestedFunc = new sol::function(luaState["onNavalPreBattleScrollAdviceRequested"]);
	checkLuaFunc(&onNavalPreBattleScrollAdviceRequestedFunc);

	/***
	@function onCollegeOfCardinalsPanelOpen
	@tparam collegeCardinalsStruct college

	@usage
	--something
	*/


	onCollegeOfCardinalsPanelOpenFunc = new sol::function(luaState["onCollegeOfCardinalsPanelOpen"]);
	checkLuaFunc(&onCollegeOfCardinalsPanelOpenFunc);





	if (onPluginLoad != nullptr)
	{
		tryLua((*onPluginLoad)());
	}
}
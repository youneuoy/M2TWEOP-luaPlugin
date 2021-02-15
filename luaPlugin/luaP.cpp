#include "luaP.h"
std::string luaP::logS;


void replaceAll2(std::string& s, const std::string& search, const std::string& replace) {
	for (size_t pos = 0; ; pos += replace.length())
	{
		pos = s.find(search, pos);
		if (pos == std::string::npos) break;

		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

void poststring(const char* sv) 
{ 
	if (sv == nullptr)return;

	luaP::logS+=sv;
	luaP::logS+= +"\n";
}

int l_my_print(lua_State* L) {
	int nargs = lua_gettop(L);
	for (int i = 1; i <= nargs; ++i) {
		poststring(luaL_tolstring(L, i, nullptr));
		lua_pop(L, 1); // remove the string
	}
	return 0;
}

const char* luaP::runScriptS(std::string* script)
{
	const char* retS=nullptr;

	bool err= luaL_dostring(L, script->c_str());
	if (err)
	{
		retS = lua_tostring(L, -1);
	}

	return retS;
}
static const struct luaL_Reg printlib[] = {
  {"print", l_my_print},
  {NULL, NULL} /* end of array */
};
bool luaP::checkVar(const char* gName,int variable)
{
	LuaRef retF = getGlobal(L, gName);
	if (retF.isNumber()==false)
	{
		return false;
	}
	
	return (retF == variable);

}
bool luaP::init(std::string& luaFilePath, std::string& modPath)
{
	luaPath = modPath + "\\youneuoy_Data\\plugins\\lua";
	L = luaL_newstate();
	std::string packagePS = "package.path = '";
	packagePS += modPath;
	packagePS += "\\youneuoy_Data\\plugins\\lua\\?.lua;'..package.path ";
	std::string f = "\\";
	std::string r = "/";
	replaceAll2(packagePS, f, r);
	luaL_openlibs(L);


	lua_getglobal(L, "_G");
	luaL_setfuncs(L, printlib, 0);
	lua_pop(L, 1);
	//luaL_dostring(L, "package.path = 'D://Game.Helper/Lua/libs/?.lua;'..package.path ");
	luaL_dostring(L, packagePS.c_str());

	luaL_dofile(L, luaFilePath.c_str());

	if (lua_tostring(L, -1)!=nullptr)
	{
		MessageBoxA(NULL, lua_tostring(L, -1), "info", NULL);
	}
	lua_pcall(L, 0, 0, 0);

	getGlobalNamespace(L)
		.beginNamespace("M2TWEOP")
			.addFunction("getModPath",&m2tweopHelpers::getModPath)
			.addFunction("getPluginPath",&m2tweopHelpers::getLuaPath)

		.endNamespace()
		.beginNamespace("stratmap")
		//strategic map data and functions
			.beginNamespace("objects")
				//namespace for different objects
				.addFunction("addModelToGame", &objectsHelpers::addModelToGame)
				.addFunction("setModel", &objectsHelpers::setModel)
				.addFunction("replaceTile", &objectsHelpers::replaceTile)
			.endNamespace()
			.beginNamespace("camera")
				.addFunction("move",&cameraHelpers::moveStratCamera)
				.addFunction("jump",&cameraHelpers::snapStratCamera)
				.addFunction("setZoom",&cameraHelpers::zoomStratCamera)
			.endNamespace()
			.beginNamespace("game")
				.addFunction("getFactionsCount", &gameHelpers::getFactionsCount)
				.addFunction("getFaction", &gameHelpers::getFaction)
				.addFunction("createCharacterByString", &gameHelpers::createCharacter)
				.addFunction("createArmy", &gameHelpers::createArmy)
				.addFunction("createUnitN", &gameHelpers::createUnitN)
				.addFunction("createUnitIdx", &gameHelpers::createUnitIdx)
			.endNamespace()
		.endNamespace();

	getGlobalNamespace(L)
		.beginClass<unit>("unit")
			.addData<EduEntry*>("eduEntry", &unit::eduEntry)
			.addProperty("movePoints",
				&unitHelpers::getMovepoints, &unitHelpers::setMovepoints)
			.addProperty<int>("number", &unit::number,&unitHelpers::setSoldiersCount)
			.addData<int>("numberTact", &unit::numberTact, false)
			.addData<int>("numberMax", &unit::numberMax)
			.addFunction("kill",&unitHelpers::killUnit)
			.addFunction("setParams",&unitHelpers::setUnitParams)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<general>("character")
			.addData<int>("xCoord", &general::xCoord)
			.addData<int>("yCoord", &general::yCoord)
			.addData<generalCharacterictics*>("namedCharacter", &general::genChar)
			.addData<unit*>("bodyguards", &general::bodyguards)
			.addData<float>("movepointsMax", &general::movepointsMax)
			.addData<float>("movepointsModifier", &general::movepointsModifier)
			.addProperty("movepoints",
				&generalHelpers::getMovepoints, &generalHelpers::setMovepoints)
			.addProperty("ability",
				&luaGetSetFuncs::getStringProperty<generalStruct_abilityID>, &luaGetSetFuncs::setStringProperty<generalStruct_abilityID>)
			.addFunction("moveToTile", &generalHelpers::moveToTile)
			.addFunction("reposition", &generalHelpers::reposition)
			.addFunction("siegeSettlement", &generalHelpers::siegeSettlement)
			.addFunction("kill", &generalHelpers::killGeneral)
			.addFunction("setBodyguardUnit", &generalHelpers::setBodyguard)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<generalCharacterictics>("namedCharacter")
			.addData<UINT32>("index", &generalCharacterictics::index,false)
			.addData<general*>("character", &generalCharacterictics::gen)
			.addProperty("shortName",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_shortName>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_shortName>)
			.addProperty("fullName",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_fullName>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_fullName>)
			.addProperty("label",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_label>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_label>)
			.addProperty("modelName",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_modelName>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_modelName>)
			.addData<unsigned char>("status", &generalCharacterictics::status)
			.addData<int>("command", &generalCharacterictics::authority)
			.addData<int>("loyalty", &generalCharacterictics::loyality)
			.addData<int>("piety", &generalCharacterictics::piety)
			.addData<int>("chivalryAndDread", &generalCharacterictics::nobility)
			.addData<int>("authority", &generalCharacterictics::leaderAutority)
			.addFunction("getAncillary", &generalCharactericticsHelpers::getAnchillary)
			.addData<UINT32>("ancNum", &generalCharacterictics::anchNum)
			.addData<float>("yearOfBirth", &generalCharacterictics::yearOfBirth)
			.addData<factionStruct*>("faction", &generalCharacterictics::faction)
			.addData<int>("subFaction", &generalCharacterictics::subFaction)
			.addData<generalCharacterictics*>("parent", &generalCharacterictics::parent)
			.addData<generalCharacterictics*>("spouse", &generalCharacterictics::spouse)
			.addProperty("portrait",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_portrait>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_portrait>)
			.addProperty("portrait2",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_portrait2>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_portrait2>)
			.addProperty("portrait_custom",
				&luaGetSetFuncs::getStringProperty<generalCharactericticsStruct_portrait_custom>, &luaGetSetFuncs::setStringProperty<generalCharactericticsStruct_portrait_custom>)
		
			.addFunction("addAncillary", &generalCharactericticsHelpers::addAnchillary)
			.addFunction("removeAncillary", &generalCharactericticsHelpers::removeAnchillary)
		.endClass();


	getGlobalNamespace(L)
		.beginClass<anchillary>("ancillary")					
			.addData<UINT32>("index", &anchillary::index)
			.addProperty("name",
				&luaGetSetFuncs::getStringProperty<anchillaryStruct_name>, &luaGetSetFuncs::setStringProperty<anchillaryStruct_name>)
			.addProperty("imagePath",
				&luaGetSetFuncs::getStringProperty<anchillaryStruct_imagePath>, &luaGetSetFuncs::setStringProperty<anchillaryStruct_imagePath>)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<EduEntry>("EduEntry")
			.addProperty("Type",
				&luaGetSetFuncs::getStringProperty<EduEntryStruct_portrait_Type>, &luaGetSetFuncs::setStringProperty<EduEntryStruct_portrait_Type>)
			.addData<int32_t>("Dictionary", &EduEntry::Dictionary)
			.addData<int32_t>("Index", &EduEntry::Index)
			.addData<int32_t>("UnitCreatedCounter", &EduEntry::UnitCreatedCounter)
		.endClass();


	getGlobalNamespace(L)
		.beginClass<factionStruct>("factionStruct")
			.addData<int>("dipNum", &factionStruct::dipNum)
			.addProperty("ai_label",
				&factionHelpers::getStringProperty<factionStruct_ai_label>, &factionHelpers::setStringProperty<factionStruct_ai_label>)
			.addData<settlementStruct*>("capital", &factionStruct::capital)
			.addData<generalCharacterictics*>("leader", &factionStruct::leader)
			.addData<generalCharacterictics*>("heir", &factionStruct::heir)
			.addFunction("getFactionName",&factionHelpers::getFactionName)
			.addData<int>("isPlayerControlled", &factionStruct::isPlayerControlled)
			.addFunction("getNamedCharacter", &factionHelpers::getCharacterFromFullList)
			.addData<int>("numOfNamedCharacters", &factionStruct::numOfCharactersAll)
			.addFunction("getCharacter", &factionHelpers::getCharacterFromGeneralsList)
			.addData<int>("numOfCharacters", &factionStruct::numOfCharacters)
			.addFunction("getStack", &factionHelpers::getStack)
			.addData<int>("stackNum", &factionStruct::stackNum)
			.addFunction("getSettlement", &factionHelpers::getSettlement)
			.addData<int>("settlementsNum", &factionStruct::settlementsNum)
			.addFunction("getFort", &factionHelpers::getFort)
			.addData<int>("fortsNum", &factionStruct::fortsNum)
			.addFunction("getPort", &factionHelpers::getPort)
			.addData<int>("portsNum", &factionStruct::portBuildingsNum)
			.addData<UINT32>("religion", &factionStruct::religion)
			.addData<int>("money", &factionStruct::money)
		.endClass();



	getGlobalNamespace(L)
		.beginClass<settlementStruct>("settlementStruct")
			.addData<general*>("gubernator", &settlementStruct::gubernator)
			.addData<UINT32>("xCoord", &settlementStruct::xCoord,false)
			.addData<UINT32>("yCoord", &settlementStruct::yCoord, false)
			.addData<stackStruct*>("army", &settlementStruct::army)
			.addProperty("name",
				&settlementHelpers::getStringProperty<settlementStruct_name>, &settlementHelpers::setStringProperty<settlementStruct_name>)
			.addData<factionStruct*>("ownerFaction", &settlementStruct::ownerFac)
			.addData<int>("level", &settlementStruct::level)
			.addData<int>("fac_creatorNum", &settlementStruct::fac_creatorModNum)
			.addData<unsigned char>("isCastle", &settlementStruct::isCastle)
			.addData<UINT32>("regionNumber", &settlementStruct::regionNumber)
			.addData<uchar>("isProvokedRebellion", &settlementStruct::isProvokedRebellion)
			.addFunction("getBuilding", &settlementHelpers::getBuilding)
			.addData<int>("buldingsNum", &settlementStruct::buldingsNum)
			.addFunction("getResource", &settlementHelpers::getResource)
			.addData<int>("resourcesNum", &settlementStruct::resourcesNum)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<resStrat>("resStrat")
			.addData<int>("xCoord", &resStrat::xCoord)
			.addData<int>("yCoord", &resStrat::yCoord)
			.addFunction("setStratModel", &resourcesHelpers::setModel)
			.addFunction("getResourceCode", &resourcesHelpers::getResourceCode)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<stackStruct>("stackStruct")
			.addData<factionStruct*>("faction", &stackStruct::faction)
			.addFunction("getUnit", &stackStructHelpers::getUnit)
			.addData<int>("numOfUnits", &stackStruct::numOfUnits)
			.addFunction("getCharacter", &stackStructHelpers::getCharacter)
			.addData<int>("numOfCharacters", &stackStruct::charactersNum)
			.addData<stackStruct*>("boardedArmy", &stackStruct::boardedArmy)
			.addData<portBuildingStruct*>("blockedPort", &stackStruct::blockedPort)
			.addData<general*>("leader", &stackStruct::gen)
			.addFunction("findInSettlement", &stackStructHelpers::findInSettlement)
			.addFunction("findInFort", &stackStructHelpers::findInFort)
			.addData<int>("totalStrength", &stackStruct::totalStrength)
			.addData<float>("reform_point_x", &stackStruct::reform_point_x)
			.addData<float>("reform_point_y", &stackStruct::reform_point_y)
			.addFunction("addUnit", &stackStructHelpers::addUnitToArmy)
			.addFunction("attackArmy", &stackStructHelpers::attackArmy)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<building>("building")
			.addData<building_data*>("buildingData", &building::bData)
			.addData<int>("level", &building::level)
			.addData<int>("hp", &building::hp)
			.addData<settlementStruct*>("settlement", &building::settlement)
		.endClass();

	getGlobalNamespace(L)
		.beginClass<building_data>("building_data")
		.addProperty("type",
			&buildingStructHelpers::getStringProperty<building_dataStruct_type>, &buildingStructHelpers::setStringProperty<building_dataStruct_type>)
			.addData<buildingDrawInfo*>("buildingInfo", &building_data::drawInfo)
		.endClass();
	
	getGlobalNamespace(L)
		.beginClass<buildingDrawInfo>("buildingDrawInfo")
		.addProperty("name",
			&buildingStructHelpers::getStringProperty<buildingDrawInfoStruct_name>, &buildingStructHelpers::setStringProperty<buildingDrawInfoStruct_name>)
		.endClass();


	onPluginLoadF();
	return true;
}




void checkRef(LuaRef** lRef)
{
	if ((*lRef)->isFunction() == false)
	{
		*lRef = nullptr;
	}
}
void luaP::onPluginLoadF()
{
	onPluginLoad  = new LuaRef(getGlobal(L, "onPluginLoad"));
	checkRef(&onPluginLoad);

	onChangeTurnNumFunc = new LuaRef(getGlobal(L, "onChangeTurnNum"));
	checkRef(&onChangeTurnNumFunc);

	onCharacterSelectedFunc = new LuaRef(getGlobal(L, "onCharacterSelected"));
	checkRef(&onCharacterSelectedFunc);

	onPreFactionTurnStartFunc = new LuaRef(getGlobal(L, "onPreFactionTurnStart"));
	checkRef(&onPreFactionTurnStartFunc);
	
	onFactionTurnStartFunc = new LuaRef(getGlobal(L, "onFactionTurnStart"));
	checkRef(&onFactionTurnStartFunc);

	onFactionTurnEndFunc = new LuaRef(getGlobal(L, "onFactionTurnEnd"));
	checkRef(&onFactionTurnEndFunc);

	onFactionNewCapitalFunc = new LuaRef(getGlobal(L, "onFactionNewCapital"));
	checkRef(&onFactionNewCapitalFunc);

	onFactionWarDeclaredFunc = new LuaRef(getGlobal(L, "onFactionWarDeclared"));
	checkRef(&onFactionWarDeclaredFunc);

	onFactionAllianceDeclaredFunc = new LuaRef(getGlobal(L, "onFactionAllianceDeclared"));
	checkRef(&onFactionAllianceDeclaredFunc);

	onFactionTradeAgreementMadeFunc = new LuaRef(getGlobal(L, "onFactionTradeAgreementMade"));
	checkRef(&onFactionTradeAgreementMadeFunc);

	onFactionBreakAllianceFunc = new LuaRef(getGlobal(L, "onFactionBreakAlliance"));
	checkRef(&onFactionBreakAllianceFunc);
	
	onGiveMoneyFunc = new LuaRef(getGlobal(L, "onGiveMoney"));
	checkRef(&onGiveMoneyFunc);
		
	onUpdateAttitudeFunc = new LuaRef(getGlobal(L, "onUpdateAttitude"));
	checkRef(&onUpdateAttitudeFunc);

	onDemeanourFunc = new LuaRef(getGlobal(L, "onDemeanour"));
	checkRef(&onDemeanourFunc);

	
	onGeneralAssaultsGeneralFunc = new LuaRef(getGlobal(L, "onGeneralAssaultsGeneral"));
	checkRef(&onGeneralAssaultsGeneralFunc);
		
	onGeneralAssaultsResidenceFunc = new LuaRef(getGlobal(L, "onGeneralAssaultsResidence"));
	checkRef(&onGeneralAssaultsResidenceFunc);
	
		
	onGeneralCaptureSettlementFunc = new LuaRef(getGlobal(L, "onGeneralCaptureSettlement"));
	checkRef(&onGeneralCaptureSettlementFunc);
		
		
	onGeneralCaptureResidenceFunc = new LuaRef(getGlobal(L, "onGeneralCaptureResidence"));
	checkRef(&onGeneralCaptureResidenceFunc);
			
	onSiegeEquipmentCompletedFunc = new LuaRef(getGlobal(L, "onSiegeEquipmentCompleted"));
	checkRef(&onSiegeEquipmentCompletedFunc);

			
	onPostBattleFunc = new LuaRef(getGlobal(L, "onPostBattle"));
	checkRef(&onPostBattleFunc);

				
	onMultiTurnMoveFunc = new LuaRef(getGlobal(L, "onMultiTurnMove"));
	checkRef(&onMultiTurnMoveFunc);
					
	onSettlementSelectedFunc = new LuaRef(getGlobal(L, "onSettlementSelected"));
	checkRef(&onSettlementSelectedFunc);
	
					
	onSettlementUpgradedFunc = new LuaRef(getGlobal(L, "onSettlementUpgraded"));
	checkRef(&onSettlementUpgradedFunc);

	onSettlementConvertedFunc = new LuaRef(getGlobal(L, "onSettlementConverted"));
	checkRef(&onSettlementConvertedFunc);

	
	onCityRiotsFunc = new LuaRef(getGlobal(L, "onCityRiots"));
	checkRef(&onCityRiotsFunc);

	onUngarrisonedSettlementFunc = new LuaRef(getGlobal(L, "onUngarrisonedSettlement"));
	checkRef(&onUngarrisonedSettlementFunc);

	
	onUngarrisonedFortFunc = new LuaRef(getGlobal(L, "onUngarrisonedFort"));
	checkRef(&onUngarrisonedFortFunc);

	onGiveSettlementFunc = new LuaRef(getGlobal(L, "onGiveSettlement"));
	checkRef(&onGiveSettlementFunc);
	
	onOccupySettlementFunc = new LuaRef(getGlobal(L, "onOccupySettlement"));
	checkRef(&onOccupySettlementFunc);
		
	onExterminatePopulationFunc = new LuaRef(getGlobal(L, "onExterminatePopulation"));
	checkRef(&onExterminatePopulationFunc);
			
	onSackSettlementFunc = new LuaRef(getGlobal(L, "onSackSettlement"));
	checkRef(&onSackSettlementFunc);
				
	onAddedToBuildingQueueFunc = new LuaRef(getGlobal(L, "onAddedToBuildingQueue"));
	checkRef(&onAddedToBuildingQueueFunc);
					
	onBuildingDestroyedFunc = new LuaRef(getGlobal(L, "onBuildingDestroyed"));
	checkRef(&onBuildingDestroyedFunc);
						
	onBuildingCompletedFunc = new LuaRef(getGlobal(L, "onBuildingCompleted"));
	checkRef(&onBuildingCompletedFunc);

							
	onEventCounterFunc = new LuaRef(getGlobal(L, "onEventCounter"));
	checkRef(&onEventCounterFunc);
								
	onFactionExcommunicatedFunc = new LuaRef(getGlobal(L, "onFactionExcommunicated"));
	checkRef(&onFactionExcommunicatedFunc);
								
	onDisasterFunc = new LuaRef(getGlobal(L, "onDisaster"));
	checkRef(&onDisasterFunc);
									
	onHordeFormedFunc = new LuaRef(getGlobal(L, "onHordeFormed"));
	checkRef(&onHordeFormedFunc);

	onAddedToTrainingQueueFunc = new LuaRef(getGlobal(L, "onAddedToTrainingQueue"));
	checkRef(&onAddedToTrainingQueueFunc);
	
	onUnitDisbandedFunc = new LuaRef(getGlobal(L, "onUnitDisbanded"));
	checkRef(&onUnitDisbandedFunc);
		
	onUnitTrainedFunc = new LuaRef(getGlobal(L, "onUnitTrained"));
	checkRef(&onUnitTrainedFunc);
			
	onAgentCreatedFunc = new LuaRef(getGlobal(L, "onAgentCreated"));
	checkRef(&onAgentCreatedFunc);

				
	onObjSeenFunc = new LuaRef(getGlobal(L, "onObjSeen"));
	checkRef(&onObjSeenFunc);
					
	onTileSeenFunc = new LuaRef(getGlobal(L, "onTileSeen"));
	checkRef(&onTileSeenFunc);
					
	onGameReloadedFunc = new LuaRef(getGlobal(L, "onGameReloaded"));
	checkRef(&onGameReloadedFunc);
							
	onTransgressionFunc = new LuaRef(getGlobal(L, "onTransgression"));
	checkRef(&onTransgressionFunc);
			



	onPopeAcceptsCrusadeTargetFunc = new LuaRef(getGlobal(L, "onPopeAcceptsCrusadeTarget"));
	checkRef(&onPopeAcceptsCrusadeTargetFunc);
	
	onCrusadeCalledFunc = new LuaRef(getGlobal(L, "onCrusadeCalled"));
	checkRef(&onCrusadeCalledFunc);
		
	onCrusadeEndsFunc = new LuaRef(getGlobal(L, "onCrusadeEnds"));
	checkRef(&onCrusadeEndsFunc);
		
	onPopeRejectsCrusadeTargetFunc = new LuaRef(getGlobal(L, "onPopeRejectsCrusadeTarget"));
	checkRef(&onPopeRejectsCrusadeTargetFunc);
			
	onArmyTakesCrusadeTargetFunc = new LuaRef(getGlobal(L, "onArmyTakesCrusadeTarget"));
	checkRef(&onArmyTakesCrusadeTargetFunc);
				
	onUnitsDesertCrusadeFunc = new LuaRef(getGlobal(L, "onUnitsDesertCrusade"));
	checkRef(&onUnitsDesertCrusadeFunc);
					
	onPopeElectedFunc = new LuaRef(getGlobal(L, "onPopeElected"));
	checkRef(&onPopeElectedFunc);
						
	onVotedForPopeFunc = new LuaRef(getGlobal(L, "onVotedForPope"));
	checkRef(&onVotedForPopeFunc);
							
	onAssassinCaughtAttackingPopeFunc = new LuaRef(getGlobal(L, "onAssassinCaughtAttackingPope"));
	checkRef(&onAssassinCaughtAttackingPopeFunc);
								
	onInquisitorAppointedFunc = new LuaRef(getGlobal(L, "onInquisitorAppointed"));
	checkRef(&onInquisitorAppointedFunc);
						


	onSettlementPanelOpenFunc = new LuaRef(getGlobal(L, "onSettlementPanelOpen"));
	checkRef(&onSettlementPanelOpenFunc);

	onFinancesPanelOpenFunc = new LuaRef(getGlobal(L, "onFinancesPanelOpen"));
	checkRef(&onFinancesPanelOpenFunc);

	onFactionSummaryPanelOpenFunc = new LuaRef(getGlobal(L, "onFactionSummaryPanelOpen"));
	checkRef(&onFactionSummaryPanelOpenFunc);
	
	onFamilyTreePanelOpenFunc = new LuaRef(getGlobal(L, "onFamilyTreePanelOpenFunc"));
	checkRef(&onFamilyTreePanelOpenFunc);
		
	onDiplomaticStandingPanelOpenFunc = new LuaRef(getGlobal(L, "onDiplomaticStandingPanelOpen"));
	checkRef(&onDiplomaticStandingPanelOpenFunc);
			
	onDiplomacyPanelOpenFunc = new LuaRef(getGlobal(L, "onDiplomacyPanelOpen"));
	checkRef(&onDiplomacyPanelOpenFunc);
				
	onPreBattlePanelOpenFunc = new LuaRef(getGlobal(L, "onPreBattlePanelOpen"));
	checkRef(&onPreBattlePanelOpenFunc);
					
	onNavalAutoResolvePanelOpenFunc = new LuaRef(getGlobal(L, "onNavalAutoResolvePanelOpen"));
	checkRef(&onNavalAutoResolvePanelOpenFunc);
						
	onCharacterPanelOpenFunc = new LuaRef(getGlobal(L, "onCharacterPanelOpen"));
	checkRef(&onCharacterPanelOpenFunc);
							
	onTradePanelOpenFunc = new LuaRef(getGlobal(L, "onTradePanelOpen"));
	checkRef(&onTradePanelOpenFunc);
								
	onRequestBuildingAdviceFunc = new LuaRef(getGlobal(L, "onRequestBuildingAdvice"));
	checkRef(&onRequestBuildingAdviceFunc);
									
	onRequestTrainingAdviceFunc = new LuaRef(getGlobal(L, "onRequestTrainingAdvice"));
	checkRef(&onRequestTrainingAdviceFunc);
										
	onMessageOpenFunc = new LuaRef(getGlobal(L, "onMessageOpen"));
	checkRef(&onMessageOpenFunc);
											
	onIncomingMessageFunc = new LuaRef(getGlobal(L, "onIncomingMessage"));
	checkRef(&onIncomingMessageFunc);
												
	onMessageClosedFunc = new LuaRef(getGlobal(L, "onMessageClosed"));
	checkRef(&onMessageClosedFunc);
													
	onButtonPressedFunc = new LuaRef(getGlobal(L, "onButtonPressed"));
	checkRef(&onButtonPressedFunc);
														
	onScrollClosedFunc = new LuaRef(getGlobal(L, "onScrollClosed"));
	checkRef(&onScrollClosedFunc);
															
	onScrollOpenedFunc = new LuaRef(getGlobal(L, "onScrollOpened"));
	checkRef(&onScrollOpenedFunc);
																
	onUIElementVisibleFunc = new LuaRef(getGlobal(L, "onUIElementVisible"));
	checkRef(&onUIElementVisibleFunc);
																	
	onScrollAdviceRequestedFunc = new LuaRef(getGlobal(L, "onScrollAdviceRequested"));
	checkRef(&onScrollAdviceRequestedFunc);
																		
	onSettlementScrollAdviceRequestedFunc = new LuaRef(getGlobal(L, "onSettlementScrollAdviceRequested"));
	checkRef(&onSettlementScrollAdviceRequestedFunc);
																			
	onPreBattleScrollAdviceRequestedFunc = new LuaRef(getGlobal(L, "onPreBattleScrollAdviceRequested"));
	checkRef(&onPreBattleScrollAdviceRequestedFunc);
																				
	onNavalPreBattleScrollAdviceRequestedFunc = new LuaRef(getGlobal(L, "onNavalPreBattleScrollAdviceRequested"));
	checkRef(&onNavalPreBattleScrollAdviceRequestedFunc);
																					
	onCollegeOfCardinalsPanelOpenFunc = new LuaRef(getGlobal(L, "onCollegeOfCardinalsPanelOpen"));
	checkRef(&onCollegeOfCardinalsPanelOpenFunc);










	if (onPluginLoad != nullptr)
	{
		tryLua((*onPluginLoad)());
	}
}

void luaP::onChangeTurnNum(int num)
{
	if (onChangeTurnNumFunc != nullptr)
	{
		tryLua((*onChangeTurnNumFunc)(num));
	}
}

void luaP::onCharacterSelected(generalCharacterictics* gen)
{
	if (onCharacterSelectedFunc != nullptr)
	{
		tryLua((*onCharacterSelectedFunc)(gen));
	}
}

void luaP::onPreFactionTurnStart(factionStruct* fac)
{
	if (onPreFactionTurnStartFunc != nullptr)
	{
		tryLua((*onPreFactionTurnStartFunc)(fac));
	}
}

void luaP::onFactionTurnStart(factionStruct* fac)
{
	if (onFactionTurnStartFunc != nullptr)
	{
		tryLua((*onFactionTurnStartFunc)(fac));
	}
}

void luaP::onFactionTurnEnd(factionStruct* fac)
{
	if (onFactionTurnEndFunc != nullptr)
	{
		tryLua((*onFactionTurnEndFunc)(fac));
	}
}

void luaP::onFactionNewCapital(factionStruct* fac)
{
	if (onFactionNewCapitalFunc != nullptr)
	{
		tryLua((*onFactionNewCapitalFunc)(fac));
	}
}

void luaP::onFactionWarDeclared(factionStruct* fac, factionStruct* fac2)
{
	if (onFactionWarDeclaredFunc != nullptr)
	{
		tryLua((*onFactionWarDeclaredFunc)(fac, fac2));
	}
}

void luaP::onFactionAllianceDeclared(factionStruct* fac, factionStruct* fac2)
{
	if (onFactionAllianceDeclaredFunc != nullptr)
	{
		tryLua((*onFactionAllianceDeclaredFunc)(fac, fac2));
	}
}

void luaP::onFactionTradeAgreementMade(factionStruct* fac, factionStruct* fac2)
{
	if (onFactionTradeAgreementMadeFunc != nullptr)
	{
		tryLua((*onFactionTradeAgreementMadeFunc)(fac, fac2));
	}
}

void luaP::onFactionBreakAlliance(factionStruct* fac, factionStruct* fac2)
{
	if (onFactionBreakAllianceFunc != nullptr)
	{
		tryLua((*onFactionBreakAllianceFunc)(fac, fac2));
	}
}

void luaP::onGiveMoney(factionStruct* fac, factionStruct* fac2, float amount)
{
	if (onGiveMoneyFunc != nullptr)
	{
		tryLua((*onGiveMoneyFunc)(fac, fac2, amount));
	}
}

void luaP::onUpdateAttitude(factionStruct* fac, factionStruct* fac2)
{
	if (onUpdateAttitudeFunc != nullptr)
	{
		tryLua((*onUpdateAttitudeFunc)(fac, fac2));
	}
}

void luaP::onDemeanour(factionStruct* fac, factionStruct* fac2, float amount)
{
	if (onDemeanourFunc != nullptr)
	{
		tryLua((*onDemeanourFunc)(fac, fac2,amount));
	}
}

void luaP::onGeneralAssaultsGeneral(generalCharacterictics* gen, generalCharacterictics* gen2)
{
	if (onGeneralAssaultsGeneralFunc != nullptr)
	{
		tryLua((*onGeneralAssaultsGeneralFunc)(gen, gen2));
	}
}

void luaP::onGeneralAssaultsResidence(generalCharacterictics* gen, settlementStruct* sett, fortStruct* frt)
{
	if (onGeneralAssaultsResidenceFunc != nullptr)
	{
		tryLua((*onGeneralAssaultsResidenceFunc)(gen, sett, frt));
	}
}

void luaP::onGeneralCaptureSettlement(generalCharacterictics* gen, settlementStruct* sett)
{
	if (onGeneralCaptureSettlementFunc != nullptr)
	{
		tryLua((*onGeneralCaptureSettlementFunc)(gen, sett));
	}
}

void luaP::onGeneralCaptureResidence(generalCharacterictics* gen)
{
	if (onGeneralCaptureResidenceFunc != nullptr)
	{
		tryLua((*onGeneralCaptureResidenceFunc)(gen));
	}
}

void luaP::onSiegeEquipmentCompleted(settlementStruct* sett, fortStruct* frt)
{
	if (onSiegeEquipmentCompletedFunc != nullptr)
	{
		tryLua((*onSiegeEquipmentCompletedFunc)(sett,frt));
	}
}

void luaP::onPostBattle(generalCharacterictics* gen)
{
	if (onPostBattleFunc != nullptr)
	{
		tryLua((*onPostBattleFunc)(gen));
	}
}

void luaP::onMultiTurnMove(generalCharacterictics* gen)
{
	if (onMultiTurnMoveFunc != nullptr)
	{
		tryLua((*onMultiTurnMoveFunc)(gen));
	}
}

void luaP::onSettlementSelected(settlementStruct* sett)
{
	if (onSettlementSelectedFunc != nullptr)
	{
		tryLua((*onSettlementSelectedFunc)(sett));
	}
}

void luaP::onSettlementUpgraded(settlementStruct* sett)
{
	if (onSettlementUpgradedFunc != nullptr)
	{
		tryLua((*onSettlementUpgradedFunc)(sett));
	}
}

void luaP::onSettlementConverted(settlementStruct* sett)
{
	if (onSettlementConvertedFunc != nullptr)
	{
		tryLua((*onSettlementConvertedFunc)(sett));
	}
}

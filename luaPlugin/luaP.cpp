///
// Info about M2TWEOP structures and functions
//@module LUA-PLUGIN
#include "luaP.h"
#include "plugData.h"
std::string luaP::logS;


static int ourP(lua_State* L) {
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i = 1; i <= n; i++) {
		const char* s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */
		if (s == NULL)
			return luaL_error(L, LUA_QL("tostring") " must return a string to "
				LUA_QL("print"));
		if (i > 1)
		{
			luaP::logS += "\t";
			//fputs("\t", stdout);
		}
		luaP::logS += s;
		//fputs(s, stdout);
		lua_pop(L, 1);  /* pop result */
	}
	luaP::logS += "\n";
	//fputs("\n", stdout);
	return 0;
}

void replaceAll2(std::string& s, const std::string& search, const std::string& replace) {
	for (size_t pos = 0; ; pos += replace.length())
	{
		pos = s.find(search, pos);
		if (pos == std::string::npos) break;

		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}



void luaP::runScriptS(std::string* script)
{
	const char* retS = nullptr;
	auto funcResult = luaState.script(*script); 
	if (!funcResult.valid())
	{
		sol::error luaError = funcResult; 
		luaP::logS += luaError.what()+'\n';
	}
	return;
}

bool luaP::checkVar(const char* gName, int variable)
{
	sol::optional<int> scriptVar = luaState[gName];
	if (scriptVar)
	{
		return scriptVar.value()==variable;
	}

	return false;
}
sol::state* luaP::init(std::string& luaFilePath, std::string& modPath)
{
	luaPath = modPath + "\\youneuoy_Data\\plugins\\lua";
	luaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::os, sol::lib::math, sol::lib::table, sol::lib::bit32, sol::lib::io, sol::lib::ffi, sol::lib::jit);

	std::string packagePS = "package.path = '";
	packagePS += modPath;
	packagePS += "\\youneuoy_Data\\plugins\\lua\\?.lua;'..package.path ";
	std::string f = "\\";
	std::string r = "/";
	replaceAll2(packagePS, f, r);

	luaState["print"] = &ourP;
	auto funcResult = luaState.script(packagePS.c_str());
	if (!funcResult.valid())
	{
		sol::error luaError = funcResult;
		MessageBoxA(NULL, luaError.what(), "Lua exception!", NULL);
		return nullptr;
	}

	

	sol::load_result fileRes = luaState.load_file(luaFilePath.c_str());
	if (!fileRes.valid()) { // This checks the syntax of your script, but does not execute it
		sol::error luaError = fileRes;
		MessageBoxA(NULL, luaError.what(), "Lua exception!", NULL);
		return nullptr;
	}
	else
	{
		sol::protected_function_result result1 = fileRes(); // this causes the script to execute
		if (!result1.valid()) {
			sol::error luaError = result1;
			MessageBoxA(NULL, luaError.what(), "Lua exception!", NULL);
			return nullptr;
		}
	}


	///M2TWEOP table section
	//@section m2tweopTable

	/***
	Basic M2TWEOP table

	@tfield getModPath getModPath
	@tfield getPluginPath  getPluginPath
	@tfield loadTexture loadTexture
	@tfield unloadTexture unloadTexture
	@tfield setAncillariesLimit setAncillariesLimit
	@tfield unlockGameConsoleCommands unlockGameConsoleCommands
	@tfield setMaxBgSize setMaxBgSize
	@table M2TWEOP
	*/



	tables.M2TWEOPTable = luaState.create_table("M2TWEOP");


	/***
	Get mod path


	@function M2TWEOP.getModPath
	@treturn string mod path

	@usage 
	mPath=M2TWEOP.getModPath();
	print(mPath);
	*/
	tables.M2TWEOPTable["getModPath"] = &m2tweopHelpers::getModPath;
	/***
	Get path of the plugin(your lua files here)
	@function M2TWEOP.getPluginPath
	@treturn string plugin path
	@usage 
	plPath=M2TWEOP.getPluginPath();
	print(plPath);
	*/

	tables.M2TWEOPTable["getPluginPath"] = &m2tweopHelpers::getLuaPath;

	/***
	Load d3d texture
	@function M2TWEOP.loadTexture
	@tparam string path full path to texture
	@treturn int x size of the image
	@treturn int y size of the image
	@treturn int id of the image
	@usage 
	local testImage={x=0,y=0,img=nil};
	testImage.x, testImage.y, testImage.img=M2TWEOP.loadTexture(M2TWEOP.getModPath().."/youneuoy_textures/test.dds");
	*/
	tables.M2TWEOPTable["loadTexture"] = &m2tweopHelpers::loadTextureToGame;
	/***
	Unload d3d texture
	@function M2TWEOP.unloadTexture
	@tparam int id of the image
	@usage 
	local testImage={x=0,y=0,img=nil};
	testImage.x, testImage.y, testImage.img=M2TWEOP.loadTexture(M2TWEOP.getModPath().."/youneuoy_textures/test.dds");
	M2TWEOP.unloadTexture(testImage.img);
	*/
	tables.M2TWEOPTable["unloadTexture"] = &m2tweopHelpers::unloadTextureFromGame;
	/***
	Set limit of ancillaries
	@function M2TWEOP.setAncillariesLimit
	@tparam int newLimit maximum - 127
	@usage
	M2TWEOP.setAncillariesLimit(15);
	*/
	tables.M2TWEOPTable["setAncillariesLimit"] = &m2tweopHelpers::setAncLimit;
	/***
	Unloc all console commands
	@function M2TWEOP.unlockGameConsoleCommands
	@usage
	M2TWEOP.unlockGameConsoleCommands();
	*/
	tables.M2TWEOPTable["unlockGameConsoleCommands"] = &plugData::data.funcs.unlockConsoleCommands.proc;
	/***
	Set new max bodyguard size
	@function M2TWEOP.setMaxBgSize
	@tparam int newSize maximum bodyguard size - 255
	@usage
	M2TWEOP.setMaxBgSize(222);
	*/
	tables.M2TWEOPTable["setMaxBgSize"] = &plugData::data.funcs.setMaxBgSize.proc;


	///Objects table section
	//@section objectsTable


	/***
	Basic stratmap.objects table

	@tfield addModelToGame addModelToGame
	@tfield setModel  setModel
	@tfield replaceTile  replaceTile

	@table stratmap.objects
	*/
	tables.objectsTable = luaState.create_table("objects");


	/***
	Add new cas stratmodel to game
	@function objects.addModelToGame
	@tparam string modelPath relative(to modfolder) path
	@tparam int modelId model id
	@usage
	stratmap.objects.addModelToGame("data/models_strat/residences/invisible.CAS",1);
	*/
	tables.objectsTable["addModelToGame"] = &objectsHelpers::addModelToGame;
	/***
	Set the model for the object at the specified coordinates. Works only for supported object types. 
	@function objects.setModel
	@tparam int xCoord
	@tparam int yCoord
	@tparam int modelId
	@tparam int modelId2
	@usage
	stratmap.objects.addModelToGame("data/models_strat/residences/invisible.CAS",1);
	stratmap.objects.setModel(288,257,1,1);
	*/
	tables.objectsTable["setModel"] = &objectsHelpers::setModel;
	/***
	Replace custom tile. Change custom battlefield for coordinates.
	@function objects.replaceTile
	@tparam string label
	@tparam int xCoord
	@tparam int yCoord
	@tparam string filename
	@tparam string weather
	@tparam string dayTime
	@usage
	stratmap.objects.replaceTile("Helms-Deep_Province",167,158,"hornburg_amb.wfc","clear","midday");
	*/
	tables.objectsTable["replaceTile"] = &objectsHelpers::replaceTile;

	///Camera table section
	//@section cameraTable


	/***
	Basic stratmap.camera table

	@tfield move move
	@tfield jump  jump
	@tfield zoom  zoom

	@table stratmap.camera
	*/
	tables.cameraTable = luaState.create_table("camera");
	/***
	Slow move camera to tile
	@function camera.move
	@tparam int xCoord
	@tparam int yCoord
	@usage
	stratmap.camera.move(1,2);
	*/
	tables.cameraTable["move"] = &cameraHelpers::moveStratCamera;
	/***
	Fast move camera to tile
	@function camera.jump
	@tparam int xCoord
	@tparam int yCoord
	@usage
	stratmap.camera.jump(1,2);
	*/
	tables.cameraTable["jump"] = &cameraHelpers::snapStratCamera;
	/***
	Set zoom of stratcamera
	@function camera.zoom
	@tparam float distance
	@usage
	stratmap.camera.zoom(0.12);
	*/
	tables.cameraTable["zoom"] = &cameraHelpers::zoomStratCamera;

	///Game table section
	//@section gameTable


	/***
	Basic stratmap.game table

	@tfield getFactionsCount getFactionsCount
	@tfield getFaction getFaction
	@tfield createCharacterByString createCharacterByString
	@tfield createArmy createArmy
	@tfield createUnitN createUnitN
	@tfield createUnitIdx createUnitIdx

	@table stratmap.game
*/
	tables.gameTable = luaState.create_table("game");
	/***
	Get factions number
	@function game.getFactionsCount
	@treturn int facNumber number of factions
	@usage
	local facNum=stratmap.game.getFactionsCount();
	*/
	tables.gameTable["getFactionsCount"] = &gameHelpers::getFactionsCount;
	/***
	Get faction with index
	@function game.getFaction
	@tparam int index
	@treturn factionStruct faction
	@usage
	faction=stratmap.game.getFaction(2);
	*/
	tables.gameTable["getFaction"] = &gameHelpers::getFaction;
	/***
	Create character at coords
	@function game.createCharacterByString
	@tparam string type
	@tparam factionStruct faction
	@tparam int age
	@tparam string name
	@tparam string name2
	@tparam int subFaction
	@tparam string portrait
	@tparam int xCoord
	@tparam int yCoord
	@treturn character newCharacter
	@usage
	newCharacter=stratmap.game.createCharacterByString("named character",stratmap.game.getFaction(0),18,"Name1","Name2",31,nil,character.character.xCoord+5,character.character.yCoord);
	*/
	tables.gameTable["createCharacterByString"] = &gameHelpers::createCharacter;
	/***
	Create army for character. 
	@function game.createArmy
	@tparam character ourGeneral
	@treturn stackStruct army
	@usage
	army=stratmap.game.createArmy(gen);
	*/
	tables.gameTable["createArmy"] = &gameHelpers::createArmy;
	/***
	create unit by name. 
	@function game.createUnitN
	@tparam string type
	@tparam int facNum
	@tparam int exp
	@tparam int armor
	@tparam int weapon
	@treturn unit newUnit
	@usage
	newUnit=stratmap.game.createUnitN("Axemen of Lossarnach",2,1,1,1);
	*/
	tables.gameTable["createUnitN"] = &gameHelpers::createUnitN;
	/***
	create unit by index in EDU.
	@function game.createUnitIdx
	@tparam int type
	@tparam int facNum
	@tparam int exp
	@tparam int armor
	@tparam int weapon
	@treturn unit newUnit
	@usage
	newUnit=stratmap.game.createUnitIdx(52,2,1,1,1);
*/
	tables.gameTable["createUnitIdx"] = &gameHelpers::createUnitIdx;

	///Stratmap table section
	//@section stratmapTable

	/***
	Basic stratmap table

	@tfield objects objects
	@tfield camera camera
	@tfield game game


	@table stratmap
	*/
	tables.stratmapTable = luaState.create_table("stratmap");
	tables.stratmapTable.set(&tables.objectsTable);
	tables.stratmapTable.set(&tables.cameraTable);
	tables.stratmapTable.set(&tables.gameTable);

	///Unit table section
	//@section unitTable

	/***
	Unit table

	@tfield eduEntry eduEntry
	@tfield float movePoints
	@tfield int number
	@tfield int numberTact
	@tfield int numberMax
	@tfield kill kill
	@tfield setParams setParams


	@table unit
	*/
	types.unit = luaState.new_usertype<unit>("unit");
	types.unit["eduEntry"] = &unit::eduEntry;
	types.unit["movePoints"] = sol::property(&unitHelpers::getMovepoints, &unitHelpers::setMovepoints);
	types.unit["number"] = sol::property(&unit::number, &unitHelpers::setSoldiersCount);
	types.unit["numberTact"] = &unit::numberTact;
	types.unit["numberMax"] = &unit::numberMax;
	/***
	Kill this unit
	@function unit:kill
	@usage
	newUnit=stratmap.game.createUnitN("Axemen of Lossarnach",2,1,1,1);
	newUnit:kill();
	*/
	types.unit["kill"] = &unitHelpers::killUnit;
	/***
	Set unit basic parameters
	@function unit:setParams
	@tparam int exp
	@tparam int armor
	@tparam int weapon
	@usage
	newUnit=stratmap.game.createUnitN("Axemen of Lossarnach",2,1,1,1);
	newUnit:setParams(0,0,0);
	*/
	types.unit["setParams"] = &unitHelpers::setUnitParams;

	types.character = luaState.new_usertype<general>("character");
	types.character["xCoord"] = &general::xCoord;
	types.character["yCoord"] = &general::yCoord;
	types.character["namedCharacter"] = &general::genChar;
	types.character["bodyguards"] = &general::bodyguards;
	types.character["movepointsMax"] = &general::movepointsMax;
	types.character["movepointsModifier"] = &general::movepointsModifier;
	types.character["movepoints"] = sol::property(&generalHelpers::getMovepoints, &generalHelpers::setMovepoints);
	types.character["ability"] = sol::property(&luaGetSetFuncs::getStringPropertyGen<generalStruct_abilityID>, &luaGetSetFuncs::setStringPropertyGen<generalStruct_abilityID>);
	types.character["moveToTile"] = &generalHelpers::moveToTile;
	types.character["reposition"] = &generalHelpers::reposition;
	types.character["siegeSettlement"] = &generalHelpers::siegeSettlement;
	types.character["kill"] = &generalHelpers::killGeneral;
	types.character["setBodyguardUnit"] = &generalHelpers::setBodyguard;

	types.namedCharacter= luaState.new_usertype<generalCharacterictics>("namedCharacter");
	types.namedCharacter["index"] = &generalCharacterictics::index;
	types.namedCharacter["character"] = &generalCharacterictics::gen;
	types.namedCharacter["shortName"] = sol::property(
		&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_shortName>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_shortName>);
	types.namedCharacter["fullName"] = sol::property(&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_fullName>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_fullName>);
	types.namedCharacter["label"] = sol::property(&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_label>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_label>);
	types.namedCharacter["modelName"] = sol::property(&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_modelName>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_modelName>);
	types.namedCharacter["status"] = &generalCharacterictics::status;
	types.namedCharacter["command"] = &generalCharacterictics::authority;
	types.namedCharacter["loyalty"] = &generalCharacterictics::loyality;
	types.namedCharacter["piety"] = &generalCharacterictics::piety;
	types.namedCharacter["chivalryAndDread"] = &generalCharacterictics::nobility;
	types.namedCharacter["authority"] = &generalCharacterictics::leaderAutority;
	types.namedCharacter["getAncillary"] = &generalCharactericticsHelpers::getAnchillary;
	types.namedCharacter["ancNum"] = &generalCharacterictics::anchNum;
	types.namedCharacter["yearOfBirth"] = &generalCharacterictics::yearOfBirth;
	types.namedCharacter["faction"] = &generalCharacterictics::faction;
	types.namedCharacter["subFaction"] = &generalCharacterictics::subFaction;
	types.namedCharacter["parent"] = &generalCharacterictics::parent;
	types.namedCharacter["spouse"] = &generalCharacterictics::spouse;
	types.namedCharacter["portrait"] = sol::property(
		&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_portrait>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_portrait>
	);
	types.namedCharacter["portrait"] = sol::property(
		&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_portrait2>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_portrait2>
	);
	types.namedCharacter["portrait_custom"] = sol::property(
		&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_portrait_custom>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_portrait_custom>
	);
	types.namedCharacter["addAncillary"] = &generalCharactericticsHelpers::addAnchillary;
	types.namedCharacter["removeAncillary"] = &generalCharactericticsHelpers::removeAnchillary;
	types.namedCharacter["age"] = sol::property(
		&generalCharactericticsHelpers::getAge,&generalCharactericticsHelpers::setAge
		);
	types.namedCharacter["isAlive"] = &generalCharactericticsHelpers::isAlive;

	types.ancillary= luaState.new_usertype<anchillary>("ancillary");
	types.ancillary["index"]= &anchillary::index;
	types.ancillary["name"] = sol::property(
		&luaGetSetFuncs::getStringPropertyAnc<anchillaryStruct_name>, &luaGetSetFuncs::setStringPropertyAnc<anchillaryStruct_name>
		);
	types.ancillary["imagePath"] = sol::property(
		&luaGetSetFuncs::getStringPropertyAnc<anchillaryStruct_imagePath>, &luaGetSetFuncs::setStringPropertyAnc<anchillaryStruct_imagePath>
		);


	types.EduEntry = luaState.new_usertype<EduEntry>("eduEntry");
	types.EduEntry["Type"] = sol::property(
		&luaGetSetFuncs::getStringPropertyEDU<EduEntryStruct_Type>, &luaGetSetFuncs::setStringPropertyEDU<EduEntryStruct_Type>
		);
	types.EduEntry["Dictionary"] = &EduEntry::Dictionary;
	types.EduEntry["Index"] = &EduEntry::Index;
	types.EduEntry["UnitCreatedCounter"] = &EduEntry::UnitCreatedCounter;

	types.factionStruct = luaState.new_usertype<factionStruct>("factionStruct");
	types.factionStruct["dipNum"] = &factionStruct::dipNum;
	types.factionStruct["ai_label"] = sol::property(
		&factionHelpers::getStringProperty<factionStruct_ai_label>, &factionHelpers::setStringProperty<factionStruct_ai_label>
		);
	types.factionStruct["capital"] = &factionStruct::capital;
	types.factionStruct["leader"] = &factionStruct::leader;
	types.factionStruct["heir"] = &factionStruct::heir;
	types.factionStruct["getFactionName"] = &factionHelpers::getFactionName;
	types.factionStruct["isPlayerControlled"] = &factionStruct::isPlayerControlled;
	types.factionStruct["getNamedCharacter"] = &factionHelpers::getCharacterFromFullList;
	types.factionStruct["numOfNamedCharacters"] = &factionStruct::numOfCharactersAll;
	types.factionStruct["getCharacter"] = &factionHelpers::getCharacterFromGeneralsList;
	types.factionStruct["numOfCharacters"] = &factionStruct::numOfCharacters;
	types.factionStruct["getStack"] = &factionHelpers::getStack;
	types.factionStruct["stackNum"] = &factionStruct::stackNum;
	types.factionStruct["getSettlement"] = &factionHelpers::getSettlement;
	types.factionStruct["settlementsNum"] = &factionStruct::settlementsNum;
	types.factionStruct["getFort"] = &factionHelpers::getFort;
	types.factionStruct["fortsNum"] = &factionStruct::fortsNum;
	types.factionStruct["getPort"] = &factionHelpers::getPort;
	types.factionStruct["portsNum"] = &factionStruct::portBuildingsNum;
	types.factionStruct["religion"] = &factionStruct::religion;
	types.factionStruct["money"] = &factionStruct::money;

	types.settlementStruct = luaState.new_usertype<settlementStruct>("settlementStruct");
	types.settlementStruct["governor"] = &settlementStruct::gubernator;
	types.settlementStruct["xCoord"] = &settlementStruct::xCoord;
	types.settlementStruct["yCoord"] = &settlementStruct::yCoord;
	types.settlementStruct["army"] = &settlementStruct::army;
	types.settlementStruct["name"] = sol::property(
		&settlementHelpers::getStringProperty<settlementStruct_name>, &settlementHelpers::setStringProperty<settlementStruct_name>
		);
	types.settlementStruct["ownerFaction"] = &settlementStruct::ownerFac;
	types.settlementStruct["level"] = &settlementStruct::level;
	types.settlementStruct["fac_creatorNum"] = &settlementStruct::fac_creatorModNum;
	types.settlementStruct["isCastle"] = &settlementStruct::isCastle;
	types.settlementStruct["regionNumber"] = &settlementStruct::regionNumber;
	types.settlementStruct["isProvokedRebellion"] = &settlementStruct::isProvokedRebellion;
	types.settlementStruct["getBuilding"] = &settlementHelpers::getBuilding;
	types.settlementStruct["buldingsNum"] = &settlementStruct::buldingsNum;	
	types.settlementStruct["getResource"] = &settlementHelpers::getResource;
	types.settlementStruct["resourcesNum"] = &settlementStruct::resourcesNum;

	types.resStrat= luaState.new_usertype<resStrat>("resStrat");
	types.resStrat["xCoord"] = &resStrat::xCoord;
	types.resStrat["yCoord"] = &resStrat::yCoord;
	types.resStrat["setStratModel"] = &resourcesHelpers::setModel;
	types.resStrat["getResourceCode"] = &resourcesHelpers::getResourceCode;

	types.stackStruct= luaState.new_usertype<stackStruct>("stackStruct");
	types.stackStruct["faction"] = &stackStruct::faction;
	types.stackStruct["getUnit"] = &stackStructHelpers::getUnit;
	types.stackStruct["numOfUnits"] = &stackStruct::numOfUnits;
	types.stackStruct["getCharacter"] = &stackStructHelpers::getCharacter;
	types.stackStruct["numOfCharacters"] = &stackStruct::charactersNum;
	types.stackStruct["boardedArmy"] = &stackStruct::boardedArmy;
	types.stackStruct["blockedPort"] = &stackStruct::blockedPort;
	types.stackStruct["leader"] = &stackStruct::gen;
	types.stackStruct["findInSettlement"] = &stackStructHelpers::findInSettlement;
	types.stackStruct["findInFort"] = &stackStructHelpers::findInFort;
	types.stackStruct["totalStrength"] = &stackStruct::totalStrength;
	types.stackStruct["reform_point_x"] = &stackStruct::reform_point_x;
	types.stackStruct["reform_point_y"] = &stackStruct::reform_point_y;
	types.stackStruct["addUnit"] = &stackStructHelpers::addUnitToArmy;
	types.stackStruct["attackArmy"] = &stackStructHelpers::attackArmy;

	types.building= luaState.new_usertype<building>("building");
	types.building["buildingData"] = &building::bData;
	types.building["level"] = &building::level;
	types.building["hp"] = &building::hp;
	types.building["settlement"] = &building::settlement;

	types.building_data = luaState.new_usertype<building_data>("building_data");
	types.building_data["type"] = sol::property(
		&buildingStructHelpers::getStringPropertyBD<building_dataStruct_type>, &buildingStructHelpers::setStringPropertyBD<building_dataStruct_type>
		);
	types.building_data["buildingInfo"] = &building_data::drawInfo;

	types.buildingDrawInfo= luaState.new_usertype<buildingDrawInfo>("buildingDrawInfo");
	types.buildingDrawInfo["name"] = sol::property(
		&buildingStructHelpers::getStringPropertyBDI<buildingDrawInfoStruct_name>, &buildingStructHelpers::setStringPropertyBDI<buildingDrawInfoStruct_name>
		);




	onPluginLoadF();
	return &luaState;
}




void checkLuaFunc(sol::function** lRef)
{
	if ((*lRef)->valid() == false)
	{
		*lRef = nullptr;
	}
}
void luaP::onPluginLoadF()
{
	drawLuaFunc = new sol::function(luaState["draw"]);
	checkLuaFunc(&drawLuaFunc);

	resetDXFunc = new sol::function(luaState["deinitDX"]);
	checkLuaFunc(&resetDXFunc);

	initDXFunc = new sol::function(luaState["initDX"]);
	checkLuaFunc(&initDXFunc);

	onPluginLoad = new sol::function(luaState["onPluginLoad"]);
	checkLuaFunc(&onPluginLoad);

	onChangeTurnNumFunc = new sol::function(luaState["onChangeTurnNum"]);
	checkLuaFunc(&onChangeTurnNumFunc);

	onCharacterSelectedFunc = new sol::function(luaState["onCharacterSelected"]);
	checkLuaFunc(&onCharacterSelectedFunc);

	onPreFactionTurnStartFunc = new sol::function(luaState["onPreFactionTurnStart"]);
	checkLuaFunc(&onPreFactionTurnStartFunc);

	onFactionTurnStartFunc = new sol::function(luaState["onFactionTurnStart"]);
	checkLuaFunc(&onFactionTurnStartFunc);

	onFactionTurnEndFunc = new sol::function(luaState["onFactionTurnEnd"]);
	checkLuaFunc(&onFactionTurnEndFunc);

	onFactionNewCapitalFunc = new sol::function(luaState["onFactionNewCapital"]);
	checkLuaFunc(&onFactionNewCapitalFunc);

	onFactionWarDeclaredFunc = new sol::function(luaState["onFactionWarDeclared"]);
	checkLuaFunc(&onFactionWarDeclaredFunc);

	onFactionAllianceDeclaredFunc = new sol::function(luaState["onFactionAllianceDeclared"]);
	checkLuaFunc(&onFactionAllianceDeclaredFunc);

	onFactionTradeAgreementMadeFunc = new sol::function(luaState["onFactionTradeAgreementMade"]);
	checkLuaFunc(&onFactionTradeAgreementMadeFunc);

	onFactionBreakAllianceFunc = new sol::function(luaState["onFactionBreakAlliance"]);
	checkLuaFunc(&onFactionBreakAllianceFunc);

	onGiveMoneyFunc = new sol::function(luaState["onGiveMoney"]);
	checkLuaFunc(&onGiveMoneyFunc);

	onUpdateAttitudeFunc = new sol::function(luaState["onUpdateAttitude"]);
	checkLuaFunc(&onUpdateAttitudeFunc);

	onDemeanourFunc = new sol::function(luaState["onDemeanour"]);
	checkLuaFunc(&onDemeanourFunc);


	onGeneralAssaultsGeneralFunc = new sol::function(luaState["onGeneralAssaultsGeneral"]);
	checkLuaFunc(&onGeneralAssaultsGeneralFunc);

	onGeneralAssaultsResidenceFunc = new sol::function(luaState["onGeneralAssaultsResidence"]);
	checkLuaFunc(&onGeneralAssaultsResidenceFunc);


	onGeneralCaptureSettlementFunc = new sol::function(luaState["onGeneralCaptureSettlement"]);
	checkLuaFunc(&onGeneralCaptureSettlementFunc);


	onGeneralCaptureResidenceFunc = new sol::function(luaState["onGeneralCaptureResidence"]);
	checkLuaFunc(&onGeneralCaptureResidenceFunc);

	onSiegeEquipmentCompletedFunc = new sol::function(luaState["onSiegeEquipmentCompleted"]);
	checkLuaFunc(&onSiegeEquipmentCompletedFunc);


	onPostBattleFunc = new sol::function(luaState["onPostBattle"]);
	checkLuaFunc(&onPostBattleFunc);


	onMultiTurnMoveFunc = new sol::function(luaState["onMultiTurnMove"]);
	checkLuaFunc(&onMultiTurnMoveFunc);

	onSettlementSelectedFunc = new sol::function(luaState["onSettlementSelected"]);
	checkLuaFunc(&onSettlementSelectedFunc);


	onSettlementUpgradedFunc = new sol::function(luaState["onSettlementUpgraded"]);
	checkLuaFunc(&onSettlementUpgradedFunc);

	onSettlementConvertedFunc = new sol::function(luaState["onSettlementConverted"]);
	checkLuaFunc(&onSettlementConvertedFunc);


	onCityRiotsFunc = new sol::function(luaState["onCityRiots"]);
	checkLuaFunc(&onCityRiotsFunc);

	onUngarrisonedSettlementFunc = new sol::function(luaState["onUngarrisonedSettlement"]);
	checkLuaFunc(&onUngarrisonedSettlementFunc);


	onUngarrisonedFortFunc = new sol::function(luaState["onUngarrisonedFort"]);
	checkLuaFunc(&onUngarrisonedFortFunc);

	onGiveSettlementFunc = new sol::function(luaState["onGiveSettlement"]);
	checkLuaFunc(&onGiveSettlementFunc);

	onOccupySettlementFunc = new sol::function(luaState["onOccupySettlement"]);
	checkLuaFunc(&onOccupySettlementFunc);

	onExterminatePopulationFunc = new sol::function(luaState["onExterminatePopulation"]);
	checkLuaFunc(&onExterminatePopulationFunc);

	onSackSettlementFunc = new sol::function(luaState["onSackSettlement"]);
	checkLuaFunc(&onSackSettlementFunc);

	onAddedToBuildingQueueFunc = new sol::function(luaState["onAddedToBuildingQueue"]);
	checkLuaFunc(&onAddedToBuildingQueueFunc);

	onBuildingDestroyedFunc = new sol::function(luaState["onBuildingDestroyed"]);
	checkLuaFunc(&onBuildingDestroyedFunc);

	onBuildingCompletedFunc = new sol::function(luaState["onBuildingCompleted"]);
	checkLuaFunc(&onBuildingCompletedFunc);


	onEventCounterFunc = new sol::function(luaState["onEventCounter"]);
	checkLuaFunc(&onEventCounterFunc);

	onFactionExcommunicatedFunc = new sol::function(luaState["onFactionExcommunicated"]);
	checkLuaFunc(&onFactionExcommunicatedFunc);

	onDisasterFunc = new sol::function(luaState["onDisaster"]);
	checkLuaFunc(&onDisasterFunc);

	onHordeFormedFunc = new sol::function(luaState["onHordeFormed"]);
	checkLuaFunc(&onHordeFormedFunc);

	onAddedToTrainingQueueFunc = new sol::function(luaState["onAddedToTrainingQueue"]);
	checkLuaFunc(&onAddedToTrainingQueueFunc);

	onUnitDisbandedFunc = new sol::function(luaState["onUnitDisbanded"]);
	checkLuaFunc(&onUnitDisbandedFunc);

	onUnitTrainedFunc = new sol::function(luaState["onUnitTrained"]);
	checkLuaFunc(&onUnitTrainedFunc);

	onAgentCreatedFunc = new sol::function(luaState["onAgentCreated"]);
	checkLuaFunc(&onAgentCreatedFunc);


	onObjSeenFunc = new sol::function(luaState["onObjSeen"]);
	checkLuaFunc(&onObjSeenFunc);

	onTileSeenFunc = new sol::function(luaState["onTileSeen"]);
	checkLuaFunc(&onTileSeenFunc);

	onGameReloadedFunc = new sol::function(luaState["onGameReloaded"]);
	checkLuaFunc(&onGameReloadedFunc);

	onTransgressionFunc = new sol::function(luaState["onTransgression"]);
	checkLuaFunc(&onTransgressionFunc);




	onPopeAcceptsCrusadeTargetFunc = new sol::function(luaState["onPopeAcceptsCrusadeTarget"]);
	checkLuaFunc(&onPopeAcceptsCrusadeTargetFunc);

	onCrusadeCalledFunc = new sol::function(luaState["onCrusadeCalled"]);
	checkLuaFunc(&onCrusadeCalledFunc);

	onCrusadeEndsFunc = new sol::function(luaState["onCrusadeEnds"]);
	checkLuaFunc(&onCrusadeEndsFunc);

	onPopeRejectsCrusadeTargetFunc = new sol::function(luaState["onPopeRejectsCrusadeTarget"]);
	checkLuaFunc(&onPopeRejectsCrusadeTargetFunc);

	onArmyTakesCrusadeTargetFunc = new sol::function(luaState["onArmyTakesCrusadeTarget"]);
	checkLuaFunc(&onArmyTakesCrusadeTargetFunc);

	onUnitsDesertCrusadeFunc = new sol::function(luaState["onUnitsDesertCrusade"]);
	checkLuaFunc(&onUnitsDesertCrusadeFunc);

	onPopeElectedFunc = new sol::function(luaState["onPopeElected"]);
	checkLuaFunc(&onPopeElectedFunc);

	onVotedForPopeFunc = new sol::function(luaState["onVotedForPope"]);
	checkLuaFunc(&onVotedForPopeFunc);

	onAssassinCaughtAttackingPopeFunc = new sol::function(luaState["onAssassinCaughtAttackingPope"]);
	checkLuaFunc(&onAssassinCaughtAttackingPopeFunc);

	onInquisitorAppointedFunc = new sol::function(luaState["onInquisitorAppointed"]);
	checkLuaFunc(&onInquisitorAppointedFunc);



	onSettlementPanelOpenFunc = new sol::function(luaState["onSettlementPanelOpen"]);
	checkLuaFunc(&onSettlementPanelOpenFunc);

	onFinancesPanelOpenFunc = new sol::function(luaState["onFinancesPanelOpen"]);
	checkLuaFunc(&onFinancesPanelOpenFunc);

	onFactionSummaryPanelOpenFunc = new sol::function(luaState["onFactionSummaryPanelOpen"]);
	checkLuaFunc(&onFactionSummaryPanelOpenFunc);

	onFamilyTreePanelOpenFunc = new sol::function(luaState["onFamilyTreePanelOpenFunc"]);
	checkLuaFunc(&onFamilyTreePanelOpenFunc);

	onDiplomaticStandingPanelOpenFunc = new sol::function(luaState["onDiplomaticStandingPanelOpen"]);
	checkLuaFunc(&onDiplomaticStandingPanelOpenFunc);

	onDiplomacyPanelOpenFunc = new sol::function(luaState["onDiplomacyPanelOpen"]);
	checkLuaFunc(&onDiplomacyPanelOpenFunc);

	onPreBattlePanelOpenFunc = new sol::function(luaState["onPreBattlePanelOpen"]);
	checkLuaFunc(&onPreBattlePanelOpenFunc);

	onNavalAutoResolvePanelOpenFunc = new sol::function(luaState["onNavalAutoResolvePanelOpen"]);
	checkLuaFunc(&onNavalAutoResolvePanelOpenFunc);

	onCharacterPanelOpenFunc = new sol::function(luaState["onCharacterPanelOpen"]);
	checkLuaFunc(&onCharacterPanelOpenFunc);

	onTradePanelOpenFunc = new sol::function(luaState["onTradePanelOpen"]);
	checkLuaFunc(&onTradePanelOpenFunc);

	onRequestBuildingAdviceFunc = new sol::function(luaState["onRequestBuildingAdvice"]);
	checkLuaFunc(&onRequestBuildingAdviceFunc);

	onRequestTrainingAdviceFunc = new sol::function(luaState["onRequestTrainingAdvice"]);
	checkLuaFunc(&onRequestTrainingAdviceFunc);

	onMessageOpenFunc = new sol::function(luaState["onMessageOpen"]);
	checkLuaFunc(&onMessageOpenFunc);

	onIncomingMessageFunc = new sol::function(luaState["onIncomingMessage"]);
	checkLuaFunc(&onIncomingMessageFunc);

	onMessageClosedFunc = new sol::function(luaState["onMessageClosed"]);
	checkLuaFunc(&onMessageClosedFunc);

	onButtonPressedFunc = new sol::function(luaState["onButtonPressed"]);
	checkLuaFunc(&onButtonPressedFunc);

	onScrollClosedFunc = new sol::function(luaState["onScrollClosed"]);
	checkLuaFunc(&onScrollClosedFunc);

	onScrollOpenedFunc = new sol::function(luaState["onScrollOpened"]);
	checkLuaFunc(&onScrollOpenedFunc);

	onUIElementVisibleFunc = new sol::function(luaState["onUIElementVisible"]);
	checkLuaFunc(&onUIElementVisibleFunc);

	onScrollAdviceRequestedFunc = new sol::function(luaState["onScrollAdviceRequested"]);
	checkLuaFunc(&onScrollAdviceRequestedFunc);

	onSettlementScrollAdviceRequestedFunc = new sol::function(luaState["onSettlementScrollAdviceRequested"]);
	checkLuaFunc(&onSettlementScrollAdviceRequestedFunc);

	onPreBattleScrollAdviceRequestedFunc = new sol::function(luaState["onPreBattleScrollAdviceRequested"]);
	checkLuaFunc(&onPreBattleScrollAdviceRequestedFunc);

	onNavalPreBattleScrollAdviceRequestedFunc = new sol::function(luaState["onNavalPreBattleScrollAdviceRequested"]);
	checkLuaFunc(&onNavalPreBattleScrollAdviceRequestedFunc);

	onCollegeOfCardinalsPanelOpenFunc = new sol::function(luaState["onCollegeOfCardinalsPanelOpen"]);
	checkLuaFunc(&onCollegeOfCardinalsPanelOpenFunc);





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
		tryLua((*onDemeanourFunc)(fac, fac2, amount));
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
		tryLua((*onSiegeEquipmentCompletedFunc)(sett, frt));
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

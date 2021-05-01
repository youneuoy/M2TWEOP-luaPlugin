///
//![Lua logo](_static/Lua.png)
//M2TWEOP structures and functions. There are not many examples and descriptions here. Also note that the examples do not include many of the checks that would be required when creating modifications.
//@module LUA-PLUGIN
//@author youneuoy
//@license GPL-3.0
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
		luaP::logS += luaError.what();
		luaP::logS += '\n';
	}
	return;
}

bool luaP::checkVar(const char* gName, int variable)
{
	sol::optional<int> scriptVar = luaState[gName];
	if (scriptVar)
	{
		return scriptVar.value() == variable;
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



	sol::load_result fileRes = luaState.load_file(luaFilePath);
	if (!fileRes.valid()) { // This checks the syntax of your script, but does not execute it
		sol::error luaError = fileRes;
		MessageBoxA(NULL, luaError.what(), "Lua exception!", NULL);
		return nullptr;
	}
	sol::protected_function_result result1 = fileRes(); // this causes the script to execute
	if (!result1.valid()) {
		sol::error luaError = result1;
		MessageBoxA(NULL, luaError.what(), "Lua exception!", NULL);
		return nullptr;
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
	tables.M2TWEOPTable["unlockGameConsoleCommands"] = &m2tweopHelpers::unlockGameConsoleCommands;
	/***
	Set new max bodyguard size
	@function M2TWEOP.setMaxBgSize
	@tparam int newSize maximum bodyguard size - 255
	@usage
	M2TWEOP.setMaxBgSize(222);
	*/
	tables.M2TWEOPTable["setMaxBgSize"] = &m2tweopHelpers::setMaxBgSize;


	///Objects table section
	//@section objectsTable


	/***
	Basic stratmap.objects table

	@tfield addModelToGame addModelToGame
	@tfield setModel  setModel
	@tfield replaceTile  replaceTile

	@table stratmap.objects
	*/
	tables.objectsTable = luaState.create_table();


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
	tables.cameraTable = luaState.create_table();
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
	tables.gameTable = luaState.create_table();
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

	/*tables.stratmapTable["objects"] = &tables.objectsTable;
	tables.stratmapTable["camera"] = &tables.cameraTable;
	tables.stratmapTable["game"] = &tables.gameTable;*/
	tables.stratmapTable.set("objects", tables.objectsTable);
	tables.stratmapTable.set("camera", tables.cameraTable);
	tables.stratmapTable.set("game", tables.gameTable);

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


	///Character table section
	//@section characterTable

	/***
	Basic character table
	This had all characters(princess, diplomat, etc), if character in stratmap (not died,not to young, etc) has this fields.


	@tfield int xCoord
	@tfield int yCoord
	@tfield namedCharacter namedCharacter
	@tfield unit bodyguards
	@tfield float movepointsMax
	@tfield float movepointsModifier
	@tfield float movepoints
	@tfield string ability
	@tfield moveToTile moveToTile
	@tfield reposition reposition
	@tfield siegeSettlement siegeSettlement
	@tfield kill kill
	@tfield setBodyguardUnit setBodyguardUnit

	@table character
	*/
	types.character = luaState.new_usertype<general>("character");
	types.character["xCoord"] = &general::xCoord;
	types.character["yCoord"] = &general::yCoord;
	types.character["namedCharacter"] = &general::genChar;
	types.character["bodyguards"] = &general::bodyguards;
	types.character["movepointsMax"] = &general::movepointsMax;
	types.character["movepointsModifier"] = &general::movepointsModifier;
	types.character["movepoints"] = sol::property(&generalHelpers::getMovepoints, &generalHelpers::setMovepoints);
	types.character["ability"] = sol::property(&luaGetSetFuncs::getStringPropertyGen<generalStruct_abilityID>, &luaGetSetFuncs::setStringPropertyGen<generalStruct_abilityID>);
	/***
	Start moving to tale. Need movepoints.
	@function character:moveToTile
	@tparam int xCoord
	@tparam int yCoord
	@usage
	ourCharacter:moveToTile(11,25);
	*/
	types.character["moveToTile"] = &generalHelpers::moveToTile;
	/***
	Character reposition. Just teleports him.
	@function character:reposition
	@tparam int xCoord
	@tparam int yCoord
	@usage
	ourCharacter:moveToTile(11,25);
	*/
	types.character["reposition"] = &generalHelpers::reposition;
	/***
	Siege settlement, or attack it if in siege
	@function character:siegeSettlement
	@tparam settlementStruct settlement
	@usage
	ourCharacter:siegeSettlement(settlement);
	*/
	types.character["siegeSettlement"] = &generalHelpers::siegeSettlement;
	/***
	Delete this character
	@function character:kill
	@usage
	ourCharacter:kill();
	*/
	types.character["kill"] = &generalHelpers::killGeneral;
	/***
	Set bodyguard. Do this only for characters without it (after creating,for example)
	@function character:setBodyguardUnit
	@tparam unit unit
	@usage
	newUnit=stratmap.game.createUnitN("Axemen of Lossarnach",2,1,1,1);
	ourCharacter:setBodyguardUnit(newUnit);
	*/
	types.character["setBodyguardUnit"] = &generalHelpers::setBodyguard;


	///NamedCharacter table section
	//@section namedCharacterTable

	/***
	Basic namedCharacter table

	@tfield int index
	@tfield character character
	@tfield string shortName
	@tfield string fullName
	@tfield string label
	@tfield string modelName
	@tfield int status 5-leader,2 - heir, 0 - ordinary character. Only read it, not set it!
	@tfield int command
	@tfield int loyalty
	@tfield int piety
	@tfield int chivalryAndDread Dread if negative value
	@tfield int authority
	@tfield getAncillary getAncillary
	@tfield int ancNum
	@tfield float yearOfBirth
	@tfield factionStruct faction
	@tfield int subFaction
	@tfield namedCharacter parent
	@tfield namedCharacter spouse
	@tfield string portrait
	@tfield string portrait2
	@tfield string portrait_custom
	@tfield addAncillary addAncillary
	@tfield removeAncillary removeAncillary
	@tfield int age
	@tfield isAlive isAlive

	@table namedCharacter
	*/
	types.namedCharacter = luaState.new_usertype<generalCharacterictics>("namedCharacter");
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
	/***
	Get pointer to ancillary with number
	@function namedCharacter:getAncillary
	@tparam int index
	@tparam int yCoord
	@treturn ancillary ancillary
	@usage
	ancillary=ourNamedCharacter:getAncillary(2);
	*/
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
	types.namedCharacter["portrait2"] = sol::property(
		&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_portrait2>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_portrait2>
		);
	types.namedCharacter["portrait_custom"] = sol::property(
		&luaGetSetFuncs::getStringPropertyGenChar<generalCharactericticsStruct_portrait_custom>, &luaGetSetFuncs::setStringPropertyGenChar<generalCharactericticsStruct_portrait_custom>
		);
	/***
	Add new ancillary
	@function namedCharacter:addAncillary
	@tparam string ancillaryName
	@usage
	ourNamedCharacter:addAncillary("VeryVeryGoodMan");
	*/
	types.namedCharacter["addAncillary"] = &generalCharactericticsHelpers::addAnchillary;
	/***
	Remove ancillary
	@function namedCharacter:removeAncillary
	@tparam ancillary ancillary
	@usage
	ourAnc=ourNamedCharacter:getAncillary(2);
	ourNamedCharacter:removeAncillary(ourAnc);
	*/
	types.namedCharacter["removeAncillary"] = &generalCharactericticsHelpers::removeAnchillary;
	types.namedCharacter["age"] = sol::property(
		&generalCharactericticsHelpers::getAge, &generalCharactericticsHelpers::setAge
		);
	/***
	Check if the character is alive
	@function namedCharacter:isAlive
	@treturn int liveStatus 1 - live, 0 - dead
	@usage
	if(ourcharacter:isAlive()==1)
	then
		ourcharacter:kill();
	end
	*/
	types.namedCharacter["isAlive"] = &generalCharactericticsHelpers::isAlive;


	///Ancillary table section
	//@section ancillaryTable

	/***
	Basic ancillary table

	@tfield int index
	@tfield string name
	@tfield string imagePath

	@table ancillary
	*/
	types.ancillary = luaState.new_usertype<anchillary>("ancillary");
	types.ancillary["index"] = &anchillary::index;
	types.ancillary["name"] = sol::property(
		&luaGetSetFuncs::getStringPropertyAnc<anchillaryStruct_name>, &luaGetSetFuncs::setStringPropertyAnc<anchillaryStruct_name>
		);
	types.ancillary["imagePath"] = sol::property(
		&luaGetSetFuncs::getStringPropertyAnc<anchillaryStruct_imagePath>, &luaGetSetFuncs::setStringPropertyAnc<anchillaryStruct_imagePath>
		);

	///EduEntry table section
	//@section eduEntryTable

	/***
	Basic eduEntry table

	@tfield string Type
	@tfield int Dictionary
	@tfield int Index
	@tfield int UnitCreatedCounter

	@table eduEntry
	*/
	types.EduEntry = luaState.new_usertype<EduEntry>("eduEntry");
	types.EduEntry["Type"] = sol::property(
		&luaGetSetFuncs::getStringPropertyEDU<EduEntryStruct_Type>, &luaGetSetFuncs::setStringPropertyEDU<EduEntryStruct_Type>
		);
	types.EduEntry["Dictionary"] = &EduEntry::Dictionary;
	types.EduEntry["Index"] = &EduEntry::Index;
	types.EduEntry["UnitCreatedCounter"] = &EduEntry::UnitCreatedCounter;


	///FactionStruct table section
	//@section factionStructTable

	/***
	Basic factionStruct table

	@tfield int dipNum
	@tfield string ai_label
	@tfield settlementStruct capital
	@tfield namedCharacter leader
	@tfield namedCharacter heir
	@tfield getFactionName getFactionName
	@tfield int isPlayerControlled
	@tfield getNamedCharacter getNamedCharacter
	@tfield int numOfNamedCharacters
	@tfield getCharacter getCharacter
	@tfield int numOfCharacters
	@tfield getStack getStack
	@tfield int stacksNum
	@tfield getSettlement getSettlement
	@tfield int settlementsNum
	@tfield getFort getFort
	@tfield int fortsNum
	@tfield getFort getPort
	@tfield int portsNum
	@tfield int religion
	@tfield int money

	@table factionStruct
	*/
	types.factionStruct = luaState.new_usertype<factionStruct>("factionStruct");
	types.factionStruct["dipNum"] = &factionStruct::dipNum;
	types.factionStruct["ai_label"] = sol::property(
		&factionHelpers::getStringProperty<factionStruct_ai_label>, &factionHelpers::setStringProperty<factionStruct_ai_label>
		);
	types.factionStruct["capital"] = &factionStruct::capital;
	types.factionStruct["leader"] = &factionStruct::leader;
	types.factionStruct["heir"] = &factionStruct::heir;
	/***
	Get faction technical name
	@function factionStruct:getFactionName
	@treturn string facName
	@usage
	ourFac = stratmap.game.getFaction(0);
	ourFacName = ourFac:getFactionName();
	if(ourFacName == "hre")
	then
		ourFac.money = ourFac.money + (ourFac.fortsNum * 500);
	end
	*/
	types.factionStruct["getFactionName"] = &factionHelpers::getFactionName;
	types.factionStruct["isPlayerControlled"] = &factionStruct::isPlayerControlled;
	/***
	Get named character with number
	@function factionStruct:getNamedCharacter
	@tparam int number
	@treturn namedCharacter retNamedCharacter
	@usage
	ourFac = stratmap.game.getFaction(0);
	ourNamedCharacter = ourFac:getNamedCharacter(0);
	if(ourNamedCharacter.command > 5)
	then
		ourFac.money = ourFac.money - (ourNamedCharacter.command * 10);
	end
	*/
	types.factionStruct["getNamedCharacter"] = &factionHelpers::getCharacterFromFullList;
	types.factionStruct["numOfNamedCharacters"] = &factionStruct::numOfCharactersAll;
	/***
	Get  character with number
	@function factionStruct:getCharacter
	@tparam int number
	@treturn character retCharacter
	@usage
	ourFac = stratmap.game.getFaction(0);
	ourCharacter = ourFac:getCharacter(0);
	if(ourCharacter.xCoord > 150 and ourCharacter.movepoints<10)
	then
		ourCharacter:kill();
	end
	*/
	types.factionStruct["getCharacter"] = &factionHelpers::getCharacterFromGeneralsList;
	types.factionStruct["numOfCharacters"] = &factionStruct::numOfCharacters;
	/***
	Get army with number
	@function factionStruct:getStack
	@tparam int number
	@treturn stackStruct army
	@usage
	ourFac = stratmap.game.getFaction(0);
	ourArmy = ourFac:getCharacter(0);
	if(ourArmy.totalStrength > 1500)
	then
		ourFac.money = ourFac.money - (ourArmy.totalStrength);
	end
	*/
	types.factionStruct["getStack"] = &factionHelpers::getStack;
	types.factionStruct["stacksNum"] = &factionStruct::stackNum;
	/***
	Get settlement with number
	@function factionStruct:getSettlement
	@tparam int number
	@treturn settlementStruct settlement
	@usage
	ourFac = stratmap.game.getFaction(0);
	ourSett = ourFac:getSettlement(0);
	if(ourSett.isProvokedRebellion ~= 0)
	then
		ourFac.money = ourFac.money - (ourSett.level*5000);
	end
	*/
	types.factionStruct["getSettlement"] = &factionHelpers::getSettlement;
	types.factionStruct["settlementsNum"] = &factionStruct::settlementsNum;
	/***
	Get fort with number
	@function factionStruct:getFort
	@tparam int number
	@treturn fortStruct fort
	@usage
	later
	*/
	types.factionStruct["getFort"] = &factionHelpers::getFort;
	types.factionStruct["fortsNum"] = &factionStruct::fortsNum;
	/***
	Get fort with number
	@function factionStruct:getPort
	@tparam int number
	@treturn portStruct port
	@usage
	later
	*/
	types.factionStruct["getPort"] = &factionHelpers::getPort;
	types.factionStruct["portsNum"] = &factionStruct::portBuildingsNum;
	types.factionStruct["religion"] = &factionStruct::religion;
	types.factionStruct["money"] = &factionStruct::money;

	///SettlementStruct table section
	//@section settlementStructTable

	/***
	Basic settlementStruct table

	@tfield character governor
	@tfield int xCoord
	@tfield int yCoord
	@tfield stackStruct army
	@tfield string name
	@tfield factionStruct ownerFaction
	@tfield int level
	@tfield int fac_creatorNum
	@tfield int isCastle
	@tfield int regionNumber
	@tfield int isProvokedRebellion
	@tfield getBuilding getBuilding
	@tfield int buldingsNum
	@tfield getResource getResource
	@tfield int resourcesNum

	@table settlementStruct
	*/
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
	/***
	Get building with number
	@function settlementStruct:getBuilding
	@tparam int number
	@treturn building build
	@usage
	ourBuilding=settlementStruct:getBuilding(0);
	if(ourBuilding.level>1)
	then
		print("test");
	end
	*/
	types.settlementStruct["getBuilding"] = &settlementHelpers::getBuilding;
	types.settlementStruct["buldingsNum"] = &settlementStruct::buldingsNum;
	/***
	Get resource with number
	@function settlementStruct:getResource
	@tparam int number
	@treturn resStrat resource
	@usage
	ourResStrat=settlementStruct:getResource(0);
	*/
	types.settlementStruct["getResource"] = &settlementHelpers::getResource;
	types.settlementStruct["resourcesNum"] = &settlementStruct::resourcesNum;


	///ResStrat table section
	//@section resStratTable

	/***
	Basic resStrat table

	@tfield int xCoord
	@tfield int yCoord
	@tfield setStratModel setStratModel
	@tfield getResourceCode getResourceCode

	@table resStrat
	*/
	types.resStrat = luaState.new_usertype<resStrat>("resStrat");
	types.resStrat["xCoord"] = &resStrat::xCoord;
	types.resStrat["yCoord"] = &resStrat::yCoord;
	/***
	Set resource strat. model
	@function resStrat:setStratModel
	@tparam int modelId
	@usage
	resStrat:setStratModel(5);
	*/
	types.resStrat["setStratModel"] = &resourcesHelpers::setModel;
	types.resStrat["getResourceCode"] = &resourcesHelpers::getResourceCode;

	///StackStruct table section
	//@section stackStructTable

	/***
	Basic stackStruct table

	@tfield factionStruct faction
	@tfield getUnit getUnit
	@tfield int numOfUnits
	@tfield getCharacter getCharacter
	@tfield int numOfCharacters
	@tfield stackStruct boardedArmy
	@tfield portStruct blockedPort
	@tfield character leader
	@tfield findInSettlement findInSettlement
	@tfield findInFort findInFort
	@tfield int totalStrength
	@tfield float reform_point_x reform point x coordinate in battle
	@tfield float reform_point_y reform point y coordinate in battle
	@tfield addUnit addUnit
	@tfield attackArmy attackArmy


	@table stackStruct
	*/
	types.stackStruct = luaState.new_usertype<stackStruct>("stackStruct");
	types.stackStruct["faction"] = &stackStruct::faction;
	/***
	Get unit with number
	@function stackStruct:getUnit
	@tparam int number
	@treturn unit retUnit
	@usage
	ourUnit=stackStruct:getUnit(0);
	ourUnit:kill();
	*/
	types.stackStruct["getUnit"] = &stackStructHelpers::getUnit;
	types.stackStruct["numOfUnits"] = &stackStruct::numOfUnits;
	/***
	Get character(agent) with number
	@function stackStruct:getCharacter
	@tparam int number
	@treturn character retCharacter
	@usage
	ourChar=stackStruct:getCharacter(0);
	ourChar:kill();
	*/
	types.stackStruct["getCharacter"] = &stackStructHelpers::getCharacter;
	types.stackStruct["numOfCharacters"] = &stackStruct::charactersNum;
	types.stackStruct["boardedArmy"] = &stackStruct::boardedArmy;
	types.stackStruct["blockedPort"] = &stackStruct::blockedPort;
	types.stackStruct["leader"] = &stackStruct::gen;
	/***
	Find the settlement in which the army is located

	Returns nil if the army is not in the settlement.

	@function stackStruct:findInSettlement
	@treturn  settlementStruct  settlement
	@usage
	ourSett=stackStruct:findInSettlement();
	if(ourSett~=nil)
	then
		--something
	end
	*/
	types.stackStruct["findInSettlement"] = &stackStructHelpers::findInSettlement;
	/***
	Find the fort in which the army is located

	Returns nil if the army is not in the fort.

	@function stackStruct:findInFort
	@treturn  fortStruct  fort
	@usage
	ourFort=stackStruct:findInFort();
	if(ourFort~=nil)
	then
		--something
	end
	*/
	types.stackStruct["findInFort"] = &stackStructHelpers::findInFort;
	types.stackStruct["totalStrength"] = &stackStruct::totalStrength;
	types.stackStruct["reform_point_x"] = &stackStruct::reform_point_x;
	types.stackStruct["reform_point_y"] = &stackStruct::reform_point_y;
	/***
	Add unit to this army.

	@function stackStruct:addUnit
	@tparam unit unit
	@treturn  int  ifSucess
	@usage
	newUnit=stratmap.game.createUnitN("Axemen of Lossarnach",2,1,1,1);
	sucess=stackStruct:addUnit(newUnit);
	if(sucess~=0)
	then
		--something
	end
	*/
	types.stackStruct["addUnit"] = &stackStructHelpers::addUnitToArmy;
	/***
	Attack another army. Need movepoints.

	@function stackStruct:attackArmy
	@tparam stackStruct defender
	@treturn  int  ifSucess
	@usage
	sucess=stackStruct:attackArmy(defenderArmy);
	if(sucess~=0)
	then
		--something
	end
	*/
	types.stackStruct["attackArmy"] = &stackStructHelpers::attackArmy;


	///Building table section
	//@section buildingTable

	/***
	Basic building table

	@tfield buildingData buildingData
	@tfield int level
	@tfield int hp
	@tfield settlementStruct settlement

	@table building
	*/
	types.building = luaState.new_usertype<building>("building");
	types.building["buildingData"] = &building::bData;
	types.building["level"] = &building::level;
	types.building["hp"] = &building::hp;
	types.building["settlement"] = &building::settlement;

	///BuildingData table section
	//@section buildingDataTable

	/***
	Basic buildingData table

	@tfield string type
	@tfield buildingInfo buildingInfo

	@table buildingData
	*/
	types.building_data = luaState.new_usertype<building_data>("buildingData");
	types.building_data["type"] = sol::property(
		&buildingStructHelpers::getStringPropertyBD<building_dataStruct_type>, &buildingStructHelpers::setStringPropertyBD<building_dataStruct_type>
		);
	types.building_data["buildingInfo"] = &building_data::drawInfo;


	///BuildingInfo table section
	//@section buildingInfoTable

	/***
	Basic buildingInfo table

	@tfield string name

	@table buildingInfo
	*/
	types.buildingDrawInfo = luaState.new_usertype<buildingDrawInfo>("buildingInfo");
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
	///EVENTS TABLE SECTION
	//@section eventsList

	/***
	Events functions list.
	Just list, use it without EventsFunctionsList.!!!

	@tfield draw draw
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
	Called on plugin load(at game start)

	@function onPluginLoad

	@usage
	function onPluginLoad()
	--something here
	end
	*/



	onPluginLoad = new sol::function(luaState["onPluginLoad"]);

	checkLuaFunc(&onPluginLoad);


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

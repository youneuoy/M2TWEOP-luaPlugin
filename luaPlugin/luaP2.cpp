///
//![Lua logo](../Lua.png)
//M2TWEOP structures and functions. There are not many examples and descriptions here. Also note that the examples do not include many of the checks that would be required when creating modifications.
//@module LuaPlugin
//@author youneuoy
//@license GPL-3.0
#include "luaP.h"
#include "plugData.h"
#include "gameDataAllHelper.h"
#include "battleHandlerHelpers.h"
void luaP::initP2()
{
	///gameDataAll table section
	//@section gameDataAll

	/***
	Basic gameDataAll table

	@tfield get get call it on start of your script, this is static object and pointer to it dont changes
	@tfield battleStruct battleStruct many battle data

	@table gameDataAll
	*/
	typeAll.gameDataAllTable = luaState.new_usertype<gameDataAllStruct>("gameDataAll");
	/***
	Call it on start of your script, this is static object and pointer to it dont changed
	@function gameDataAll.get
	@treturn gameDataAllStruct gameDataAll
	@usage
	gameData=gameDataAll.get();
	battleXCoord=gameData.battleStruct.xCoord;
	*/
	typeAll.gameDataAllTable["get"] = &gameDataAllHelper::get;
	typeAll.gameDataAllTable["battleStruct"] = &gameDataAllStruct::battleHandler;



	///battleStruct table section
	//@section battleStruct


	/***
	basic battleStruct table

	@tfield int xCoord
	@tfield int yCoord
	@tfield int attackerXCoord
	@tfield int attackerYCoord
	@tfield int defenderXCoord
	@tfield int defenderYCoord
	@tfield battleSide[8] sides
	@tfield int sidesNum


	@table gameDataAll.battleStruct
	*/
	typeAll.battleTable = luaState.new_usertype<battleDataS>("battleStruct");
	typeAll.battleTable["xCoord"] = &battleDataS::xCoord;
	typeAll.battleTable["yCoord"] = &battleDataS::yCoord;
	typeAll.battleTable["attackerXCoord"] = &battleDataS::attackerXCoord;
	typeAll.battleTable["attackerYCoord"] = &battleDataS::attackerYCoord;
	typeAll.battleTable["defenderXCoord"] = &battleDataS::defenderXCoord;
	typeAll.battleTable["defenderYCoord"] = &battleDataS::defenderYCoord;
	typeAll.battleTable["sides"] = sol::property([](battleDataS& self) { return std::ref(self.sides); });
	typeAll.battleTable["sidesNum"] = &battleDataS::sidesNum;


	///battleSide table section
	//@section battleSide

	/***
	basic battleStruct table

	@tfield boolean isDefender
	@tfield boolean isCanDeploy
	@tfield int[4] winConditions
	@tfield getWinConditionString getWinConditionString
	@tfield int armiesNum
	@tfield trackedPointerArmy[8] armies



	@table battleStruct.battleSide
	*/
	typeAll.battleSideTable= luaState.new_usertype<battleSide>("battleSide");
	typeAll.battleSideTable["isDefender"] = &battleSide::isDefender;
	typeAll.battleSideTable["isCanDeploy"] = &battleSide::isCanDeploy;
	typeAll.battleSideTable["winConditions"] = sol::property([](battleSide& self) { return std::ref(self.winConditions); });
	/***
	Get win condition string, for example: destroy_or_rout_enemy
	@function battleSide:getWinConditionString
	@tparam int condition
	@treturn string winCondition
	@usage
	gameData=gameDataAll.get();
	battleS=gameData.battleStruct;
	side1=gameData.battleStruct.sides[1];
	for i=1,4 do
		winCond=side1.winConditions[i];
		if(winCond~=0)then
			print(side1.getWinConditionString(winCond));
		end
	end
	*/
	typeAll.battleSideTable["getWinConditionString"] = &battleHandlerHelpers::getWinConditionS;
	typeAll.battleSideTable["armies"] = sol::property([](battleSide& self) { return std::ref(self.armies); });
	typeAll.battleSideTable["armiesNum"] = &battleSide::armiesNum;


	///trackedPointerArmy table section
	//@section trackedPointerArmy

	/***
	basic trackedPointerArmy table

	@tfield stackStruct army
	@tfield deploymentAreaS deploymentArea



	@table battleSide.trackedPointerArmy
	*/
	typeAll.trackedPointerArmyTable = luaState.new_usertype<trackedPointerArmy>("trackedPointerArmy");
	typeAll.trackedPointerArmyTable["army"] = &trackedPointerArmy::stack;
	typeAll.trackedPointerArmyTable["deploymentArea"] = &trackedPointerArmy::deploymentArea;	
	
	///deploymentAreaS table section
	//@section deploymentAreaS

	/***
	basic trackedPointerArmy table

	@tfield int coordsNum
	@tfield getCoordPair getCoordPair



	@table trackedPointerArmy.deploymentAreaS
	*/
	typeAll.deploymentAreaTable = luaState.new_usertype<deploymentAreaS>("deploymentAreaS");
	typeAll.deploymentAreaTable["coordsNum"] = &deploymentAreaS::coordsNum;
	/***
	Get pair of coords with number
	@function deploymentAreaS:getCoordPair
	@treturn float xCoord x coordinate of area
	@treturn float yCoord y coordinate of area
	@usage
	gameData=gameDataAll.get();
	battleS=gameData.battleStruct;
	side1=gameData.battleStruct.sides[1];
	deployArea1=side1.armies[1].deploymentArea;

	for i = 0, deployArea1.coordsNum-1 do
		xCoord,yCoord=side1.armies[1].deploymentArea:getCoordPair(i);
		print(xCoord,yCoord);
	end
	*/
	typeAll.deploymentAreaTable["getCoordPair"] =[](deploymentAreaS& self, int pairNum) { return std::make_tuple(self.coordsPairs[0 + pairNum], self.coordsPairs[1 + pairNum]); };
}
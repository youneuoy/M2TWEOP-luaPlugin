#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"

#include "lua/sol.hpp"
namespace gameHelpers
{
	UINT32 getFactionsCount();
	std::string callConsole(std::string cmdName,sol::variadic_args va);
	factionStruct* getFaction(int index);

	general* createCharacter(const char* type, factionStruct* fac, int age, const char* name, const char* name2, int subFaction, const char* portrait, int x, int y);
	stackStruct* createArmy(general* character);
	unit* createUnitN(const char* type, int facNum, int exp, int arm, int weap);
	unit* createUnitIdx(int eduIdx, int facNum, int exp, int arm, int weap);

	std::tuple<bool, int> getScriptCounter(const char* type);
	void setScriptCounter(const char* type,int value);
};


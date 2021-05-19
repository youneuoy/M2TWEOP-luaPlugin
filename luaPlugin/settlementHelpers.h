#pragma once
#define settlementStruct_name 1
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace settlementHelpers
{
	resStrat* getResource(const settlementStruct* sett, int index);
	building* getBuilding(const settlementStruct* sett, int index);
	void destroyBuilding(settlementStruct* sett, const char* typeName, bool isReturnMoney);
	void createBuilding(settlementStruct* sett, const char* building_level_id);

	//settlement
	template <char fieldIndex>
	std::string getStringProperty(const settlementStruct* sett)
	{
		char* retS = nullptr;
		if (fieldIndex == settlementStruct_name)
		{
			retS = sett->name;
		}

		if (retS != nullptr)
		{
			return std::string(retS);
		}
		else
		{
			return std::string("");
		}
	}

	template <char fieldIndex>
	void setStringProperty(settlementStruct* sett, std::string newS)
	{
		char* arg = nullptr;
		if (fieldIndex == settlementStruct_name)
		{

			arg = reinterpret_cast<char*>(&sett->name);
		}
		luaGetSetFuncs::setGameString(arg, newS.c_str());
	}
};


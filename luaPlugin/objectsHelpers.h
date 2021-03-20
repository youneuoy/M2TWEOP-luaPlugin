#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace objectsHelpers
{
	void setModel(int x,int y, UINT32 modelId, UINT32 modelId2);
	void addModelToGame(std::string path,UINT32 modelId);


	void replaceTile(std::string tileLabel, UINT32 x, UINT32 y, std::string fileName, std::string weather, std::string dayTime);
};


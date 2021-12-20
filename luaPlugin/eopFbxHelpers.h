#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace eopFbxHelpers
{
	void addFbxModel(const char* modelPath, const char* texturePath,int modelID);
	void deleteFbxModel(int modelID);
	void* getFbxModel(int modelID);
};


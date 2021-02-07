#pragma once
#include <string>
#include "realGameTypes.h"
#include "luaGetSetFuncs.h"
namespace resourcesHelpers
{
	void setModel(const resStrat* resource,UINT32 modelId);
	int getResourceCode(const resStrat* resource);
	int getResourceCost(const resStrat* resource);
};


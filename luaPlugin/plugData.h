#pragma once
#include "framework.h"
#include "basicFuncs.h"
#include "luaP.h"
#define basicFunc plugData::data.funcs
class plugData
{
public:
	static struct pDat
	{
		std::string modFolder;
		basicFuncs funcs;
		battleFuncs funcsBattle;

		luaP luaAll;
	}
	data;
};


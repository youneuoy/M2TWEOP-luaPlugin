#pragma once
#include <string>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

#include "lua/sol.hpp"
namespace m2tweopHelpers
{

	std::string getModPath();
	std::string getLuaPath();

	void setAncLimit(unsigned char limit);
	void seReligionsLimit(unsigned char limit);
	void setMaxBgSize(unsigned char maxBgSize);
	void unlockGameConsoleCommands();


	std::tuple<int, int, void*>  loadTextureToGame(const std::string& path);
	void unloadTextureFromGame(void* texture);

	void toggleUnitsBMapHighlight();
};


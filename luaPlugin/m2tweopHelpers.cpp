#include "m2tweopHelpers.h"
#include "plugData.h"
namespace m2tweopHelpers
{
	std::string getModPath()
	{
		return  plugData::data.modFolder;
	}
	std::string getLuaPath()
	{
		return plugData::data.luaAll.luaPath;
	}
}
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
	void setAncLimit(unsigned char limit)
	{
		(*(*plugData::data.funcs.setAncLimit))(limit);
	}
	void setMaxBgSize(unsigned char maxBgSize)
	{
		(*(*plugData::data.funcs.setMaxBgSize))(maxBgSize);
	}
	void unlockGameConsoleCommands()
	{
		(*(*plugData::data.funcs.unlockConsoleCommands))();
	}
	std::tuple<int,int,void*> loadTextureToGame(const std::string& path)
	{
		int x = 0;
		int y = 0;
		LPDIRECT3DTEXTURE9 retTexture = (*(*plugData::data.funcs.loadTexture))(path.c_str(), &x, &y);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			x, y
		});

		return std::make_tuple(x,y, reinterpret_cast<void*>(retTexture));
	}
	void unloadTextureFromGame(void* texture)
	{
		LPDIRECT3DTEXTURE9 tex = reinterpret_cast<LPDIRECT3DTEXTURE9>(texture);
		(*(*plugData::data.funcs.unloadTexture))(tex);

	}
}
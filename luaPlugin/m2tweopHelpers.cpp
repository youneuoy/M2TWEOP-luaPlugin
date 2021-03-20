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
	std::tuple<int,int,void*> loadTextureToGame(const std::string& path)
	{
		int x = 0;
		int y = 0;
		LPDIRECT3DTEXTURE9* retTexture = (*(*plugData::data.funcs.loadTexture))(path.c_str(), &x, &y);

		sol::as_table_t int2 = sol::as_table(std::vector<int>{
			x, y
		});

		return std::make_tuple(x,y, reinterpret_cast<void*>(retTexture));
	}
}
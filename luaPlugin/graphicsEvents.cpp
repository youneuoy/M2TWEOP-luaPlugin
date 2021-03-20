#include "graphicsEvents.h"
#include "console.h"
void drawOnEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (plugData::data.luaAll.drawLuaFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.drawLuaFunc)(pDevice));
	}

	console::draw();
}

void onReset(LPDIRECT3DDEVICE9 pDevice)
{
	if (plugData::data.luaAll.resetDXFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.resetDXFunc)(pDevice));
	}
}



void onChangeImGuiContext(ImGuiContext* imCtx)
{
	if (plugData::data.luaAll.initDXFunc != nullptr)
	{
		tryLua((*plugData::data.luaAll.initDXFunc)());
	}

	//do not delete this line!!!!!!!!!
	ImGui::SetCurrentContext(imCtx);
}

void onWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


}

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



void onChangeImGuiContext(ImGuiContext* imCtx)
{
	//do not delete this line!!!!!!!!!
	ImGui::SetCurrentContext(imCtx);
}

void onWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


}

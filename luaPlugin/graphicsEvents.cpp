#include "graphicsEvents.h"

void drawOnEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	/*ImGui::Begin("TestPluginsWindow");

	ImGui::Text("Test");

	ImGui::End();*/
}



void onChangeImGuiContext(ImGuiContext* imCtx)
{
	//do not delete this line!!!!!!!!!
	ImGui::SetCurrentContext(imCtx);
}

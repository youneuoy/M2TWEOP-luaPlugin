#include "console.h"
#include "imgui_stdlib.h"
#include "plugData.h"

namespace console
{
	struct
	{
		std::string input;
		
		bool isDraw = false;
	}consoleData;

	void applyCommand()
	{
		if (consoleData.input.size() > 0)
		{
			plugData::data.luaAll.logS+="Command: "+consoleData.input+"\n";
		}
		else
		{
			return;
		}


		plugData::data.luaAll.runScriptS(&consoleData.input);

		consoleData.input.clear();
	}

	void draw()
	{

		if ((ImGui::GetIO().KeysDownDuration[VK_CONTROL] > 0.f && ImGui::GetIO().KeysDownDuration['1'] > 0.f&& ImGui::GetIO().KeysDownDuration['9']>0.f)
			&& (ImGui::GetIO().KeysDownDurationPrev[VK_CONTROL] == 0.f || ImGui::GetIO().KeysDownDurationPrev['1'] == 0.f|| ImGui::GetIO().KeysDownDuration['9'] == 0.f)
			)
		{
			plugData::data.luaAll.resetState();
			return;

		}

		if ((ImGui::GetIO().KeysDownDuration[VK_CONTROL] > 0.f && ImGui::GetIO().KeysDownDuration['1'] > 0.f)
			&& (ImGui::GetIO().KeysDownDurationPrev[VK_CONTROL] == 0.f || ImGui::GetIO().KeysDownDurationPrev['1'] == 0.f)
			)
		{

			consoleData.isDraw = !consoleData.isDraw;

			if (plugData::data.luaAll.checkVar("enableConsole", 1) == false)
			{
				consoleData.isDraw = false;
			}
		}
		if (consoleData.isDraw == false)
		{
			return;
		}



		ImGuiWindowFlags iwf = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowSize(ImVec2(800, 0));
		ImGui::SetNextWindowPos(ImVec2(0.5f, 0.5f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));


		ImGui::Begin("##consoleWindow", NULL, iwf);

		ImGui::InputTextMultiline("##consoleLog", &plugData::data.luaAll.logS, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 8), ImGuiInputTextFlags_AllowTabInput);


		ImGui::InputTextMultiline("##console", &consoleData.input, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() *4), ImGuiInputTextFlags_AllowTabInput);
		if (ImGui::Button("Run"))
		{
			applyCommand();
		}
		ImGui::End();
	}

}
#include "console.h"
#include "imgui_stdlib.h"
#include "plugData.h"
#include "pluginM2TWEOP.h"
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
			plugData::data.luaAll.logS.push_back("Command: "+consoleData.input+'\n');
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
			initLua();
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



		ImGuiWindowFlags iwf = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse;
		ImGui::SetNextWindowSize(ImVec2(800, 0), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0.5f, 0.5f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));


		ImGui::Begin("##consoleWindow", NULL, iwf);


		ImGui::BeginChild("##consoleLogW", ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 12), false, ImGuiWindowFlags_HorizontalScrollbar);
		
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGuiListClipper clipper;
		clipper.Begin(plugData::data.luaAll.logS.size());
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				std::string* currS = &plugData::data.luaAll.logS[line_no];

				ImGui::PushID(currS);
				ImGui::SetNextItemWidth(-1);
				ImGui::InputTextMultiline("##consoleLog", currS, ImVec2(0, 0), ImGuiInputTextFlags_ReadOnly);
				ImGui::PopID();
			}
		}
		clipper.End();
		ImGui::PopStyleVar();
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);
		ImGui::EndChild();

		ImGui::InputTextMultiline("##console", &consoleData.input, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() *4), ImGuiInputTextFlags_AllowTabInput);
		if (ImGui::Button("Run"))
		{
			applyCommand();
		}

		ImGui::End();
	}

}
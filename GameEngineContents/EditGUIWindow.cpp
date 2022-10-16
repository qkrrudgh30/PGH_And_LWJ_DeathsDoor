#include "PreCompile.h"
#include "EditGUIWindow.h"

EditGUIWindow::EditGUIWindow() 
{
}

EditGUIWindow::~EditGUIWindow() 
{
}

void EditGUIWindow::Initialize(GameEngineLevel* _Level)
{
}

void EditGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("Create landscape");	
	/*if (true == ImGui::BeginMenu("Landscape"))
	{
		if (ImGui::MenuItem("Landscape01", "Ctrl+O")) 
		{ 
			int a = 10;
		}
		if (ImGui::MenuItem("Landscape02", "Ctrl+S")) 
		{ 
			int a = 10;
		}
		if (ImGui::MenuItem("Landscape03", "Ctrl+W")) 
		{ 
			int a = 10;
		}
		ImGui::EndMenu();
	}*/

	static int selected = 0;
	ImGui::BeginChild("left pane", ImVec2(150, 100), true);
	for (int i = 0; i < 100; i++)
	{
		char label[128];
		sprintf(label, "MyObject %d", i);
		if (ImGui::Selectable(label, selected == i))
		{
			selected = i;
		}
	}
	ImGui::EndChild();

	static int s_iXcount, s_iYCount, s_iZCount;
	ImGui::InputInt("X COUNT", &s_iXcount);
	ImGui::InputInt("Y COUNT", &s_iYCount);
	ImGui::InputInt("Z COUNT", &s_iZCount);

	if (ImGui::Button("Create"))
	{
		// SendInfoToMouseSlotFunction();
	}
}


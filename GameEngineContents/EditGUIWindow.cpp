#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"

#include <filesystem>

EditGUIWindow::EditGUIWindow() 
{
}

EditGUIWindow::~EditGUIWindow() 
{
}

void EditGUIWindow::Initialize(GameEngineLevel* _Level)
{
#pragma region PushPannel
	m_CurrentDirectory.MoveParentToExitsChildDirectory("ContentsResources");
	m_CurrentDirectory.Move("ContentsResources");
	m_CurrentDirectory.Move("Texture");
	m_CurrentDirectory.Move("EditLevel");
	m_CurrentDirectory.Move("Actor");
	std::filesystem::directory_iterator dirIter1(m_CurrentDirectory.GetFullPath());
	for (const std::filesystem::directory_entry& entry : dirIter1)
	{
		std::string Ext(entry.path().string());
		if (true == entry.is_directory())
		{
			size_t idx = Ext.rfind("\\");
			std::string strTemp(entry.path().string());
			std::string strTemp2(strTemp.substr(idx + 1));
			m_vLoadedFromActor.push_back(strTemp2);
		}
	}

	m_CurrentDirectory.Move("..\\");
	m_CurrentDirectory.Move("Tile");
	std::filesystem::directory_iterator dirIter2(m_CurrentDirectory.GetFullPath());

	for (const std::filesystem::directory_entry& entry : dirIter2)
	{
		std::string Ext(entry.path().string());
		if (true == entry.is_directory())
		{
			size_t idx = Ext.rfind("\\");
			std::string strTemp(entry.path().string());
			std::string strTemp2(strTemp.substr(idx + 1));
			m_vLoadedFromTile.push_back(strTemp2);
		}
	}
#pragma endregion	
}

void EditGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == EditLevelPipe::GetInst()->GetEditLevel()) { return; }
	else { m_ptrEditLevel = EditLevelPipe::GetInst()->GetEditLevel(); }

	// Edit Level인지 체크 필요.
	ImGui::Text("Create landscape");	

#pragma region SelectLandscapePannel
	static int selected = 0;
	static int selectedPannel = ACTORPANNEL;
	if (true == ImGui::Button("Actor"))
	{
		selectedPannel = ACTORPANNEL;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Tile"))
	{
		selectedPannel = TILEPANNEL;
	}

	if (ACTORPANNEL == selectedPannel)
	{
		ImGui::BeginChild("left pane", ImVec2(150, 100), true);
		for (int i = 0; i < m_vLoadedFromActor.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_vLoadedFromActor[i].c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, selected == i))
			{
				selected = i;
			}
		}
		ImGui::EndChild();
	}
	else if (TILEPANNEL == selectedPannel)
	{
		ImGui::BeginChild("left pane", ImVec2(150, 100), true);
		for (int i = 0; i < m_vLoadedFromTile.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_vLoadedFromTile[i].c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, selected == i))
			{
				selected = i;
			}
		}
		ImGui::EndChild();
	}

	ImGui::SameLine();
#pragma endregion	

#pragma region CreatedActorsPannel
	static int selectedActor = 0;
	ImGui::BeginChild("left pane2", ImVec2(150, 100), true);

	if (0 == m_vCreatedActors.size())
	{
		if (ImGui::Selectable("Empty...", selectedActor == 0))
		{
			selectedActor = 0;
		}
	}
	else
	{
		for (int i = 0; i < m_vCreatedActors.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_vCreatedActors[i].first.c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, selectedActor == i))
			{
				selectedActor = i;
			}
		}
	}
	ImGui::EndChild();
#pragma endregion

	static int s_iXCount, s_iYCount, s_iZCount;
	ImGui::InputInt("X Count", &s_iXCount);
	ImGui::InputInt("Y Count", &s_iYCount);
	ImGui::InputInt("Z Count", &s_iZCount);

	static float s_iXScale, s_iYScale, s_iZScale;
	ImGui::InputFloat("X Scale", &s_iXScale);
	ImGui::InputFloat("Y Scale", &s_iYScale);
	ImGui::InputFloat("Z Scale", &s_iZScale);

	if (true == ImGui::Button("Create"))
	{
		// SendInfoToMouseSlotFunction();
		std::string tempStr;
		if (ACTORPANNEL == selectedPannel) { tempStr = m_vLoadedFromActor[selected]; }
		else if (TILEPANNEL == selectedPannel) { tempStr = m_vLoadedFromTile[selected]; }
		GameEngineActor* temp = m_ptrEditLevel->CreateActor<TestActor>();
		temp->GetTransform().SetWorldScale(float4{ s_iXScale, s_iYScale, s_iZScale , 1.f});

		std::pair tempPair(tempStr, temp);
		m_vCreatedActors.push_back(tempPair);

	}

	ImGui::SameLine();

	if (true == ImGui::Button("Load"))
	{
		// SendInfoToMouseSlotFunction();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Save"))
	{
		// SendInfoToMouseSlotFunction();
	}
}


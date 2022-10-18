#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"
#include "Player.h"

#include <filesystem>

EditGUIWindow::EditGUIWindow() 
	: m_ptrEditLevel(nullptr)
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

	if (false == GameEngineInput::GetInst()->IsKey("SelectedObjectUp"))
	{
		GameEngineInput::GetInst()->CreateKey("SelectedObjectUp", 'T');
		GameEngineInput::GetInst()->CreateKey("SelectedObjectDown", 'G');
		GameEngineInput::GetInst()->CreateKey("SelectedObjectLeft", 'F');
		GameEngineInput::GetInst()->CreateKey("SelectedObjectRight", 'H');
		GameEngineInput::GetInst()->CreateKey("SelectedObjectForward", 'R');
		GameEngineInput::GetInst()->CreateKey("SelectedObjectBackward", 'Y');
		GameEngineInput::GetInst()->CreateKey("SelectedObjectRotate", MK_LBUTTON);
	}
}

void EditGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == EditLevelPipe::GetInst()->GetEditLevel()) { return; }
	else { m_ptrEditLevel = EditLevelPipe::GetInst()->GetEditLevel(); }

	// Edit Level인지 체크 필요.

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
			std::string tempStr = m_vLoadedFromActor[i];
			sprintf(label, (tempStr + "-(%d)").c_str(), i);
			if (ImGui::Selectable(label, selectedActor == i))
			{
				selectedActor = i;
			}
		}
	}
	ImGui::EndChild();

	
#pragma endregion

#pragma region TransformSelectedObject
	static int s_iXCount, s_iYCount, s_iZCount;
	ImGui::InputInt("X Count", &s_iXCount);
	ImGui::InputInt("Y Count", &s_iYCount);
	ImGui::InputInt("Z Count", &s_iZCount);

	static float s_fXScale, s_fYScale, s_fZScale;
	ImGui::InputFloat("X Scale", &s_fXScale);
	ImGui::InputFloat("Y Scale", &s_fYScale);
	ImGui::InputFloat("Z Scale", &s_fZScale);

	ImGui::Text("Moving: ");
	static float s_fXPos, s_fYPos, s_fZPos;
	ImGui::InputFloat("X Position", &s_fXPos);
	ImGui::InputFloat("Y Position", &s_fYPos);
	ImGui::InputFloat("Z Position", &s_fZPos);

	ImGui::Text("Rotating: Mouse");
	static float s_fXRot, s_fYRot, s_fZRot;
	ImGui::InputFloat("X Rotation", &s_fXRot);
	ImGui::InputFloat("Y Rotation", &s_fYRot);
	ImGui::InputFloat("Z Rotation", &s_fZRot);
#pragma endregion


	if (true == ImGui::Button("Create"))
	{
		// SendInfoToMouseSlotFunction();
		std::string tempStr;
		if (ACTORPANNEL == selectedPannel) { tempStr = m_vLoadedFromActor[selected]; }
		else if (TILEPANNEL == selectedPannel) { tempStr = m_vLoadedFromTile[selected]; }
		GameEngineActor* temp = m_ptrEditLevel->CreateActor<TestActor>();
		temp->GetTransform().SetLocalScale(float4{ s_fXScale, s_fYScale, s_fZScale , 1.f});
		temp->GetTransform().SetLocalPosition(float4{ s_fXPos, s_fYPos, s_fZPos , 1.f});
		temp->GetTransform().SetLocalRotate(float4{ s_fXRot , s_fYRot , s_fZRot });

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

#pragma region SelectedObjectMovement
	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectUp"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetUpVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectDown"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetDownVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectLeft"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetLeftVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRight"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetRightVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectForward"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetForwardVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectBackward"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetBackVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(dir * 400.f * _DeltaTime);
	}
#pragma endregion

#pragma region SelectedObjectRotation
	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectUp"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetUpVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectDown"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetDownVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectLeft"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetLeftVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectRight"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetRightVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectForward"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetForwardVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(dir * 400.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectBackward"))
	{
		float4 dir = m_vCreatedActors[selectedActor].second->GetTransform().GetBackVector();
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(dir * 400.f * _DeltaTime);
	}
#pragma endregion

}


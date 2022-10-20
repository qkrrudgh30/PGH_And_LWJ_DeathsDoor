#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"
#include "Player.h"

#include <filesystem>
#include <fstream>

EditGUIWindow::EditGUIWindow() 
	: m_ptrEditLevel(nullptr)
{
}

EditGUIWindow::~EditGUIWindow() 
{
}

void EditGUIWindow::Initialize(GameEngineLevel* _Level)
{
	m_ProjectDirectory.MoveParentToExitsChildDirectory("ContentsResources");
	m_ProjectDirectory.Move("ContentsResources");
	m_ProjectDirectory.Move("Texture");

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
		if (false == entry.is_directory())
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
		if (false == entry.is_directory())
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
			std::string tempStr = m_vCreatedActors[i].first;
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
	// static int s_iXCount, s_iYCount, s_iZCount;
	// ImGui::InputInt("X Count", &s_iXCount);
	// ImGui::InputInt("Y Count", &s_iYCount);
	// ImGui::InputInt("Z Count", &s_iZCount);

	static float s_fXScale = 1.f, s_fYScale = 1.f, s_fZScale = 1.f;
	ImGui::InputFloat("X Scale", &s_fXScale);
	ImGui::InputFloat("Y Scale", &s_fYScale);
	ImGui::InputFloat("Z Scale", &s_fZScale);

	static float s_fXRot = 0.f, s_fYRot = 0.f, s_fZRot = 0.f;
	ImGui::InputFloat("X Rotation", &s_fXRot);
	ImGui::InputFloat("Y Rotation", &s_fYRot);
	ImGui::InputFloat("Z Rotation", &s_fZRot);

	static float s_fXPos = 0.f, s_fYPos = 0.f, s_fZPos = 0.f;
	ImGui::InputFloat("X Position", &s_fXPos);
	ImGui::InputFloat("Y Position", &s_fYPos);
	ImGui::InputFloat("Z Position", &s_fZPos);
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

	if (true == ImGui::Button("Delete"))
	{
		auto iterBeg = m_vCreatedActors.begin();
		auto iterEnd = m_vCreatedActors.end();
		for (int i = 0; iterBeg != iterEnd; ++i)
		{
			if (selectedActor == i) 
			{ 
				m_vCreatedActors[i].second->Death();
				m_vCreatedActors.erase(iterBeg); 
				break; 
			}
			++iterBeg;
		}
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Load"))
	{
		Load();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Save"))
	{
		Save();
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

void EditGUIWindow::Save()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);      
	ofn.hwndOwner = GameEngineWindow::GetHWND(); 
	wchar_t szName[256] = {};
	ofn.lpstrFile = (LPSTR)szName;               
	ofn.nMaxFile = sizeof(szName);               
	// ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	// ofn.nFilterIndex = 0;                        // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; 
	ofn.nMaxFileTitle = 0; 
	std::string strTileFolder(m_ProjectDirectory.GetFullPath());
	// strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();       // 초기경로. 
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (TRUE == GetSaveFileName(&ofn))
	{
		std::filesystem::path p(ofn.lpstrFile);
		SaveTileData(p.filename().string());
	}
}

void EditGUIWindow::SaveTileData(const std::string& _strTitle)
{
	std::ofstream fout;

	fout.open(_strTitle);

	fout << m_vCreatedActors.size() << '\n';

	for (auto& item : m_vCreatedActors)
	{

		fout << item.first << ' ' 
			<< item.second->GetTransform().GetLocalScale().x << ' '
			<< item.second->GetTransform().GetLocalScale().y << ' '
			<< item.second->GetTransform().GetLocalScale().z << ' '

			<< item.second->GetTransform().GetLocalRotation().x << ' '
			<< item.second->GetTransform().GetLocalRotation().y << ' '
			<< item.second->GetTransform().GetLocalRotation().z << ' '
			
			<< item.second->GetTransform().GetLocalPosition().x << ' '
			<< item.second->GetTransform().GetLocalPosition().y << ' '
			<< item.second->GetTransform().GetLocalPosition().z << ' '
			<< '\n';
	}

	fout.close();
}

void EditGUIWindow::Load()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameEngineWindow::GetHWND();
	wchar_t szName[256] = {};
	ofn.lpstrFile = (LPSTR)szName;               // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName);               
	// ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; 
	ofn.nFilterIndex = 0; 
	ofn.lpstrFileTitle = nullptr; 
	ofn.nMaxFileTitle = 0; 
	std::string strTileFolder(m_ProjectDirectory.GetFullPath());
	// strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); 
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; 

	if (TRUE == GetSaveFileName(&ofn))
	{
		std::filesystem::path p(ofn.lpstrFile);

		std::ifstream fin;
		fin.open(p);

		int uCount = 0;

		fin >> uCount;

		std::string strName;
		float4 f4Scale, f4Rotation, f4Position;
		for (int i = 0; i < uCount; ++i)
		{
			fin >> strName 
				>> f4Scale.x >> f4Scale.y >> f4Scale.z
				>> f4Rotation.x >> f4Rotation.y >> f4Rotation.z
				>> f4Position.x >> f4Position.y >> f4Position.z;

			GameEngineActor* temp = m_ptrEditLevel->CreateActor<TestActor>();
			temp->GetTransform().SetLocalScale(f4Scale);
			temp->GetTransform().SetLocalRotate(f4Rotation);
			temp->GetTransform().SetLocalPosition(f4Position);

			std::pair tempPair(strName, temp);
			m_vCreatedActors.push_back(tempPair);

		}


		// LoadTileData(p.filename().string());
	}
}

void EditGUIWindow::LoadTileData(const std::string& _strFilePath)
{
	int a = 0;
}

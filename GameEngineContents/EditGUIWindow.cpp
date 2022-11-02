#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"
#include "Player.h"
#include "StaticMesh.h"

#include <filesystem>
#include <fstream>

#include <GameEngineCore/GameEngineFBXRenderer.h>

std::vector<std::string> EditGUIWindow::m_vLoadedFromAnimator;
std::vector<std::string> EditGUIWindow::m_vLoadedFromStatic;

float EditGUIWindow::s_farrScaleOnEditGUI[3];
float EditGUIWindow::s_farrRotationOnEditGUI[3];
float EditGUIWindow::s_farrPositionOnEditGUI[3];

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
	/*m_CurrentDirectory.MoveParentToExitsChildDirectory("ContentsResources");
	m_CurrentDirectory.Move("ContentsResources");
	m_CurrentDirectory.Move("Texture");
	m_CurrentDirectory.Move("07_EditLevel");
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
			m_vLoadedFromAnimator.push_back(strTemp2);
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
			m_vLoadedFromStatic.push_back(strTemp2);
		}
	}*/
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
	// else { m_ptrEditLevel = ; }

	// Edit Level인지 체크 필요.

#pragma region SelectLandscapePannel
	static int selected = 0;
	static int selectedPannel = AnimatorPannel;
	if (true == ImGui::Button("Animator"))
	{
		selectedPannel = AnimatorPannel;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Static"))
	{
		selectedPannel = StaticPannel;
	}

	if (AnimatorPannel == selectedPannel)
	{
		ImGui::BeginChild("Animator", ImVec2(150, 100), true);
		for (int i = 0; i < m_vLoadedFromAnimator.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_vLoadedFromAnimator[i].c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, selected == i))
			{
				selected = i;
			}
		}
		ImGui::EndChild();
	}
	else if (StaticPannel == selectedPannel)
	{
		ImGui::BeginChild("Static", ImVec2(150, 100), true);
		for (int i = 0; i < m_vLoadedFromStatic.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_vLoadedFromStatic[i].c_str());
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
	ImGui::BeginChild("Created", ImVec2(150, 100), true);

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
	ImGui::InputFloat3("Scale", s_farrScaleOnEditGUI);
	ImGui::InputFloat3("Rotation", s_farrRotationOnEditGUI);
	ImGui::InputFloat3("Position", s_farrPositionOnEditGUI);

#pragma endregion

	if (true == ImGui::Button("Create"))
	{
		// SendInfoToMouseSlotFunction();
		std::string tempStr;
		if (AnimatorPannel == selectedPannel) { tempStr = m_vLoadedFromAnimator[selected]; }
		else if (StaticPannel == selectedPannel) { tempStr = m_vLoadedFromStatic[selected]; }
		StaticMesh* temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
		temp->GetFBXRenderer()->SetFBXMesh(tempStr + ".fbx", "Texture");
		
		temp->GetTransform().SetLocalScale(float4{ s_farrScaleOnEditGUI[0], s_farrScaleOnEditGUI[1], s_farrScaleOnEditGUI[2] , 1.f});
		temp->GetTransform().SetLocalRotate(float4{ s_farrPositionOnEditGUI[0] , s_farrPositionOnEditGUI[1] , s_farrPositionOnEditGUI[2]});
		temp->GetTransform().SetLocalPosition(float4{ s_farrRotationOnEditGUI[0], s_farrRotationOnEditGUI[1], s_farrRotationOnEditGUI[2], 1.f});

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
				m_vCreatedActors[i] = std::make_pair<std::string, StaticMesh*>("NULL", nullptr);
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
	if (0 != m_vCreatedActors.size())
	{
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
	}
	
#pragma endregion

#pragma region SelectedObjectRotation
	if (0 != m_vCreatedActors.size())
	{
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
	}
#pragma endregion

#pragma region ValueUpdate
	if (0 != m_vCreatedActors.size() && true == CheckChanges(selectedActor))
	{
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalScale(s_farrScaleOnEditGUI[0]);
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalScale(s_farrScaleOnEditGUI[1]);
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalScale(s_farrScaleOnEditGUI[2]);

		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotation(s_farrRotationOnEditGUI[0]);
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotation(s_farrRotationOnEditGUI[1]);
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotation(s_farrRotationOnEditGUI[2]);

		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalPosition(s_farrPositionOnEditGUI[0]);
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalPosition(s_farrPositionOnEditGUI[1]);
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalPosition(s_farrPositionOnEditGUI[2]);
	}
	
	if (0 != m_vCreatedActors.size() && nullptr != m_vCreatedActors[selectedActor].second)
	{
		s_farrScaleOnEditGUI[0] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalScale().x;
		s_farrScaleOnEditGUI[1] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalScale().y;
		s_farrScaleOnEditGUI[2] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalScale().z;

		s_farrRotationOnEditGUI[0] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalRotation().x;
		s_farrRotationOnEditGUI[1] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalRotation().y;
		s_farrRotationOnEditGUI[2] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalRotation().z;

		s_farrPositionOnEditGUI[0] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalPosition().x;
		s_farrPositionOnEditGUI[1] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalPosition().y;
		s_farrPositionOnEditGUI[2] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalPosition().z;
	}

#pragma endregion

}

bool EditGUIWindow::CheckChanges(int _iSelectedActor)
{
	if (
		s_farrScaleOnEditGUI[0] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().x &&
		s_farrScaleOnEditGUI[1] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().y &&
		s_farrScaleOnEditGUI[2] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().z &&

		s_farrRotationOnEditGUI[0] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().x &&
		s_farrRotationOnEditGUI[1] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().y &&
		s_farrRotationOnEditGUI[2] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().z &&

		s_farrPositionOnEditGUI[0] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().x &&
		s_farrPositionOnEditGUI[1] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().y &&
		s_farrPositionOnEditGUI[2] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().z
		)
	{
		return true;
	}

	return false;
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

			StaticMesh* temp = m_ptrEditLevel->CreateActor<StaticMesh>();
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

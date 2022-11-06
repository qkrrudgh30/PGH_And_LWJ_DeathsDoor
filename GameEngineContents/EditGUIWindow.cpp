#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"
#include "Player.h"
#include "StaticMesh.h"

#include <filesystem>
#include <fstream>
#include <iomanip>

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

std::set<std::string> EditGUIWindow::m_setLoadedFromAnimator;
std::set<std::string> EditGUIWindow::m_setLoadedFromStatic;

float EditGUIWindow::s_farrCurrScaleOnEditGUI[3] = {1.f, 1.f, 1.f};
float EditGUIWindow::s_farrPrevScaleOnEditGUI[3] = {1.f, 1.f, 1.f};
float EditGUIWindow::s_farrCurrRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrCurrPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };

float EditGUIWindow::s_farrCurrColliderScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrCurrColliderRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrCurrColliderPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };

EditGUIWindow::EditGUIWindow() 
{
}

EditGUIWindow::~EditGUIWindow() 
{
}

void EditGUIWindow::Initialize(GameEngineLevel* _Level)
{
	m_ProjectDirectory.MoveParentToExitsChildDirectory("ContentsResources");
	m_ProjectDirectory.Move("ContentsResources");
	m_ProjectDirectory.Move("Asset");

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
#pragma region SwitchPannel
	static size_t uSelectedPannel = AnimatorPannel;
	static size_t uSelectedObject = 0;
	if (true == ImGui::Button("Animator"))
	{
		uSelectedPannel = AnimatorPannel;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Static"))
	{
		uSelectedPannel = StaticPannel;
	}


	if (AnimatorPannel == uSelectedPannel)
	{
		ImGui::BeginChild("Animator", ImVec2(150, 100), true);
		std::set<std::string>::iterator iterBeg = m_setLoadedFromAnimator.begin();
		std::set<std::string>::iterator iterEnd = m_setLoadedFromAnimator.end();

		size_t i = 0;
		while (iterBeg != iterEnd)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(iterBeg->c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, uSelectedObject == i))
			{
				uSelectedObject = i;
			}

			++i;
			++iterBeg;
		}

		/*for (int i = 0; i < m_setLoadedFromAnimator.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_setLoadedFromAnimator[i].c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, uSelectedObject == i))
			{
				uSelectedObject = i;
			}
		}*/
		ImGui::EndChild();
	}
	else if (StaticPannel == uSelectedPannel)
	{
		ImGui::BeginChild("Static", ImVec2(150, 100), true);
		
		std::set<std::string>::iterator iterBeg = m_setLoadedFromStatic.begin();
		std::set<std::string>::iterator iterEnd = m_setLoadedFromStatic.end();

		size_t i = 0;
		while (iterBeg != iterEnd)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(iterBeg->c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, uSelectedObject == i))
			{
				uSelectedObject = i;
			}

			++i;
			++iterBeg;
		}
		
		/*for (int i = 0; i < m_setLoadedFromStatic.size(); ++i)
		{
			char label[1024] = { '\0', };
			const char* temp = (const char*)(m_setLoadedFromStatic[i].c_str());
			sprintf(label, temp);
			if (ImGui::Selectable(label, uSelectedObject == i))
			{
				uSelectedObject = i;
			}
		}*/
		ImGui::EndChild();
	}

	ImGui::SameLine();
#pragma endregion

#pragma region CreaturePannel
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
	ImGui::InputFloat3("Scale", s_farrCurrScaleOnEditGUI);
	ImGui::InputFloat3("Rotation", s_farrCurrRotationOnEditGUI);
	ImGui::InputFloat3("Position", s_farrCurrPositionOnEditGUI);

#pragma endregion

#pragma region TransformSelectedObjectCollider
	ImGui::InputFloat3("Collider Scale", s_farrCurrColliderScaleOnEditGUI);
	ImGui::InputFloat3("Collider Rotation", s_farrCurrColliderRotationOnEditGUI);
	ImGui::InputFloat3("Collider Position", s_farrCurrColliderPositionOnEditGUI);

	if (0 != m_vCreatedActors.size() && nullptr != m_vCreatedActors[selectedActor].second)
	{
		m_vCreatedActors[selectedActor].second->GetCollider()->GetTransform().SetLocalScale(float4{ s_farrCurrColliderScaleOnEditGUI[0], s_farrCurrColliderScaleOnEditGUI[1], s_farrCurrColliderScaleOnEditGUI[2] });
		m_vCreatedActors[selectedActor].second->GetCollider()->GetTransform().SetLocalRotation(float4{ s_farrCurrColliderRotationOnEditGUI[0], s_farrCurrColliderRotationOnEditGUI[1], s_farrCurrColliderRotationOnEditGUI[2] });
		m_vCreatedActors[selectedActor].second->GetCollider()->GetTransform().SetLocalPosition(float4{ s_farrCurrColliderPositionOnEditGUI[0], s_farrCurrColliderPositionOnEditGUI[1], s_farrCurrColliderPositionOnEditGUI[2] });
	}

#pragma endregion

#pragma region CallbackForButtons
	if (true == ImGui::Button("Create"))
	{
		// SendInfoToMouseSlotFunction();
		std::string tempStr;
		if (AnimatorPannel == uSelectedPannel) 
		{ 
			std::set<std::string>::iterator iterToSelectedObject = m_setLoadedFromAnimator.begin();
			size_t i = uSelectedObject;
			while (0 != i) { ++iterToSelectedObject; --i; }
			tempStr = iterToSelectedObject->c_str();
		}
		else if (StaticPannel == uSelectedPannel) 
		{ 
			std::set<std::string>::iterator iterToSelectedObject = m_setLoadedFromStatic.begin();
			size_t i = uSelectedObject;
			while (0 != i) { ++iterToSelectedObject; --i; }
			tempStr = iterToSelectedObject->c_str();
		}
		StaticMesh* temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
		temp->SetPriorityInitialize();
		temp->GetFBXRenderer()->SetFBXMesh(tempStr + ".fbx", "Texture");

		temp->GetTransform().SetLocalScale(float4{ s_farrCurrScaleOnEditGUI[0], s_farrCurrScaleOnEditGUI[1], s_farrCurrScaleOnEditGUI[2] , 1.f });
		temp->GetTransform().SetLocalRotate(float4{ s_farrCurrPositionOnEditGUI[0] , s_farrCurrPositionOnEditGUI[1] , s_farrCurrPositionOnEditGUI[2] });
		temp->GetTransform().SetLocalPosition(float4{ s_farrCurrRotationOnEditGUI[0], s_farrCurrRotationOnEditGUI[1], s_farrCurrRotationOnEditGUI[2], 1.f });

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
		PrepareForLoading();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Save"))
	{
		PrepareForSaving();
	}
#pragma endregion

#pragma region SelectedObjectMovement
	if (0 != m_vCreatedActors.size())
	{
		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectUp"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(float4::UP * 400.f * _DeltaTime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectDown"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(float4::DOWN * 400.f * _DeltaTime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectLeft"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(float4::LEFT * 400.f * _DeltaTime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectRight"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(float4::RIGHT * 400.f * _DeltaTime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectForward"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(float4::FORWARD * 400.f * _DeltaTime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectBackward"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalMove(float4::BACK * 400.f * _DeltaTime);
		}
	}
	
#pragma endregion

#pragma region SelectedObjectRotation
	if (0 != m_vCreatedActors.size())
	{
		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectUp"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(float4::UP * 400.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectDown"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(float4::DOWN * 400.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectLeft"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(float4::LEFT * 400.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectRight"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(float4::RIGHT * 400.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectForward"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(float4::FORWARD * 400.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectBackward"))
		{
			m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotate(float4::BACK * 400.f * _DeltaTime);
		}
	}
#pragma endregion

#pragma region SyncronizeStaticValue
	// curr 값 변경 -> prev 값 체크 -> 엑터 값 업데이트
	// 엑터값 변경(화살표) -> prev 값과 체크 -> curr 값 변경

	if (0 != m_vCreatedActors.size() && true == CheckChangesAboutCurrStaticValue(selectedActor))
	{
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalScale(float4{ s_farrCurrScaleOnEditGUI[0], s_farrCurrScaleOnEditGUI[1], s_farrCurrScaleOnEditGUI[2] });
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalRotation(float4{ s_farrCurrRotationOnEditGUI[0], s_farrCurrRotationOnEditGUI[1], s_farrCurrRotationOnEditGUI[2] });
		m_vCreatedActors[selectedActor].second->GetTransform().SetLocalPosition(float4{ s_farrCurrPositionOnEditGUI[0], s_farrCurrPositionOnEditGUI[1], s_farrCurrPositionOnEditGUI[2] });
	}

	if (0 != m_vCreatedActors.size() && nullptr != m_vCreatedActors[selectedActor].second
		&& true == CheckChangesAboutCreature(selectedActor))
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrCurrScaleOnEditGUI[i] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalScale().Arr1D[i];
			s_farrCurrRotationOnEditGUI[i] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalRotation().Arr1D[i];
			s_farrCurrPositionOnEditGUI[i] = m_vCreatedActors[selectedActor].second->GetTransform().GetLocalPosition().Arr1D[i];
		}
	}

#pragma endregion

}

bool EditGUIWindow::CheckChangesAboutCreature(int _iSelectedActor)
{
	if (m_vCreatedActors.size() <= _iSelectedActor)
	{
		return false;
	}

	if (
		s_farrPrevScaleOnEditGUI[0] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().x ||
		s_farrPrevScaleOnEditGUI[1] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().y ||
		s_farrPrevScaleOnEditGUI[2] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().z ||

		s_farrPrevRotationOnEditGUI[0] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().x ||
		s_farrPrevRotationOnEditGUI[1] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().y ||
		s_farrPrevRotationOnEditGUI[2] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().z ||

		s_farrPrevPositionOnEditGUI[0] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().x ||
		s_farrPrevPositionOnEditGUI[1] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().y ||
		s_farrPrevPositionOnEditGUI[2] != m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().z
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevScaleOnEditGUI[i] = m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalScale().Arr1D[i];
			s_farrPrevRotationOnEditGUI[i] = m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalRotation().Arr1D[i];
			s_farrPrevPositionOnEditGUI[i] = m_vCreatedActors[_iSelectedActor].second->GetTransform().GetLocalPosition().Arr1D[i];
		}

		return true;
	}

	return false;
}

bool EditGUIWindow::CheckChangesAboutCurrStaticValue(int _iSelectedActor)
{
	if (m_vCreatedActors.size() <= _iSelectedActor)
	{
		return false;
	}

	if (
		s_farrPrevScaleOnEditGUI[0] != s_farrCurrScaleOnEditGUI[0] ||
		s_farrPrevScaleOnEditGUI[1] != s_farrCurrScaleOnEditGUI[1] ||
		s_farrPrevScaleOnEditGUI[2] != s_farrCurrScaleOnEditGUI[2] ||

		s_farrPrevRotationOnEditGUI[0] != s_farrCurrRotationOnEditGUI[0] ||
		s_farrPrevRotationOnEditGUI[1] != s_farrCurrRotationOnEditGUI[1] ||
		s_farrPrevRotationOnEditGUI[2] != s_farrCurrRotationOnEditGUI[2] ||

		s_farrPrevPositionOnEditGUI[0] != s_farrCurrPositionOnEditGUI[0] ||
		s_farrPrevPositionOnEditGUI[1] != s_farrCurrPositionOnEditGUI[1] ||
		s_farrPrevPositionOnEditGUI[2] != s_farrCurrPositionOnEditGUI[2]
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevScaleOnEditGUI[i]    = s_farrCurrScaleOnEditGUI[i];
			s_farrPrevRotationOnEditGUI[i] = s_farrCurrScaleOnEditGUI[i];
			s_farrPrevPositionOnEditGUI[i] = s_farrCurrScaleOnEditGUI[i];
		}

		return true;
	}

	return false;
}

void EditGUIWindow::PrepareForSaving()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);      
	ofn.hwndOwner = GameEngineWindow::GetHWND(); 
	wchar_t szName[256] = {};
	std::string strTileFolder(m_ProjectDirectory.GetFullPath());
#ifdef _DEBUG
	ofn.lpstrFile = (LPSTR)szName;               // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.lpstrInitialDir = (LPSTR)(strTileFolder.c_str());
#else
	ofn.lpstrFile = (LPWSTR)szName;               // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.lpstrInitialDir = (LPWSTR)strTileFolder.c_str();
#endif // DEBUG               
	ofn.nMaxFile = sizeof(szName);               
	// ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	// ofn.nFilterIndex = 0;                        // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; 
	ofn.nMaxFileTitle = 0; 
	// strTileFolder += L"tile";
	
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (TRUE == GetSaveFileName(&ofn))
	{
		std::filesystem::path p(ofn.lpstrFile);
		SaveData(p.filename().string());
	}
}

void EditGUIWindow::SaveData(const std::string& _strTitle)
{
	std::ofstream fout;

	fout.open(_strTitle);

	fout << m_vCreatedActors.size() << '\n';

	for (auto& item : m_vCreatedActors)
	{

		fout << item.first << std::endl
			<< std::setw(7) << item.second->GetTransform().GetLocalScale().x << ' '
			<< std::setw(7) << item.second->GetTransform().GetLocalScale().y << ' '
			<< std::setw(7) << item.second->GetTransform().GetLocalScale().z << ' ' << std::endl
			<< std::setw(7) << item.second->GetTransform().GetLocalRotation().x << ' '
			<< std::setw(7) << item.second->GetTransform().GetLocalRotation().y << ' '
			<< std::setw(7) << item.second->GetTransform().GetLocalRotation().z << ' ' << std::endl
			<< std::setw(7) << item.second->GetTransform().GetLocalPosition().x << ' '
			<< std::setw(7) << item.second->GetTransform().GetLocalPosition().y << ' '
			<< std::setw(7) << item.second->GetTransform().GetLocalPosition().z << ' ' << std::endl
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalScale().x << ' '
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalScale().y << ' '
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalScale().z << ' ' << std::endl
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalRotation().x << ' '
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalRotation().y << ' '
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalRotation().z << ' ' << std::endl
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalPosition().x << ' '
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalPosition().y << ' '
			<< std::setw(7) << item.second->GetCollider()->GetTransform().GetLocalPosition().z << ' ' << std::endl;

	}

	fout.close();
}

void EditGUIWindow::PrepareForLoading()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameEngineWindow::GetHWND();
	wchar_t szName[256] = {};
	std::string strTileFolder(m_ProjectDirectory.GetFullPath());
#ifdef _DEBUG
	ofn.lpstrFile = (LPSTR)szName;               // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.lpstrInitialDir = (LPSTR)(strTileFolder.c_str());
#else
	ofn.lpstrFile = (LPWSTR)szName;               // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.lpstrInitialDir = (LPWSTR)strTileFolder.c_str();
#endif // DEBUG

	ofn.nMaxFile = sizeof(szName);               
	// ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; 
	ofn.nFilterIndex = 0; 
	ofn.lpstrFileTitle = nullptr; 
	ofn.nMaxFileTitle = 0; 
	// strTileFolder += L"tile";

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
		float4 f4ColliderScale, f4ColliderRotation, f4ColliderPosition;
		for (int i = 0; i < uCount; ++i)
		{
			fin >> strName 
				>> f4Scale.x >> f4Scale.y >> f4Scale.z
				>> f4Rotation.x >> f4Rotation.y >> f4Rotation.z
				>> f4Position.x >> f4Position.y >> f4Position.z
				>> f4ColliderScale.x >> f4ColliderScale.y >> f4ColliderScale.z
				>> f4ColliderRotation.x >> f4ColliderRotation.y >> f4ColliderRotation.z
				>> f4ColliderPosition.x >> f4ColliderPosition.y >> f4ColliderPosition.z;

			StaticMesh* temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
			temp->SetPriorityInitialize();
			temp->GetFBXRenderer()->SetFBXMesh(strName + ".fbx", "Texture");
			temp->GetTransform().SetLocalScale(f4Scale);
			temp->GetTransform().SetLocalRotate(f4Rotation);
			temp->GetTransform().SetLocalPosition(f4Position);

			temp->GetCollider()->GetTransform().SetLocalScale(f4ColliderScale);
			temp->GetCollider()->GetTransform().SetLocalRotation(f4ColliderRotation);
			temp->GetCollider()->GetTransform().SetLocalPosition(f4ColliderPosition);
			

			std::pair tempPair(strName, temp);
			m_vCreatedActors.push_back(tempPair);

		}


		// LoadTileData(p.filename().string());
	}
}

void EditGUIWindow::LoadData(const std::string& _strFilePath)
{
	int a = 0;
}

#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"
#include "Player.h"
#include "StaticMesh.h"
#include "ContentsBlur.h"
#include "ContentsBloom.h"
#include "WorldLight.h"

#include <filesystem>
#include <fstream>
#include <iomanip>

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

#pragma region InitializeStaticVariables

size_t EditGUIWindow::uSelectedPannel = AnimatorPannel;
size_t EditGUIWindow::uSelectedObject = 0;
size_t EditGUIWindow::uSelectedActor = 0;

GameEngineDirectory EditGUIWindow::m_ProjectDirectory;
std::set<std::string> EditGUIWindow::m_setLoadedFromAnimator;
std::set<std::string> EditGUIWindow::m_setLoadedFromStatic;
std::map<std::string, std::vector<std::pair<std::string, std::weak_ptr<class StaticMesh>>>> EditGUIWindow::m_vCreatedActors;

float EditGUIWindow::s_farrCurrScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrPrevScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrCurrRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrCurrPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };

float EditGUIWindow::s_farrCurrColliderScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrPrevColliderScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrCurrColliderRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevColliderRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrCurrColliderPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevColliderPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };

float EditGUIWindow::s_farrCurrLightScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrPrevLightScaleOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrCurrLightRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevLightRotationOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrCurrLightPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrPrevLightPositionOnEditGUI[3] = { 0.f, 0.f, 0.f };
float EditGUIWindow::s_farrCurrLightColorOnEditGUI[3] = { 1.f, 1.f, 1.f };
float EditGUIWindow::s_farrPrevLightColorOnEditGUI[3] = { 1.f, 1.f, 1.f };

bool			EditGUIWindow::s_bAnyChanges = false;
bool			EditGUIWindow::s_bOnOffBlur = false;
unsigned int	EditGUIWindow::s_uOnOffBlur = 0u;
int				EditGUIWindow::s_iCurrAppliedArea = 3;
float			EditGUIWindow::s_fCurrIntence = 0.f;

bool			EditGUIWindow::s_bAnyChangesForBloom = false;
bool			EditGUIWindow::s_bOnOffBloom = false;
unsigned int	EditGUIWindow::s_uOnOffBloom = 0u;
int				EditGUIWindow::s_iAppliedAreaForBloom = 1;
float			EditGUIWindow::s_fLuminanceForBloom = 0.3f;
float			EditGUIWindow::s_fIntenceForBloom = 0.f;

bool			EditGUIWindow::s_bAnyChangesForLight = false;
bool			EditGUIWindow::s_bOnOffLight = false;
unsigned int	EditGUIWindow::s_uOnOffLight = 0u;
float			EditGUIWindow::s_fDiffuseLightIntensity = 0.f;
float			EditGUIWindow::s_fAmbientLightIntensity = 0.f;
float			EditGUIWindow::s_fSpecularLightIntensity = 0.f;
float			EditGUIWindow::s_fSpecularLightPower = 1.f;

bool            EditGUIWindow::s_mbStartingLevel = false;

#pragma endregion

EditGUIWindow::EditGUIWindow()
	: mstrCurrLevelName()
	, mstrNextLevelName()
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
	if (true == ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (true == ImGui::BeginTabItem("Contents"))
		{
			mstrNextLevelName = GEngine::GetCurrentLevel()->GetNameCopy();

			if (mstrCurrLevelName != mstrNextLevelName)
			{

				mstrCurrLevelName = mstrNextLevelName;
			}

#pragma region ShowPlayerAndMainCameraInfo
			
			if (nullptr != Player::GetMainPlayer())
			{
				ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Player Information");
				float4 temp = Player::GetMainPlayer()->GetTransform().GetLocalScale();
				float fArr[3] = { temp.x, temp.y, temp.z };
				ImGui::InputFloat3("PlayerScale", fArr);
				temp = Player::GetMainPlayer()->GetTransform().GetLocalRotation();
				fArr[0] = temp.x;
				fArr[1] = temp.y;
				fArr[2] = temp.z;
				ImGui::InputFloat3("PlayerRotation", fArr);
				temp = Player::GetMainPlayer()->GetTransform().GetLocalPosition();
				fArr[0] = temp.x;
				fArr[1] = temp.y;
				fArr[2] = temp.z;
				ImGui::InputFloat3("PlayerPosition", fArr);
			}

			if (nullptr != GEngine::GetCurrentLevel())
			{
				ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "MainCamera World Information");
				float4 temp = GEngine::GetCurrentLevel()->GetMainCamera()->GetTransform().GetWorldRotation();
				float fArr[3] = { temp.x, temp.y, temp.z };
				ImGui::InputFloat3("CameraRotation", fArr);
				temp = GEngine::GetCurrentLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
				fArr[0] = temp.x;
				fArr[1] = temp.y;
				fArr[2] = temp.z;
				ImGui::InputFloat3("CameraPosition", fArr);
			}

#pragma endregion

#pragma region SwitchPannel
			ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Created Object Information");

			if (AnimatorPannel == uSelectedPannel)
			{
				ImGui::BeginChild("Animator", ImVec2(200, 300), true);
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
				ImGui::EndChild();
			}
			else if (StaticPannel == uSelectedPannel)
			{
				ImGui::BeginChild("Static", ImVec2(200, 300), true);

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
				ImGui::EndChild();
			}

			ImGui::SameLine();
#pragma endregion

#pragma region CreaturePannel
			ImGui::BeginChild("Created", ImVec2(200, 300), true);

			if (0 == m_vCreatedActors[mstrCurrLevelName].size())
			{
				if (ImGui::Selectable("Empty...", uSelectedActor == 0))
				{
					uSelectedActor = 0;
				}
			}
			else
			{
				for (int i = 0; i < m_vCreatedActors[mstrCurrLevelName].size(); ++i)
				{
					char label[1024] = { '\0', };
					std::string tempStr = m_vCreatedActors[mstrCurrLevelName][i].first;
					sprintf(label, (tempStr + "-(%d)").c_str(), i);
					if (ImGui::Selectable(label, uSelectedActor == i))
					{
						uSelectedActor = i;
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
#pragma endregion

#pragma region CallbackForButtons
			if (true == ImGui::Button("Animator"))
			{
				uSelectedPannel = AnimatorPannel;
			}
			ImGui::SameLine();

			if (true == ImGui::Button("Static"))
			{
				uSelectedPannel = StaticPannel;
			}
			ImGui::SameLine();

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
				std::weak_ptr<StaticMesh> temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
				temp.lock()->SetPriorityInitialize();
				if ("Collider" != tempStr)
				{
					temp.lock()->GetFBXRenderer()->SetFBXMesh(tempStr + ".fbx", "Texture");
				}

				temp.lock()->GetTransform().SetLocalScale(float4{ s_farrCurrScaleOnEditGUI[0], s_farrCurrScaleOnEditGUI[1], s_farrCurrScaleOnEditGUI[2] , 1.f });
				temp.lock()->GetTransform().SetLocalRotate(float4{ s_farrCurrPositionOnEditGUI[0] , s_farrCurrPositionOnEditGUI[1] , s_farrCurrPositionOnEditGUI[2] });
				temp.lock()->GetTransform().SetLocalPosition(float4{ s_farrCurrRotationOnEditGUI[0], s_farrCurrRotationOnEditGUI[1], s_farrCurrRotationOnEditGUI[2], 1.f });

				temp.lock()->GetCollider()->GetTransform().SetLocalScale(float4{ s_farrCurrColliderScaleOnEditGUI[0],     s_farrCurrColliderScaleOnEditGUI[1],     s_farrCurrColliderScaleOnEditGUI[2] , 1.f });
				temp.lock()->GetCollider()->GetTransform().SetLocalRotate(float4{ s_farrCurrColliderPositionOnEditGUI[0] , s_farrCurrColliderPositionOnEditGUI[1] , s_farrCurrColliderPositionOnEditGUI[2] });
				temp.lock()->GetCollider()->GetTransform().SetLocalPosition(float4{ s_farrCurrColliderRotationOnEditGUI[0],  s_farrCurrColliderRotationOnEditGUI[1],  s_farrCurrColliderRotationOnEditGUI[2], 1.f });


				std::pair tempPair(tempStr, temp);
				m_vCreatedActors[mstrCurrLevelName].push_back(tempPair);

			}

			ImGui::SameLine();

			if (true == ImGui::Button("Delete"))
			{
				auto iterBeg = m_vCreatedActors[mstrCurrLevelName].begin();
				auto iterEnd = m_vCreatedActors[mstrCurrLevelName].end();
				for (size_t i = 0; iterBeg != iterEnd; ++i)
				{
					if (uSelectedActor == i)
					{
						m_vCreatedActors[mstrCurrLevelName][i].second.lock()->Death();
						m_vCreatedActors[mstrCurrLevelName].erase(iterBeg);
						uSelectedActor = 99999999 <= (uSelectedActor - 1u) ? 0 : uSelectedActor - 1u;
						// m_vCreatedActors[mstrCurrLevelName][i] = std::make_pair<std::string, StaticMesh*>("NULL", nullptr);
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
			if (0 != m_vCreatedActors[mstrCurrLevelName].size())
			{
				if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectUp"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalMove(float4::UP * 400.f * _DeltaTime);
				}

				if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectDown"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalMove(float4::DOWN * 400.f * _DeltaTime);
				}

				if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectLeft"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalMove(float4::LEFT * 400.f * _DeltaTime);
				}

				if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectRight"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalMove(float4::RIGHT * 400.f * _DeltaTime);
				}

				if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectForward"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalMove(float4::FORWARD * 400.f * _DeltaTime);
				}

				if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectBackward"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalMove(float4::BACK * 400.f * _DeltaTime);
				}
			}
#pragma endregion

#pragma region SelectedObjectRotation
			if (0 != m_vCreatedActors[mstrCurrLevelName].size())
			{
				if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectUp"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotate(float4::UP * 400.f * _DeltaTime);
				}

				if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectDown"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotate(float4::DOWN * 400.f * _DeltaTime);
				}

				if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectLeft"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotate(float4::LEFT * 400.f * _DeltaTime);
				}

				if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectRight"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotate(float4::RIGHT * 400.f * _DeltaTime);
				}

				if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectForward"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotate(float4::FORWARD * 400.f * _DeltaTime);
				}

				if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("SelectedObjectBackward"))
				{
					m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotate(float4::BACK * 400.f * _DeltaTime);
				}
			}
#pragma endregion

#pragma region SynchronizeStaticValue
			// curr 값 변경 -> prev 값 체크 -> 엑터 값 업데이트
			// 엑터값 변경(화살표) -> prev 값과 체크 -> curr 값 변경

			if (0u != m_vCreatedActors[mstrCurrLevelName].size() && true == CheckChangesAboutCurrStaticValue(uSelectedActor))
			{
				m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalScale(float4{ s_farrCurrScaleOnEditGUI[0], s_farrCurrScaleOnEditGUI[1], s_farrCurrScaleOnEditGUI[2] });
				m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalRotation(float4{ s_farrCurrRotationOnEditGUI[0], s_farrCurrRotationOnEditGUI[1], s_farrCurrRotationOnEditGUI[2] });
				m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().SetLocalPosition(float4{ s_farrCurrPositionOnEditGUI[0], s_farrCurrPositionOnEditGUI[1], s_farrCurrPositionOnEditGUI[2] });
			}

			if (0 != m_vCreatedActors[mstrCurrLevelName].size() && nullptr != m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()
				&& true == CheckChangesAboutCreature(uSelectedActor))
			{
				for (int i = 0; i < 3; ++i)
				{
					s_farrCurrScaleOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().GetLocalScale().Arr1D[i];
					s_farrCurrRotationOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().GetLocalRotation().Arr1D[i];
					s_farrCurrPositionOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetTransform().GetLocalPosition().Arr1D[i];
				}
			}
#pragma endregion

#pragma region SynchronizeStaticValueForCollider
			if (0u != m_vCreatedActors[mstrCurrLevelName].size() && true == CheckChangesAboutCurrStaticValueCollider(uSelectedActor))
			{
				m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetCollider()->GetTransform().SetLocalScale(float4{ s_farrCurrColliderScaleOnEditGUI[0], s_farrCurrColliderScaleOnEditGUI[1], s_farrCurrColliderScaleOnEditGUI[2] });
				m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetCollider()->GetTransform().SetLocalRotation(float4{ s_farrCurrColliderRotationOnEditGUI[0], s_farrCurrColliderRotationOnEditGUI[1], s_farrCurrColliderRotationOnEditGUI[2] });
				m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetCollider()->GetTransform().SetLocalPosition(float4{ s_farrCurrColliderPositionOnEditGUI[0], s_farrCurrColliderPositionOnEditGUI[1], s_farrCurrColliderPositionOnEditGUI[2] });
			}

			if (0 != m_vCreatedActors[mstrCurrLevelName].size() && nullptr != m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()
				&& true == CheckChangesAboutCreatureCollider(uSelectedActor))
			{
				for (int i = 0; i < 3; ++i)
				{
					s_farrCurrColliderScaleOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalScale().Arr1D[i];
					s_farrCurrColliderRotationOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalRotation().Arr1D[i];
					s_farrCurrColliderPositionOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalPosition().Arr1D[i];
				}
			}
#pragma endregion

			ImGui::EndTabItem();
		}

		if (false == s_mbStartingLevel)
		{
			ContentsLevel* rptrContentsLevel = dynamic_cast<ContentsLevel*>(GEngine::GetCurrentLevel());
			rptrContentsLevel->GetContentsBlur()->SetBlurInfo(s_uOnOffBlur, s_iCurrAppliedArea, s_fCurrIntence);
			rptrContentsLevel->GetContentsBloom()->SetBloomInfo(s_uOnOffBloom, s_iAppliedAreaForBloom, s_fLuminanceForBloom, s_fIntenceForBloom);
			rptrContentsLevel->SetLightData(s_uOnOffLight, s_fDiffuseLightIntensity, s_fAmbientLightIntensity, s_fSpecularLightIntensity, s_fSpecularLightPower);

			s_mbStartingLevel = true;
		}

		if (true == ImGui::BeginTabItem("Post Process Effects"))
		{

#pragma region Blur

			{
				ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Blur");
				ImGui::BeginChild("##colors1", ImVec2(400, 100), true, ImGuiWindowFlags_NavFlattened);

				s_bAnyChanges |= ImGui::Checkbox("On/Off blur", &s_bOnOffBlur);
				s_uOnOffBlur = true == s_bOnOffBlur ? 1u : 0u;

				s_bAnyChanges |= ImGui::InputInt("Applied area for blur", &s_iCurrAppliedArea, 2);

				if (s_iCurrAppliedArea < 3) { s_iCurrAppliedArea = 3; }
				if (7 < s_iCurrAppliedArea) { s_iCurrAppliedArea = 7; }

				s_bAnyChanges |= ImGui::InputFloat("Intence", &s_fCurrIntence, 1.f);

				if (s_fCurrIntence < 0) { s_fCurrIntence = 0; }
				if (3 == s_iCurrAppliedArea && 15.f < s_fCurrIntence) { s_fCurrIntence = 15.f; }
				if (5 == s_iCurrAppliedArea && 272.f < s_fCurrIntence) { s_fCurrIntence = 272.f; }
				if (7 == s_iCurrAppliedArea && 1000.f < s_fCurrIntence) { s_fCurrIntence = 1000.f; }

				if (true == s_bAnyChanges)
				{
					ContentsLevel* rptrContentsLevel = dynamic_cast<ContentsLevel*>(GEngine::GetCurrentLevel());
					rptrContentsLevel->GetContentsBlur()->SetBlurInfo(s_uOnOffBlur, s_iCurrAppliedArea, s_fCurrIntence);
				}

				s_bAnyChanges = false;

				ImGui::EndChild();
			}

#pragma endregion

#pragma region Bloom

			{

				ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Bloom");
				ImGui::BeginChild("##colors2", ImVec2(400, 130), true, ImGuiWindowFlags_NavFlattened);

				s_bAnyChangesForBloom |= ImGui::Checkbox("On/Off Bloom", &s_bOnOffBloom);
				s_uOnOffBloom = true == s_bOnOffBloom ? 1u : 0u;

				s_bAnyChangesForBloom |= ImGui::InputInt("Applied area for bloom", &s_iAppliedAreaForBloom);

				if (s_iAppliedAreaForBloom < 3) { s_iAppliedAreaForBloom = 3; }

				s_bAnyChangesForBloom |= ImGui::InputFloat("Luminance", &s_fLuminanceForBloom, 0.01f);

				if (s_fLuminanceForBloom < 0.f) { s_fLuminanceForBloom = 0.f; }
				if (1.f <= s_fLuminanceForBloom) { s_fLuminanceForBloom = 1.f; }

				s_bAnyChangesForBloom |= ImGui::InputFloat("Intence", &s_fIntenceForBloom, 1.f);

				if (s_fIntenceForBloom < 0.f) { s_fIntenceForBloom = 0.f; }
				if (static_cast<float>(s_iAppliedAreaForBloom) < s_fIntenceForBloom) { s_fIntenceForBloom = static_cast<float>(s_iAppliedAreaForBloom); }

				if (true == s_bAnyChangesForBloom)
				{
					ContentsLevel* rptrContentsLevel = dynamic_cast<ContentsLevel*>(GEngine::GetCurrentLevel());
					rptrContentsLevel->GetContentsBloom()->SetBloomInfo(s_uOnOffBloom, s_iAppliedAreaForBloom, s_fLuminanceForBloom, s_fIntenceForBloom);
				}

				s_bAnyChangesForBloom = false;

				ImGui::EndChild();
			}

#pragma endregion


			if (true == ImGui::Button("Save the info"))
			{
				SavePostEffectInfo();
			}
			

			ImGui::EndTabItem();
		}

		if (true == ImGui::BeginTabItem("Light"))
		{
			ContentsLevel* rptrContentsLevel = dynamic_cast<ContentsLevel*>(GEngine::GetCurrentLevel());

			if (nullptr != WorldLight::GetWorldLight())
			{
				ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Light Information");

				ImGui::InputFloat3("Light Scale", s_farrCurrLightScaleOnEditGUI);
				ImGui::InputFloat3("Light Rotation", s_farrCurrLightRotationOnEditGUI);
				ImGui::InputFloat3("Light Position", s_farrCurrLightPositionOnEditGUI);
				ImGui::InputFloat3("Light Color", s_farrCurrLightColorOnEditGUI);

				// 칸에 값 바꿈 curr - 칸 값과 이전값 바뀌었는지 체크 하고 이전값에 칸값 대입 - 원래 물체의 값도 갱신 

				if (true == CheckChangesAboutCurrLightStaticValue())
				{
					WorldLight::GetWorldLight()->GetTransform().SetLocalScale(float4{ s_farrCurrLightScaleOnEditGUI[0], s_farrCurrLightScaleOnEditGUI[1],      s_farrCurrLightScaleOnEditGUI[2] });
					WorldLight::GetWorldLight()->GetTransform().SetLocalRotation(float4{ s_farrCurrLightRotationOnEditGUI[0], s_farrCurrLightRotationOnEditGUI[1],   s_farrCurrLightRotationOnEditGUI[2] });
					WorldLight::GetWorldLight()->GetTransform().SetLocalPosition(float4{ s_farrCurrLightPositionOnEditGUI[0], s_farrCurrLightPositionOnEditGUI[1],   s_farrCurrLightPositionOnEditGUI[2] });
					WorldLight::SetWorldLightColor(float4{                               s_farrCurrLightColorOnEditGUI[0], s_farrCurrLightColorOnEditGUI[1], s_farrCurrLightColorOnEditGUI[2] });
				}

				// 원래 물체의 값 변경 - 원래물체값 바뀌었는지 체크 하고 이전값에 물체값 대입 - 물체값을 칸값에 대입

				if (true == CheckChangesAboutLight())
				{
					for (int i = 0; i < 3; ++i)
					{
						s_farrCurrLightScaleOnEditGUI[i] =    WorldLight::GetWorldLight()->GetTransform().GetLocalScale().Arr1D[i];
						s_farrCurrLightRotationOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalRotation().Arr1D[i];
						s_farrCurrLightPositionOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalPosition().Arr1D[i];
						s_farrCurrLightColorOnEditGUI[i] =    WorldLight::GetWorldLightColor().Arr1D[i];
					}
				}

			}

			ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Light");
			ImGui::BeginChild("##colors4", ImVec2(400, 160), true, ImGuiWindowFlags_NavFlattened);

			s_bAnyChangesForBloom |= ImGui::Checkbox("On/Off Light", &s_bOnOffLight);
			s_uOnOffLight = true == s_bOnOffLight ? 1u : 0u;

			s_bAnyChangesForBloom |= ImGui::InputFloat("Diffuse", &s_fDiffuseLightIntensity, 1.f);

			s_bAnyChangesForBloom |= ImGui::InputFloat("Ambient", &s_fAmbientLightIntensity, 1.f);

			s_bAnyChangesForBloom |= ImGui::InputFloat("Specular", &s_fSpecularLightIntensity, 1.f);

			s_bAnyChangesForBloom |= ImGui::InputFloat("Specular Power", &s_fSpecularLightPower, 1.f);

			if (s_fDiffuseLightIntensity < 0.f) { s_fDiffuseLightIntensity = 0.f; }
			if (s_fAmbientLightIntensity < 0.f) { s_fAmbientLightIntensity = 0.f; }
			if (s_fSpecularLightIntensity < 0.f) { s_fSpecularLightIntensity = 0.f; }
			if (s_fSpecularLightPower < 0.f) { s_fSpecularLightPower = 0.f; }

			if (true == s_bAnyChangesForBloom)
			{
				ContentsLevel* rptrContentsLevel = dynamic_cast<ContentsLevel*>(GEngine::GetCurrentLevel());
				rptrContentsLevel->SetLightData(s_uOnOffLight, s_fDiffuseLightIntensity, s_fAmbientLightIntensity, s_fSpecularLightIntensity, s_fSpecularLightPower);
			}

			s_bAnyChangesForBloom = false;

			ImGui::EndChild();

			if (true == ImGui::Button("Save the light data"))
			{
				SaveLightData();
			}

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

bool EditGUIWindow::CheckChangesAboutCreature(size_t _uSelectedActor)
{
	if (m_vCreatedActors[mstrCurrLevelName].size() <= _uSelectedActor)
	{
		return false;
	}

	if (
		s_farrPrevScaleOnEditGUI[0] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalScale().x ||
		s_farrPrevScaleOnEditGUI[1] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalScale().y ||
		s_farrPrevScaleOnEditGUI[2] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalScale().z ||

		s_farrPrevRotationOnEditGUI[0] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalRotation().x ||
		s_farrPrevRotationOnEditGUI[1] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalRotation().y ||
		s_farrPrevRotationOnEditGUI[2] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalRotation().z ||

		s_farrPrevPositionOnEditGUI[0] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalPosition().x ||
		s_farrPrevPositionOnEditGUI[1] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalPosition().y ||
		s_farrPrevPositionOnEditGUI[2] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalPosition().z
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevScaleOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalScale().Arr1D[i];
			s_farrPrevRotationOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalRotation().Arr1D[i];
			s_farrPrevPositionOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetTransform().GetLocalPosition().Arr1D[i];
		}

		return true;
	}

	return false;
}

bool EditGUIWindow::CheckChangesAboutCurrStaticValue(size_t _uSelectedActor)
{
	if (m_vCreatedActors[mstrCurrLevelName].size() <= _uSelectedActor)
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
			s_farrPrevScaleOnEditGUI[i] = s_farrCurrScaleOnEditGUI[i];
			s_farrPrevRotationOnEditGUI[i] = s_farrCurrScaleOnEditGUI[i];
			s_farrPrevPositionOnEditGUI[i] = s_farrCurrScaleOnEditGUI[i];
		}

		return true;
	}

	return false;
}

bool EditGUIWindow::CheckChangesAboutCreatureCollider(size_t _uSelectedActor)
{
	if (m_vCreatedActors[mstrCurrLevelName].size() <= _uSelectedActor)
	{
		return false;
	}

	if (
		s_farrPrevColliderScaleOnEditGUI[0] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalScale().x ||
		s_farrPrevColliderScaleOnEditGUI[1] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalScale().y ||
		s_farrPrevColliderScaleOnEditGUI[2] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalScale().z ||

		s_farrPrevColliderRotationOnEditGUI[0] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalRotation().x ||
		s_farrPrevColliderRotationOnEditGUI[1] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalRotation().y ||
		s_farrPrevColliderRotationOnEditGUI[2] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalRotation().z ||

		s_farrPrevColliderPositionOnEditGUI[0] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalPosition().x ||
		s_farrPrevColliderPositionOnEditGUI[1] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalPosition().y ||
		s_farrPrevColliderPositionOnEditGUI[2] != m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalPosition().z
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevColliderScaleOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalScale().Arr1D[i];
			s_farrPrevColliderRotationOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalRotation().Arr1D[i];
			s_farrPrevColliderPositionOnEditGUI[i] = m_vCreatedActors[mstrCurrLevelName][_uSelectedActor].second.lock()->GetCollider()->GetTransform().GetLocalPosition().Arr1D[i];
		}

		return true;
	}

	return false;
}

bool EditGUIWindow::CheckChangesAboutCurrStaticValueCollider(size_t _uSelectedActor)
{
	if (m_vCreatedActors[mstrCurrLevelName].size() <= _uSelectedActor)
	{
		return false;
	}

	if (
		s_farrPrevColliderScaleOnEditGUI[0] != s_farrCurrColliderScaleOnEditGUI[0] ||
		s_farrPrevColliderScaleOnEditGUI[1] != s_farrCurrColliderScaleOnEditGUI[1] ||
		s_farrPrevColliderScaleOnEditGUI[2] != s_farrCurrColliderScaleOnEditGUI[2] ||

		s_farrPrevColliderRotationOnEditGUI[0] != s_farrCurrColliderRotationOnEditGUI[0] ||
		s_farrPrevColliderRotationOnEditGUI[1] != s_farrCurrColliderRotationOnEditGUI[1] ||
		s_farrPrevColliderRotationOnEditGUI[2] != s_farrCurrColliderRotationOnEditGUI[2] ||

		s_farrPrevColliderPositionOnEditGUI[0] != s_farrCurrColliderPositionOnEditGUI[0] ||
		s_farrPrevColliderPositionOnEditGUI[1] != s_farrCurrColliderPositionOnEditGUI[1] ||
		s_farrPrevColliderPositionOnEditGUI[2] != s_farrCurrColliderPositionOnEditGUI[2]
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevColliderScaleOnEditGUI[i] = s_farrCurrColliderScaleOnEditGUI[i];
			s_farrPrevColliderRotationOnEditGUI[i] = s_farrCurrColliderScaleOnEditGUI[i];
			s_farrPrevColliderPositionOnEditGUI[i] = s_farrCurrColliderScaleOnEditGUI[i];
		}

		return true;
	}

	return false;
	}

bool EditGUIWindow::CheckChangesAboutLight()
{
	if (
		s_farrPrevLightScaleOnEditGUI[0] != WorldLight::GetWorldLight()->GetTransform().GetLocalScale().x ||
		s_farrPrevLightScaleOnEditGUI[1] != WorldLight::GetWorldLight()->GetTransform().GetLocalScale().y ||
		s_farrPrevLightScaleOnEditGUI[2] != WorldLight::GetWorldLight()->GetTransform().GetLocalScale().z ||
		s_farrPrevLightRotationOnEditGUI[0] != WorldLight::GetWorldLight()->GetTransform().GetLocalRotation().x ||
		s_farrPrevLightRotationOnEditGUI[1] != WorldLight::GetWorldLight()->GetTransform().GetLocalRotation().y ||
		s_farrPrevLightRotationOnEditGUI[2] != WorldLight::GetWorldLight()->GetTransform().GetLocalRotation().z ||
		s_farrPrevLightPositionOnEditGUI[0] != WorldLight::GetWorldLight()->GetTransform().GetLocalPosition().x ||
		s_farrPrevLightPositionOnEditGUI[1] != WorldLight::GetWorldLight()->GetTransform().GetLocalPosition().y ||
		s_farrPrevLightPositionOnEditGUI[2] != WorldLight::GetWorldLight()->GetTransform().GetLocalPosition().z ||
		s_farrPrevLightColorOnEditGUI[0] != WorldLight::GetWorldLightColor().r ||
		s_farrPrevLightColorOnEditGUI[1] != WorldLight::GetWorldLightColor().g ||
		s_farrPrevLightColorOnEditGUI[2] != WorldLight::GetWorldLightColor().b
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevLightScaleOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalScale().Arr1D[i];
			s_farrPrevLightRotationOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalRotation().Arr1D[i];
			s_farrPrevLightPositionOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalPosition().Arr1D[i];
			s_farrPrevLightColorOnEditGUI[i] = WorldLight::GetWorldLightColor().Arr1D[i];
		}

		return true;
	}

	return false;

	
}

bool EditGUIWindow::CheckChangesAboutCurrLightStaticValue()
{
	if (
		s_farrPrevLightScaleOnEditGUI[0] != s_farrCurrLightScaleOnEditGUI[0] ||
		s_farrPrevLightScaleOnEditGUI[1] != s_farrCurrLightScaleOnEditGUI[1] ||
		s_farrPrevLightScaleOnEditGUI[2] != s_farrCurrLightScaleOnEditGUI[2] ||

		s_farrPrevLightRotationOnEditGUI[0] != s_farrCurrLightRotationOnEditGUI[0] ||
		s_farrPrevLightRotationOnEditGUI[1] != s_farrCurrLightRotationOnEditGUI[1] ||
		s_farrPrevLightRotationOnEditGUI[2] != s_farrCurrLightRotationOnEditGUI[2] ||

		s_farrPrevLightPositionOnEditGUI[0] != s_farrCurrLightPositionOnEditGUI[0] ||
		s_farrPrevLightPositionOnEditGUI[1] != s_farrCurrLightPositionOnEditGUI[1] ||
		s_farrPrevLightPositionOnEditGUI[2] != s_farrCurrLightPositionOnEditGUI[2] ||

		s_farrPrevLightColorOnEditGUI[0] != s_farrCurrLightColorOnEditGUI[0] ||
		s_farrPrevLightColorOnEditGUI[1] != s_farrCurrLightColorOnEditGUI[1] ||
		s_farrPrevLightColorOnEditGUI[2] != s_farrCurrLightColorOnEditGUI[2]
		)
	{
		for (int i = 0; i < 3; ++i)
		{
			s_farrPrevLightScaleOnEditGUI[i] = s_farrCurrLightScaleOnEditGUI[i];
			s_farrPrevLightRotationOnEditGUI[i] = s_farrCurrLightRotationOnEditGUI[i];
			s_farrPrevLightPositionOnEditGUI[i] = s_farrCurrLightPositionOnEditGUI[i];
			s_farrPrevLightColorOnEditGUI[i] = s_farrCurrLightColorOnEditGUI[i];
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

	fout << m_vCreatedActors[mstrCurrLevelName].size() << '\n';

	for (auto& item : m_vCreatedActors[mstrCurrLevelName])
	{

		fout << item.first << std::endl
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalScale().x << ' '
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalScale().y << ' '
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalScale().z << ' ' << std::endl
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalRotation().x << ' '
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalRotation().y << ' '
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalRotation().z << ' ' << std::endl
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalPosition().x << ' '
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalPosition().y << ' '
			<< std::setw(7) << item.second.lock()->GetTransform().GetLocalPosition().z << ' ' << std::endl
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalScale().x << ' '
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalScale().y << ' '
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalScale().z << ' ' << std::endl
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalRotation().x << ' '
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalRotation().y << ' '
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalRotation().z << ' ' << std::endl
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalPosition().x << ' '
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalPosition().y << ' '
			<< std::setw(7) << item.second.lock()->GetCollider()->GetTransform().GetLocalPosition().z << ' ' << std::endl;
	}

	fout.close();
}

void EditGUIWindow::SavePostEffectInfo()
{
	std::ofstream fout;

	fout.open(m_ProjectDirectory.GetFullPath() + "/PostEffectInfo.txt", 'w');

	fout << s_uOnOffBlur << ' '
		<< s_iCurrAppliedArea << ' '
		<< s_fCurrIntence << ' '
		<< s_uOnOffBloom << ' '
		<< s_iAppliedAreaForBloom << ' '
		<< s_fLuminanceForBloom << ' '
		<< s_fIntenceForBloom << std::endl;

	fout.close();
}

void EditGUIWindow::LoadPostEffectInfo()
{
	std::ifstream fin;

	fin.open(m_ProjectDirectory.GetFullPath() + "\\PostEffectInfo.txt");

	fin >> s_uOnOffBlur
		>> s_iCurrAppliedArea
		>> s_fCurrIntence
		>> s_uOnOffBloom
		>> s_iAppliedAreaForBloom
		>> s_fLuminanceForBloom
		>> s_fIntenceForBloom;

	s_bOnOffBlur = s_uOnOffBlur == 1u ? true : false;
	s_bOnOffBloom = s_uOnOffBloom == 1u ? true : false;

	fin.close();
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

			std::shared_ptr<StaticMesh> temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
			temp->SetPriorityInitialize();
			temp->GetFBXRenderer()->SetFBXMesh(strName + ".fbx", "Texture");
			temp->GetTransform().SetLocalScale(f4Scale);
			temp->GetTransform().SetLocalRotate(f4Rotation);
			temp->GetTransform().SetLocalPosition(f4Position);

			temp->GetCollider()->GetTransform().SetLocalScale(f4ColliderScale);
			temp->GetCollider()->GetTransform().SetLocalRotation(f4ColliderRotation);
			temp->GetCollider()->GetTransform().SetLocalPosition(f4ColliderPosition);


			std::pair tempPair(strName, temp);
			m_vCreatedActors[mstrCurrLevelName].push_back(tempPair);

		}

		fin.close();
		// LoadTileData(p.filename().string());
	}
}

void EditGUIWindow::LoadData(const std::string& _strFilePath)
{
	int a = 0;
}

void EditGUIWindow::SaveLightData()
{
	std::ofstream fout;

	fout.open(m_ProjectDirectory.GetFullPath() + "/LightData.txt", 'w');

	fout << s_uOnOffLight << ' '
		<< s_fDiffuseLightIntensity << ' '
		<< s_fAmbientLightIntensity << ' '
		<< s_fSpecularLightIntensity << ' '
		<< s_fSpecularLightPower << ' '
		
		<< s_farrCurrLightScaleOnEditGUI[0] << ' '
		<< s_farrCurrLightScaleOnEditGUI[1] << ' '
		<< s_farrCurrLightScaleOnEditGUI[2] << ' '
		
		<< s_farrCurrLightRotationOnEditGUI[0] << ' '
		<< s_farrCurrLightRotationOnEditGUI[1] << ' '
		<< s_farrCurrLightRotationOnEditGUI[2] << ' '

		<< s_farrCurrLightPositionOnEditGUI[0] << ' '
		<< s_farrCurrLightPositionOnEditGUI[1] << ' '
		<< s_farrCurrLightPositionOnEditGUI[2] << ' '

		<< s_farrCurrLightColorOnEditGUI[0] << ' '
		<< s_farrCurrLightColorOnEditGUI[1] << ' '
		<< s_farrCurrLightColorOnEditGUI[2] << ' '
		
		<< std::endl;

	fout.close();
}

void EditGUIWindow::LoadLightData()
{
	std::ifstream fin;

	fin.open(m_ProjectDirectory.GetFullPath() + "/LightData.txt");

	fin >> s_uOnOffLight
		>> s_fDiffuseLightIntensity
		>> s_fAmbientLightIntensity
		>> s_fSpecularLightIntensity
		>> s_fSpecularLightPower
		>> s_farrCurrLightScaleOnEditGUI[0]
		>> s_farrCurrLightScaleOnEditGUI[1]
		>> s_farrCurrLightScaleOnEditGUI[2]
		>> s_farrCurrLightRotationOnEditGUI[0]
		>> s_farrCurrLightRotationOnEditGUI[1]
		>> s_farrCurrLightRotationOnEditGUI[2]
		>> s_farrCurrLightPositionOnEditGUI[0]
		>> s_farrCurrLightPositionOnEditGUI[1]
		>> s_farrCurrLightPositionOnEditGUI[2]
		>> s_farrCurrLightColorOnEditGUI[0]
		>> s_farrCurrLightColorOnEditGUI[1]
		>> s_farrCurrLightColorOnEditGUI[2];

	s_bOnOffLight = 1u == s_uOnOffLight ? true : false;

	// WorldLight::GetWorldLight()->GetTransform().SetLocalScale(float4{ s_farrCurrLightScaleOnEditGUI[0], s_farrCurrLightScaleOnEditGUI[1],      s_farrCurrLightScaleOnEditGUI[2] });
	// WorldLight::GetWorldLight()->GetTransform().SetLocalRotation(float4{ s_farrCurrLightRotationOnEditGUI[0], s_farrCurrLightRotationOnEditGUI[1],   s_farrCurrLightRotationOnEditGUI[2] });
	// WorldLight::GetWorldLight()->GetTransform().SetLocalPosition(float4{ s_farrCurrLightPositionOnEditGUI[0], s_farrCurrLightPositionOnEditGUI[1],   s_farrCurrLightPositionOnEditGUI[2] });
	// WorldLight::SetWorldLightColor(float4{ s_farrCurrLightColorOnEditGUI[0], s_farrCurrLightColorOnEditGUI[1], s_farrCurrLightColorOnEditGUI[2] });
	// 
	// for (int i = 0; i < 3; ++i)
	// {
	// 	s_farrCurrLightScaleOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalScale().Arr1D[i];
	// 	s_farrCurrLightRotationOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalRotation().Arr1D[i];
	// 	s_farrCurrLightPositionOnEditGUI[i] = WorldLight::GetWorldLight()->GetTransform().GetLocalPosition().Arr1D[i];
	// 	s_farrCurrLightColorOnEditGUI[i] = WorldLight::GetWorldLightColor().Arr1D[i];
	// }
	// 

	fin.close();
}

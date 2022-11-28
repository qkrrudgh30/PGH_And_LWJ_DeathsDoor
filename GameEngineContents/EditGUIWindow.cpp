#include "PreCompile.h"
#include "EditGUIWindow.h"
#include "EditLevel.h"
#include "TestActor.h"
#include "Player.h"
#include "StaticMesh.h"
#include "ContentsBlur.h"

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

		if (true == ImGui::BeginTabItem("Post Process Effects"))
		{
			//GEngine::GetCurrentLevel()->GetBlurCamera()->;
			{
				ImGui::TextColored(ImVec4{ 1.f, 0.f, 0.f, 1.f }, "Blur");
				ImGui::BeginChild("##colors", ImVec2(400, 100), true, ImGuiWindowFlags_NavFlattened);

#pragma region ShowRendertarget

				/*if (true == ImGui::TreeNodeEx("Blur Camera Render Target"))
				{
					std::shared_ptr<GameEngineRenderTarget> RenderTarget = GEngine::GetCurrentLevel()->GetBlurCamera()->GetCameraRenderTarget();

					float4 f4Scale = GameEngineWindow::GetScale() * 0.2f;
					ID3D11ShaderResourceView* rptrShaderResourceView = RenderTarget->ShaderResourceViews[1];

					if (true == ImGui::ImageButton(static_cast<ImTextureID>(rptrShaderResourceView), { f4Scale.x, f4Scale.y }))
					{
						std::shared_ptr<GameEngineImageShotWindow> NewWindow = GameEngineGUI::CreateGUIWindow<GameEngineImageShotWindow>("ImageShot", nullptr);
						NewWindow->RenderTextureSetting(static_cast<ImTextureID>(rptrShaderResourceView), { GameEngineWindow::GetScale().x ,GameEngineWindow::GetScale().y });
					}

					ImGui::TreePop();
				}*/

#pragma endregion

				static bool s_bAnyChanges = false;

				//static bool s_bVertical = false;
				//static bool s_bHorizontal = false;
				static bool s_bOnOffBlur = false;
				static unsigned int s_uOnOff = 0;
				//static int s_iCurrBlurType = 0;
				//s_bAnyChanges |= ImGui::Checkbox("Vertical", &s_bVertical);
				//s_bAnyChanges |= ImGui::Checkbox("Horizontal", &s_bHorizontal);
				s_bAnyChanges |= ImGui::Checkbox("On/Off blur", &s_bOnOffBlur);
				s_uOnOff = true == s_bOnOffBlur ? 1u : 0u;

				//if (false == s_bVertical && false == s_bHorizontal) { s_iCurrBlurType = 0; }
				//else if (true == s_bVertical && false == s_bHorizontal) { s_iCurrBlurType = 1; }
				//else if (false == s_bVertical && true == s_bHorizontal) { s_iCurrBlurType = 2; }
				//else if (true == s_bVertical && true == s_bHorizontal) { s_iCurrBlurType = 3; }

				static int s_iCurrAppliedArea = 3;
				s_bAnyChanges |= ImGui::InputInt("Applied area", &s_iCurrAppliedArea, 2);

				if (s_iCurrAppliedArea < 3) { s_iCurrAppliedArea = 3; }
				if (7 < s_iCurrAppliedArea) { s_iCurrAppliedArea = 7; }

				static float s_fCurrIntence = 0.f;
				s_bAnyChanges |= ImGui::InputFloat("Intence", &s_fCurrIntence, 1.f);

				if (s_fCurrIntence < 0) { s_fCurrIntence = 0; }
				if (3 == s_iCurrAppliedArea && 15.f < s_fCurrIntence) { s_fCurrIntence = 15.f; }
				if (5 == s_iCurrAppliedArea && 272.f < s_fCurrIntence) { s_fCurrIntence = 272.f; }
				if (7 == s_iCurrAppliedArea && 1000.f < s_fCurrIntence) { s_fCurrIntence = 1000.f; }

				if (true == s_bAnyChanges)
				{
					ContentsBlur::SetBlurInfo(s_uOnOff, s_iCurrAppliedArea, s_fCurrIntence);
				}

				s_bAnyChanges = false;

				ImGui::EndChild();
			}

			{

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

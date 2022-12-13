#include "PreCompile.h"
#include "WorldLight.h"
#include "EditGUIWindow.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

WorldLight* WorldLight::s_rptrWorldLight = nullptr;
float4 WorldLight::s_f4LightColor = float4{ 0.f, 0.f, 0.f, 0.f };

WorldLight::WorldLight() 
{
	s_rptrWorldLight = this;
}

WorldLight::~WorldLight() 
{
}

void WorldLight::Start()
{
	FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
	FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 1.f, 1.f, 1.f });
	FBXStaticRenderer->GetTransform().SetLocalRotation(float4{ 0.f, 0.f, 0.f });
	FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
	FBXStaticRenderer->SetFBXMesh("Light.fbx", "PreviousColor");

	s_f4LightColor = float4{ 1.f, 0.f, 0.f, 1.f }; 
	FBXStaticRenderer->GetAllRenderUnit()[0][0].ShaderResources.SetConstantBufferLink("ResultColor", s_f4LightColor);

	if (false == GameEngineInput::GetInst()->IsKey("LightF"))
	{
		GameEngineInput::GetInst()->CreateKey("LightF", VK_HOME);
		GameEngineInput::GetInst()->CreateKey("LightB", VK_END);
		GameEngineInput::GetInst()->CreateKey("LightL", VK_DELETE);
		GameEngineInput::GetInst()->CreateKey("LightR", VK_NEXT);
		GameEngineInput::GetInst()->CreateKey("LightU", VK_INSERT);
		GameEngineInput::GetInst()->CreateKey("LightD", VK_PRIOR);
	}
}

void WorldLight::Update(float _fDeltatime)
{
	if (false == EditGUIWindow::IsLightOn()) { FBXStaticRenderer->Off(); }
	else { FBXStaticRenderer->On(); }

#pragma region SelectedObjectMovement
		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightU"))
		{
			GetTransform().SetLocalMove(float4::UP * 100.f * _fDeltatime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightD"))
		{
			GetTransform().SetLocalMove(float4::DOWN * 100.f * _fDeltatime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightL"))
		{
			GetTransform().SetLocalMove(float4::LEFT * 100.f * _fDeltatime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightR"))
		{
			GetTransform().SetLocalMove(float4::RIGHT * 100.f * _fDeltatime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightF"))
		{
			GetTransform().SetLocalMove(float4::FORWARD * 100.f * _fDeltatime);
		}

		if (false == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightB"))
		{
			GetTransform().SetLocalMove(float4::BACK * 100.f * _fDeltatime);
		}
#pragma endregion

#pragma region SelectedObjectRotation
		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightU"))
		{
			GetTransform().SetLocalRotate(float4::UP * 100.f * _fDeltatime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightD"))
		{
			GetTransform().SetLocalRotate(float4::DOWN * 100.f * _fDeltatime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightL"))
		{
			GetTransform().SetLocalRotate(float4::LEFT * 100.f * _fDeltatime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightR"))
		{
			GetTransform().SetLocalRotate(float4::RIGHT * 100.f * _fDeltatime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightF"))
		{
			GetTransform().SetLocalRotate(float4::FORWARD * 100.f * _fDeltatime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("SelectedObjectRotate") && true == GameEngineInput::GetInst()->IsPress("LightB"))
		{
			GetTransform().SetLocalRotate(float4::BACK * 100.f * _fDeltatime);
		}
#pragma endregion

}


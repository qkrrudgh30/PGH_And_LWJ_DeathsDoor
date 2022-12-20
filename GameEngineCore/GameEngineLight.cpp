#include "PreCompile.h"
#include "GameEngineLight.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderTarget.h"

GameEngineLight::GameEngineLight()
{
	Data.LightTargetSizeX = 4096;
	Data.LightTargetSizeY = 4096;
	Data.LightNear = 0.1f;
	Data.LightFar = 1000.0f;
}

GameEngineLight::~GameEngineLight()
{
}

void GameEngineLight::ShadowTargetSetting()
{
	ShadowTarget->Clear();
	ShadowTarget->Setting();
}

void GameEngineLight::Start()
{
	ShadowTarget = GameEngineRenderTarget::Create();

	ShadowTarget->CreateRenderTargetTexture({ Data.LightTargetSizeX, Data.LightTargetSizeY }, DXGI_FORMAT_R32_FLOAT, { 0.0f, 0.0f, 0.0f });
	ShadowTarget->CreateDepthTexture();
}

void GameEngineLight::Update(float _DeltaTime)
{
	Data.LightPos = GetTransform().GetWorldPosition();
	Data.LightDir = GetTransform().GetForwardVector();
	Data.LightDir.w = 0.0f;
	Data.LightRevDir = -Data.LightDir;
	Data.LightRevDir.w = 0.0f;

	Data.LightViewMatrix.LookToLH(
		GetTransform().GetLocalPosition(),
		GetTransform().GetForwardVector(),
		GetTransform().GetUpVector());

	Data.LightProjectionMatrix.OrthographicLH(Data.LightTargetSizeX, Data.LightTargetSizeY, Data.LightNear, Data.LightFar);
}

void GameEngineLight::LightDataUpdate(GameEngineCamera* _Camera)
{
	GetTransform().SetView(_Camera->GetViewMatrix());
	GetTransform().SetProjection(_Camera->GetProjectionMatrix());
	GetTransform().CalculateWorldViewProjection();

	float4x4 WorldView = GetTransform().GetTransformData().WorldViewMatrix;

	Data.ViewLightPos = Data.ViewLightPos * GetTransform().GetViewMatrix();
	Data.ViewLightDir = Data.LightDir * GetTransform().GetViewMatrix();
	Data.ViewLightDir.Normalize3D();
	Data.ViewLightDir.w = 0.0f;
	Data.ViewLightRevDir = Data.LightRevDir * GetTransform().GetViewMatrix();
	Data.ViewLightRevDir.Normalize3D();
	Data.ViewLightRevDir.w = 0.0f;
	Data.CameraPosition = _Camera->GetTransform().GetWorldPosition() * GetTransform().GetViewMatrix();
}
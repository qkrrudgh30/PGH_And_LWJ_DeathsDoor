#include "PreCompile.h"
#include "GameEngineLight.h"
#include "GameEngineCamera.h"

GameEngineLight::GameEngineLight()
{
}

GameEngineLight::~GameEngineLight()
{
}


void GameEngineLight::Update(float _DeltaTime)
{
	Data.LightPos = GetTransform().GetWorldPosition();
	Data.LightDir = GetTransform().GetForwardVector();
	Data.LightDir.w = 0.0f;
	Data.LightRevDir = -Data.LightDir;
	Data.LightRevDir.w = 0.0f;
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
}
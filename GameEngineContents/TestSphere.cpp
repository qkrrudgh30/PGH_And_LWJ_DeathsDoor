#include "PreCompile.h"
#include "TestSphere.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

TestSphere::TestSphere() 
{
}

TestSphere::~TestSphere() 
{
}

void TestSphere::Start()
{
	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	Renderer->GetRenderUnit()->SetMesh("Sphere"); 
	Renderer->SetMaterial("Color");
	float4 ResultColor = { 1.f,1.f,1.f,1.f };
	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	Renderer->GetTransform().SetLocalScale(float4{ 300.f, 300.f, 300.f });
}

void TestSphere::Update(float _fDeltatime)
{
}


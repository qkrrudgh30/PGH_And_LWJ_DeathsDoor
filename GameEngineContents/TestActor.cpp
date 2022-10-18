#include "PreCompile.h"
#include "TestActor.h"
#include "GameEngineCore/GameEngineDefaultRenderer.h"

TestActor::TestActor()
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	Renderer->SetMesh("Box");
	Renderer->SetPipeLine("Color");

	float4 ResultColor = float4{ 1.f, 0.f, 0.f, 1.f};
	Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);
}

void TestActor::Update(float _DeltaTime)
{
}


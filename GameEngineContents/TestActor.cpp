#include "PreCompile.h"
#include "TestActor.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

TestActor::TestActor()
	: ResultColor()
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f};

	//Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//Renderer->SetPipeLine("Color");
	//Renderer->GetRenderUnit().SetMesh("Box");

	GameEngineFBXRenderer* Renderer = CreateComponent<GameEngineFBXRenderer>();
	Renderer->SetFBXMesh("Hall.FBX", "Texture");
	Renderer->GetTransform().SetLocalRotate(float4{20.f, -20.f, 180.f});

	// Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
}

void TestActor::Update(float _DeltaTime)
{
	// Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);
}


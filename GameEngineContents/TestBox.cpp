#include "PreCompile.h"
#include "TestBox.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

TestBox::TestBox() 
{
}

TestBox::~TestBox() 
{
}

void TestBox::Start()
{
	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	Renderer->GetRenderUnit()->SetMesh("Box"); 
	Renderer->SetMaterial("ContentsLightColor");
	float4 ResultColor = { 1.f,1.f,1.f,1.f };
	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	Renderer->GetTransform().SetLocalScale(float4{ 300.f, 300.f, 300.f });

}

void TestBox::Update(float _fDeltatime)
{
}


#include "PreCompile.h"
#include "TestBox.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

TestBox::TestBox() 
	: m_structLightInfo{}
{
}

TestBox::~TestBox() 
{
}

void TestBox::Start()
{
	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	Renderer->GetRenderUnit()->SetMesh("Box"); 
	Renderer->SetMaterial("ContentsDeferredLightColor");
	float4 ResultColor = { 1.f,1.f,1.f,1.f };
	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);
	m_structLightInfo.uOnOffLight = 1u;
	Renderer->GetShaderResources().SetConstantBufferLink("AdditionalInfoForLight", m_structLightInfo);

	Renderer->GetTransform().SetLocalScale(float4{ 300.f, 300.f, 300.f });
}

void TestBox::Update(float _fDeltatime)
{
}


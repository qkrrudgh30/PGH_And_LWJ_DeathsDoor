#include "PreCompile.h"
#include "TsetBackGround.h"

TsetBackGround::TsetBackGround() 
{
}

TsetBackGround::~TsetBackGround() 
{
}

void TsetBackGround::Start()
{


	float4 ResultColor = {1.f,0.f,1.f};

	{
	/*	GameEngineDefaultRenderer* Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Rect");

		float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		Renderer->GetTransform().SetLocalScale({ 1000.0f, 1000.0f ,1000.0f });
		Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", Color);
		*/

		GameEngineDefaultRenderer* Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
		Renderer->GetRenderUnit().SetMesh("Rect");
		float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", Color);


	}
	

}
void TsetBackGround::Update(float _DeltaTime)
{
}
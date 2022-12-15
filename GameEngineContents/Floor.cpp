

#include "PreCompile.h"
#include "Floor.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

Floor::Floor()
	: ResultColor()
{
}

Floor::~Floor()
{
}

void Floor::Start()
{
	
	ResultColor = float4{ 1.f, 1.f, 1.f, 1.f };
	std::shared_ptr < GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	GetTransform().SetWorldPosition({ 0.f, 0.f,-5000.f });
	Renderer->SetFBXMesh("Floor.fbx", "PreviousColor");
	Renderer->GetAllRenderUnit()[0][0]->ShaderResources.SetConstantBufferLink("ResultColor", float4::WHITE);
	
}

void Floor::Update(float _DeltaTime)
{

}


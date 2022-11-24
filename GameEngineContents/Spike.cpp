

#include "PreCompile.h"
#include "Spike.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

Spike::Spike()
	: ResultColor()
{
}

Spike::~Spike()
{
}

void Spike::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f };
	std::shared_ptr < GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->GetTransform().SetLocalScale(float4{ 1.1f, 0.5f, 0.9f });
	Renderer->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });
	Renderer->GetTransform().SetLocalPosition({ -1369.f,0.f,-1750.f });
	Renderer->SetFBXMesh("VerticalWall.fbx", "Texture");
	
}

void Spike::Update(float _DeltaTime)
{

}


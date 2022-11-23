

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
	Renderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
	Renderer->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });
	Renderer->GetTransform().SetLocalPosition({ 0.f,0.f,0.f });
	Renderer->SetFBXMesh("Spike.fbx", "Texture");
	
}

void Spike::Update(float _DeltaTime)
{

}


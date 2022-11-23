

#include "PreCompile.h"
#include "Rock.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

Rock::Rock()
	: ResultColor()
{
}

Rock::~Rock()
{
}

void Rock::Start()
{
	std::shared_ptr < GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
	Renderer->GetTransform().SetLocalPosition(float4{ 0.f, 10.f, 0.f });
	Renderer->SetFBXMesh("Rock.fbx", "Texture");
	

}

void Rock::Update(float _DeltaTime)
{

}


#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineBase\GameEngineRandom.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		// Renderer->ScaleToTexture();
	}

	{
		GameEngineCollision* Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::UI);
	}
}

void Monster::Update(float _DeltaTime) 
{

}
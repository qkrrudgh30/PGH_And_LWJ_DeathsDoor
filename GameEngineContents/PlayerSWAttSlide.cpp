#include "PreCompile.h"
#include "PlayerSWAttSlide.h"

PlayerSWAttSlide::PlayerSWAttSlide()
{
}

PlayerSWAttSlide::~PlayerSWAttSlide()
{
}

void PlayerSWAttSlide::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 150.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	


}

void PlayerSWAttSlide::Update(float _DeltaTime)
{
}

CollisionReturn PlayerSWAttSlide::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	return CollisionReturn();
}


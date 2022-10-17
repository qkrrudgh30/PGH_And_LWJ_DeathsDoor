#include "PreCompile.h"
#include "PlayerSWAtt2.h"

PlayerSWAtt2::PlayerSWAtt2()
{
}

PlayerSWAtt2::~PlayerSWAtt2()
{
}

void PlayerSWAtt2::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 100.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	


}

void PlayerSWAtt2::Update(float _DeltaTime)
{
}

CollisionReturn PlayerSWAtt2::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	return CollisionReturn();
}


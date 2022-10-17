#include "PreCompile.h"
#include "PlayerSWAtt3.h"

PlayerSWAtt3::PlayerSWAtt3()
{
}

PlayerSWAtt3::~PlayerSWAtt3()
{
}

void PlayerSWAtt3::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 150.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	


}

void PlayerSWAtt3::Update(float _DeltaTime)
{
}

CollisionReturn PlayerSWAtt3::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	return CollisionReturn();
}


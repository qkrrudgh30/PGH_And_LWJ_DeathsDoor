#include "PreCompile.h"
#include "PlayerSWAtt1.h"

PlayerSWAtt1::PlayerSWAtt1() 
{
}

PlayerSWAtt1::~PlayerSWAtt1() 
{
}

void PlayerSWAtt1::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	


}

void PlayerSWAtt1::Update(float _DeltaTime)
{
}

CollisionReturn PlayerSWAtt1::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	return CollisionReturn();
}


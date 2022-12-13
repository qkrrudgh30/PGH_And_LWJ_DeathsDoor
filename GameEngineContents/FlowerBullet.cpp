

#include "PreCompile.h"
#include "FlowerBullet.h"
#include "FlowerBulletEff.h"
#include"GameEngineBase/GameEngineRandom.h"


FlowerBullet::FlowerBullet()
{
}

FlowerBullet::~FlowerBullet()
{
}

void FlowerBullet::Start()
{

	m_fSpeed = 600.f;



	for (size_t i = 0; i < 15; i++)
	{
		std::shared_ptr < FlowerBulletEff> Bullet = GetLevel()->CreateActor<FlowerBulletEff>(OBJECTORDER::Eff);
		float4 MyPos = GetTransform().GetWorldPosition();
		MyPos.y = GameEngineRandom::MainRandom.RandomFloat(MyPos.y - 5.f, MyPos.y + 5.f);
		Bullet->GetTransform().SetWorldPosition(MyPos);
		Bullet->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(20.f, 60.f);



		m_vFlowerEff.push_back(Bullet);

	}

	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 500.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);



}

void FlowerBullet::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;












	if (m_fLifeTime >= 4.f)
	{
		Death();
	}


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&FlowerBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



	float4 MoveDir = GetTransform().GetForwardVector();
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);

}

CollisionReturn FlowerBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	Player*  NewPlayer = Player::GetMainPlayer();

	NewPlayer->m_Info.m_Hp -= 1;


	Death();
	return CollisionReturn::Break;
}


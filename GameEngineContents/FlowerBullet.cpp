

#include "PreCompile.h"
#include "FlowerBullet.h"
#include "FlowerBulletEff.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "PalyerFireMgr.h"


FlowerBullet::FlowerBullet()
{
}

FlowerBullet::~FlowerBullet()
{
}

void FlowerBullet::Start()
{

	m_fSpeed = 600.f;



	for (size_t i = 0; i < 10; i++)
	{
		std::shared_ptr < FlowerBulletEff> Bullet = GetLevel()->CreateActor<FlowerBulletEff>(OBJECTORDER::Eff);
		float4 MyPos = GetTransform().GetWorldPosition();
		MyPos.y = GameEngineRandom::MainRandom.RandomFloat(MyPos.y - 5.f, MyPos.y + 5.f);
		Bullet->GetTransform().SetWorldPosition(MyPos);
		float m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(40.f, 60.f);
		Bullet->GetTransform().SetWorldScale({ m_fScaleMax, m_fScaleMax,10.f });


		m_vFlowerEff.push_back(Bullet);

	}

	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 500.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);



}

void FlowerBullet::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;

	m_fEffTime += _DeltaTime;

	if (m_fEffTime >= 0.01f)
	{
		m_fEffTime -= 0.01f;

		for (size_t i = 0; i < m_vFlowerEff.size(); i++)
		{
			if (m_vFlowerEff[i]->m_bScaleZero == false)
			{

				float4 MyPos = GetTransform().GetWorldPosition();
				MyPos.y = GameEngineRandom::MainRandom.RandomFloat(MyPos.y - 5.f, MyPos.y + 5.f);
				m_vFlowerEff[i]->GetTransform().SetWorldPosition(MyPos);
				float m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(40.f, 60.f);
				m_vFlowerEff[i]->GetTransform().SetWorldScale({ m_fScaleMax, m_fScaleMax,10.f });

				m_vFlowerEff[i]->m_bScaleZero = true;

				break;
			}
		}


	}
	







	if (m_fLifeTime >= 4.f)
	{
		Death();
		for (size_t i = 0; i < m_vFlowerEff.size(); i++)
		{
			m_vFlowerEff[i]->Death();
		}

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

	for (size_t i = 0; i < m_vFlowerEff.size(); i++)
	{
		m_vFlowerEff[i]->Death();
	}

	std::weak_ptr < PalyerFireMgr> Bullet = GetLevel()->CreateActor<PalyerFireMgr>(OBJECTORDER::Eff);
	float4 MyPos = NewPlayer->GetTransform().GetWorldPosition();
	Bullet.lock()->GetTransform().SetWorldPosition(MyPos);

	Death();
	return CollisionReturn::Break;
}


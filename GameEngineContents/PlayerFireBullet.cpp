

#include "PreCompile.h"
#include "PlayerFireBullet.h"
#include "PlayerFireBulletEff.h"
#include"GameEngineBase/GameEngineRandom.h"

#include "PalyerFireMgr.h"

PlayerFireBullet::PlayerFireBullet()
{
}

PlayerFireBullet::~PlayerFireBullet()
{
}

void PlayerFireBullet::Start()
{

	m_fSpeed = 800.f;



	for (size_t i = 0; i < 10; i++)
	{
		std::shared_ptr < PlayerFireBulletEff> Bullet = GetLevel()->CreateActor<PlayerFireBulletEff>(OBJECTORDER::Eff);
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

void PlayerFireBullet::Update(float _DeltaTime)
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


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		std::bind(&PlayerFireBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



	float4 MoveDir = GetTransform().GetForwardVector();
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);

}

CollisionReturn PlayerFireBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	

	for (size_t i = 0; i < m_vFlowerEff.size(); i++)
	{
		m_vFlowerEff[i]->Death();
	}


	std::weak_ptr < PalyerFireMgr> Bullet = GetLevel()->CreateActor<PalyerFireMgr>(OBJECTORDER::Eff);
	Bullet.lock()->m_bColorBlue = true;
	float4 MyPos = _Other->GetTransform().GetWorldPosition();
	Bullet.lock()->GetTransform().SetWorldPosition(MyPos);


	Death();
	return CollisionReturn::Break;
}


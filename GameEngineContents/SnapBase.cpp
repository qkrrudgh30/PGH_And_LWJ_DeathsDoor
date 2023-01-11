#include "PreCompile.h"
#include "SnapBase.h"
#include "SnapTarGet.h"
#include"GameEngineBase/GameEngineRandom.h"
SnapBase::SnapBase() 
{
}

SnapBase::~SnapBase() 
{
}



void SnapBase::Start()
{
	
}

void SnapBase::Update(float _DeltaTime)
{

	//GameEngineRandom::MainRandom.

	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

	float RandX = GameEngineRandom::MainRandom.RandomFloat(PlayerPos.x - 600.f, PlayerPos.x + 600.f);
	float RandZ = GameEngineRandom::MainRandom.RandomFloat(PlayerPos.z - 600.f, PlayerPos.z + 600.f);


	float Rand2X = GameEngineRandom::MainRandom.RandomFloat(PlayerPos.x - 600.f, PlayerPos.x + 600.f);
	float Rand2Z = GameEngineRandom::MainRandom.RandomFloat(PlayerPos.z - 600.f, PlayerPos.z + 600.f);



	m_fMakeTime += _DeltaTime;

	if (m_fMakeTime >= 0.f && m_bBulletcheck[0] == false)
	{
		m_bBulletcheck[0] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ});
		
		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });

	}
	else if (m_fMakeTime >= 0.4f && m_bBulletcheck[1] == false)
	{
		m_bBulletcheck[1] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });
		

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });


	
	}
	else if (m_fMakeTime >= 0.8f && m_bBulletcheck[2] == false)
	{
		m_bBulletcheck[2] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });


	}

	else if (m_fMakeTime >= 1.2f && m_bBulletcheck[3] == false)
	{
		m_bBulletcheck[3] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });

		
	
	}

	else if (m_fMakeTime >= 1.6f && m_bBulletcheck[4] == false)
	{
		m_bBulletcheck[4] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });

	
	}
	else if (m_fMakeTime >= 2.f && m_bBulletcheck[5] == false)
	{
		m_bBulletcheck[5] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });

	


	}
	else if (m_fMakeTime >= 2.4f && m_bBulletcheck[6] == false)
	{
		m_bBulletcheck[6] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });

	


	}
	else if (m_fMakeTime >= 2.8f && m_bBulletcheck[7] == false)
	{
		m_bBulletcheck[7] = true;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ RandX ,10.f, RandZ });

		Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition({ Rand2X ,10.f, Rand2Z });

	


	}

}


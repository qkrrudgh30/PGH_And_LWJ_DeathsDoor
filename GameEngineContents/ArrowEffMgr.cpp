

#include "PreCompile.h"
#include "ArrowEffMgr.h"

#include "ArrowEff.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "BillboardRenderer.h"
ArrowEffMgr::ArrowEffMgr()
{
}

ArrowEffMgr::~ArrowEffMgr()
{
}



void ArrowEffMgr::Start()
{

}

void ArrowEffMgr::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime;


	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	float4 MyPos = GetTransform().GetWorldPosition();
	float4 Rot = {};
	float RandY = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);
													
	float RandX = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;
	float RandZ = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;

	Rot = { RandX ,RandY ,RandZ };

	

	/*if (m_fSpeed >= 0.05f)
	{
		m_fSpeed -= 0.05f;


		std::weak_ptr < ArrowEff> Bullet = GetLevel()->CreateActor<ArrowEff>(OBJECTORDER::Eff);
		
		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Bullet.lock()->m_fHitDir = Rot;
		Bullet.lock()->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(20.f,150.f);

		++m_iCount;


		if (m_iCount >= m_iCountMax)
		{

			Death();
		}

	}*/



	for (int i = 0; i <= 40; ++i)
	{

		std::weak_ptr < ArrowEff> Bullet = GetLevel()->CreateActor<ArrowEff>(OBJECTORDER::Eff);

		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Bullet.lock()->m_fHitDir = Rot;
	//	Bullet.lock()->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->TexRenderer->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(50.f, 200.f);

		if (i == 40)
		{
			Death();
		}
	}


}


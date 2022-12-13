

#include "PreCompile.h"
#include "ScreamMgr.h"

#include "ScreamEff.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "BillboardRenderer.h"
ScreamMgr::ScreamMgr()
{
}

ScreamMgr::~ScreamMgr()
{
}



void ScreamMgr::Start()
{
	m_fSpeed = 0.5f;
}

void ScreamMgr::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime;


	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	float4 MyPos = GetTransform().GetWorldPosition();
	float4 Rot = {};
	float RandY = GameEngineRandom::MainRandom.RandomFloat(90.f, 180.f);

	float RandX = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);
	float RandZ = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);

	Rot = { RandX ,RandY ,RandZ };

	if (m_fSpeed >= 0.5f)
	{
		m_fSpeed -= 0.5f;

		++m_iCount;
		

		std::weak_ptr < ScreamEff> Bullet = GetLevel()->CreateActor<ScreamEff>(OBJECTORDER::Eff);

		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Bullet.lock()->m_fHitDir = Rot;
		//	Bullet.lock()->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->TexRenderer->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(150.f, 350.f);




		if (m_iCount >= 4)
		{
			Death();
		}
	}
	


}


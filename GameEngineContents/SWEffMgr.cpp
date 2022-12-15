

#include "PreCompile.h"
#include "SWEffMgr.h"

#include "SWEff.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "BillboardRenderer.h"
SWEffMgr::SWEffMgr()
{
}

SWEffMgr::~SWEffMgr()
{
}



void SWEffMgr::Start()
{

}

void SWEffMgr::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime;

	float4 MyPos = GetTransform().GetWorldPosition();
	float4 Rot = {};





	for (int i = 0; i <= 40; ++i)
	{

		float RandY = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);

		float RandX = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;
		float RandZ = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;

		Rot = { RandX ,RandY ,RandZ };



		std::weak_ptr < SWEff> Bullet = GetLevel()->CreateActor<SWEff>(OBJECTORDER::Eff);

		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->m_fHitDir = Rot;
		//	Bullet.lock()->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->TexRenderer->GetTransform().SetWorldRotation(Rot);
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(50.f, 100.f);

		if (i == 40)
		{
			Death();
		}
	}


}


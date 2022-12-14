


#include "PreCompile.h"
#include "PalyerFireMgr.h"

#include "PlayerFireEff.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "BillboardRenderer.h"
PalyerFireMgr::PalyerFireMgr()
{
}

PalyerFireMgr::~PalyerFireMgr()
{
}



void PalyerFireMgr::Start()
{

}

void PalyerFireMgr::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime;


	
	float4 MyPos = GetTransform().GetWorldPosition();
	float4 Rot = {};
	



	for (int i = 0; i <= 20; ++i)
	{

		float RandY = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);

		float RandX = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;
		float RandZ = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;

		Rot = { RandX ,RandY ,RandZ };


		std::weak_ptr < PlayerFireEff> Bullet = GetLevel()->CreateActor<PlayerFireEff>(OBJECTORDER::Eff);

		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->GetTransform().SetWorldRotation(Rot);
		float ScaleMax_f = GameEngineRandom::MainRandom.RandomFloat(30.f, 50.f);
		float4 ScaleMax = { ScaleMax_f ,ScaleMax_f ,10.f};
		Bullet.lock()->GetTransform().SetWorldScale(ScaleMax);


		if (i == 20)
		{
			Death();
		}
	}


}


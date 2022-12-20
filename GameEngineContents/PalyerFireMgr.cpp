


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
	

	

	for (int i = 0; i <= 30; ++i)
	{


		MyPos.x = GameEngineRandom::MainRandom.RandomFloat(MyPos.x - 5.f, MyPos.x + 5.f);
		MyPos.y = GameEngineRandom::MainRandom.RandomFloat(MyPos.y - 5.f, MyPos.y + 5.f);
		MyPos.z = GameEngineRandom::MainRandom.RandomFloat(MyPos.z - 5.f, MyPos.z + 5.f);


		float RandY = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);

		float RandX = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;
		float RandZ = GameEngineRandom::MainRandom.RandomFloat(0.f, 180.f) - 90.f;

		Rot = { RandX ,RandY ,RandZ };


	
		std::weak_ptr < PlayerFireEff> Bullet = GetLevel()->CreateActor<PlayerFireEff>(OBJECTORDER::Eff);

		if (m_bColorBlue)
		{
			Bullet.lock()->ChangeColorBlue();
		}
		
		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(RanSmall, RanBig);



		Bullet = GetLevel()->CreateActor<PlayerFireEff>(OBJECTORDER::Eff);

		if (m_bColorBlue)
		{
			Bullet.lock()->ChangeColorBlue();
		}

		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(RanSmall, RanBig);
		Bullet.lock()->TexRenderer->GetTransform().SetLocalRotation({ 0.f,-90.f,0.f });
	}
	



	Death();
}

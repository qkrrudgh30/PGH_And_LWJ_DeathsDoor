
#include "PreCompile.h"
#include "Firemgr.h"

#include "FireEff.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "BillboardRenderer.h"
Firemgr::Firemgr()
{
}

Firemgr::~Firemgr()
{
}



void Firemgr::Start()
{

}

void Firemgr::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime;



	for (int i = 0; i <= 10; ++i)
	{

		std::weak_ptr < FireEff> Bullet = GetLevel()->CreateActor<FireEff>(OBJECTORDER::Eff);
		float4 MyPos = GetTransform().GetWorldPosition();

		MyPos.x = GameEngineRandom::MainRandom.RandomFloat(MyPos.x - 20.f, MyPos.x + 20.f);
		MyPos.y = GameEngineRandom::MainRandom.RandomFloat(MyPos.y - 5.f, MyPos.y + 5.f);
		MyPos.z = GameEngineRandom::MainRandom.RandomFloat(MyPos.z - 20.f, MyPos.z + 20.f);

		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->m_fStartPos = MyPos;
		Bullet.lock()->m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(20.f, 60.f);

		if (i == 10)
		{
			Death();
		}
	}


}


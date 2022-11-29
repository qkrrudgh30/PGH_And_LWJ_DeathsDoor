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



	m_fMakeTime += _DeltaTime;

	if (m_fMakeTime >= 0.f && m_bBulletcheck[0] == true)
	{
		m_bBulletcheck[0] = false;
		std::weak_ptr < SnapTarGet> Bullet = GetLevel()->CreateActor<SnapTarGet>(OBJECTORDER::MonsterAtt);

		

	}



}


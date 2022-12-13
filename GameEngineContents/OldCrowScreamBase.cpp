

#include "PreCompile.h"
#include "OldCrowScreamBase.h"

#include "ScreamBullet.h"
#include"GameEngineBase/GameEngineRandom.h"
OldCrowScreamBase::OldCrowScreamBase()
{
}

OldCrowScreamBase::~OldCrowScreamBase()
{
}



void OldCrowScreamBase::Start()
{
	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("29_LastBossBat.mp3");
}

void OldCrowScreamBase::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime;

	
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	float4 MyPos = GetTransform().GetWorldPosition();
	float Angle = DirToRot(PlayerPos, MyPos);
	float RandY = GameEngineRandom::MainRandom.RandomInt(Angle - 30.f, Angle + 30.f);
	


	if (m_fSpeed >= 0.05f)
	{
		m_fSpeed -= 0.05f;


		std::weak_ptr < ScreamBullet> Bullet = GetLevel()->CreateActor<ScreamBullet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetLocalRotation({ 0.f ,RandY, 0.f });
		Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	
		++m_iCount;


		if (m_iCount >= m_iCountMax)
		{

			Death();
		}

	}



}


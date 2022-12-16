

#include "PreCompile.h"
#include "SnapBullet.h"
#include "SnapTarGet.h"

#include"GameEngineBase/GameEngineRandom.h"
#include "FlowerBulletEff.h"
#include "PalyerFireMgr.h"
#include "BillboardRenderer.h"
#pragma region TestCode

#include "SnapCircle.h"

#pragma endregion


SnapBullet::SnapBullet()
{
}

SnapBullet::~SnapBullet()
{
}

void SnapBullet::Start()
{
	m_Info.Dammage = 1;



	for (size_t i = 0; i < 10; i++)
	{
		std::shared_ptr < FlowerBulletEff> Bullet = GetLevel()->CreateActor<FlowerBulletEff>(OBJECTORDER::Eff);
		float4 MyPos = GetTransform().GetWorldPosition();
		MyPos.y = GameEngineRandom::MainRandom.RandomFloat(MyPos.y - 5.f, MyPos.y + 5.f);
		Bullet->GetTransform().SetWorldPosition(MyPos);
		float m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(40.f, 60.f);
		Bullet->GetTransform().SetWorldScale({ m_fScaleMax, m_fScaleMax,10.f });


		m_vFlowerEff.push_back(Bullet);

	}


	{
		
		float4 color = { 1.f,0.f,0.f, 1.f };

	
		sptrTestPicture = CreateComponent<BillboardRenderer>();
		sptrTestPicture->SetTexture("ripple_alpha.png");
		//TexRenderer->ScaleToTexture();
		sptrTestPicture->GetTransform().SetLocalScale({ 20.f, 20.f, 10.f });
		sptrTestPicture->GetPixelData().MulColor = color;
		sptrTestPicture->SetBillboardInfo(1);
		//sptrTestPicture->ChangeCamera(CAMERAORDER::USER1);

	}


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 40.0f, 40.0f, 40.0f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);
	AttCollision->Off();

	m_fDownSpeed = GameEngineRandom::MainRandom.RandomFloat(800.f, 1200.f);

}

void SnapBullet::Update(float _DeltaTime)
{
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


	m_fSpeed = GameEngineRandom::MainRandom.RandomFloat(200.f, 500.f);
	
	GetTransform().SetWorldDownMove(m_fDownSpeed, _DeltaTime);



	float4 TarGetDir = m_pTarget.lock()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	float Len = TarGetDir.Length();

	if (Len <= 40.f)
	{

		AttCollision->On();

		AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Player), CollisionType::CT_OBB,
		std::bind(&SnapBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	}


	if (Len <= 20.f)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("21-1_MeteorHit.mp3");

		std::weak_ptr < PalyerFireMgr> Bullet = GetLevel()->CreateActor<PalyerFireMgr>(OBJECTORDER::Eff);
		float4 MyPos = m_pTarget.lock()->GetTransform().GetWorldPosition();
		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->RanSmall = 60.f;
		Bullet.lock()->RanBig = 100.f;



		m_pTarget.lock()->Death();
		m_pTarget.reset();
		for (size_t i = 0; i < m_vFlowerEff.size(); i++)
		{
			m_vFlowerEff[i]->Death();
		}





		Death();

	}



	float4 MyRot = sptrTestPicture->GetTransform().GetLocalRotation();
	MyRot.z += m_fSpeed * _DeltaTime;
	sptrTestPicture->GetTransform().SetLocalRotation(MyRot);



}

CollisionReturn SnapBullet::PlayerCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{
	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("21-1_MeteorHit.mp3");
	
	
	
	
	
	
	if (m_pTarget.lock())
	{

		std::weak_ptr < PalyerFireMgr> Bullet = GetLevel()->CreateActor<PalyerFireMgr>(OBJECTORDER::Eff);
		float4 MyPos = m_pTarget.lock()->GetTransform().GetWorldPosition();
		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);


		m_pTarget.lock()->Death();
		m_pTarget.reset();



		for (size_t i = 0; i < m_vFlowerEff.size(); i++)
		{
			m_vFlowerEff[i]->Death();
		}


	}

	Player::GetMainPlayer()->m_bHitBackCheck = true;


	Death();


	return CollisionReturn::Break;

}


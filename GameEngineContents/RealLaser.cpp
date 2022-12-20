


#include "PreCompile.h"
#include "RealLaser.h"
#include"GameEngineBase/GameEngineRandom.h"

RealLaser::RealLaser()
{
}

RealLaser::~RealLaser()
{
}

void RealLaser::Start()
{

	m_fSpeed = 1200.f;


	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->ChangeCamera(CAMERAORDER::USER1);
		TexRenderer->SetTexture("LightningBoltTexture.png");
		TexRenderer->SetPivot(PIVOTMODE::LEFT);
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 1.f });
		TexRenderer->GetTransform().SetLocalRotation({ 45.f,135.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}

	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("23_MiddleBossLaser.mp3");
	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer2->ChangeCamera(CAMERAORDER::USER1);
		TexRenderer2->SetTexture("LightningBoltTexture.png");
		TexRenderer2->SetPivot(PIVOTMODE::LEFT);
		TexRenderer2->GetTransform().SetLocalScale({ 2000.f, 100.f, 1.f });
		TexRenderer2->GetTransform().SetLocalRotation({ 135.f,135.f,0.f });
		TexRenderer2->GetPixelData().MulColor = color;

	}
}

void RealLaser::Update(float _DeltaTime)
{


	float RandomF = GameEngineRandom::MainRandom.RandomFloat(0, 400.f);


	TexRenderer->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });
	TexRenderer2->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });


	//m_fScaleMax += 600.f * _DeltaTime;



	//TexRenderer->GetTransform().SetLocalRotation({ 45.f + m_fScaleMax,135.f,0.f });
	//TexRenderer2->GetTransform().SetLocalRotation({ 135.f + m_fScaleMax,135.f,0.f });

}

//-436  218  43






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
		//TexRenderer->SetPivot(PIVOTMODE::LEFT);
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 1.f });
		TexRenderer->GetTransform().SetLocalRotation({ 45.f,135.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}

	
	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer2->ChangeCamera(CAMERAORDER::USER1);
		TexRenderer2->SetTexture("LightningBoltTexture.png");
		//TexRenderer2->SetPivot(PIVOTMODE::LEFT);
		TexRenderer2->GetTransform().SetLocalScale({ 2000.f, 100.f, 1.f });
		TexRenderer2->GetTransform().SetLocalRotation({ 135.f,135.f,0.f });
		TexRenderer2->GetPixelData().MulColor = color;

	}
}

void RealLaser::Update(float _DeltaTime)
{

	if (m_bScalecheck)
	{
		float RandomF = GameEngineRandom::MainRandom.RandomFloat(0, 400.f);
		TexRenderer->SetPivot(PIVOTMODE::LEFT);
		TexRenderer2->SetPivot(PIVOTMODE::LEFT);

		TexRenderer->GetTransform().SetLocalRotation({ 45.f,135.f,0.f });
		TexRenderer2->GetTransform().SetLocalRotation({ 135.f,135.f,0.f });

		TexRenderer->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });
		TexRenderer2->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });

	}
	else
	{
		float RandomF = GameEngineRandom::MainRandom.RandomFloat(0, 100.f);
		m_fScaleMax += 600.f * _DeltaTime;

		TexRenderer->GetTransform().SetLocalScale({ RandomF, RandomF, RandomF });
		TexRenderer2->GetTransform().SetLocalScale({ RandomF, RandomF, RandomF });



		TexRenderer->GetTransform().SetLocalRotation({ m_fScaleMax ,m_fScaleMax,m_fScaleMax });
		TexRenderer2->GetTransform().SetLocalRotation({ m_fScaleMax , m_fScaleMax,m_fScaleMax });

	}
	

	
}

//-436  218  43



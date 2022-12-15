
#include "PreCompile.h"
#include "SWEff.h"
#include "BillboardRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"

SWEff::SWEff()
{
}

SWEff::~SWEff()
{
}

void SWEff::Start()
{

	m_fSpeed = 800.f;


	float R = GameEngineRandom::MainRandom.RandomFloat(700.f, 1000.f) / 1000.f;
	float A = GameEngineRandom::MainRandom.RandomFloat(700.f, 1000.f) / 1000.f;


	float4 color = { R ,0.f,0.f,A };
	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("Soft.png");
	TexRenderer->GetTransform().SetLocalScale({ 20.f, 20.f, 1 });
	//sptrTestPicture->SetPivot(PIVOTMODE::LEFT);
	TexRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	TexRenderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
	TexRenderer->GetPixelData().MulColor = color;
	TexRenderer->ChangeCamera(CAMERAORDER::USER1);


	//Death(1.f);
}

void SWEff::Update(float _DeltaTime)
{



	float4 MyScale = TexRenderer->GetTransform().GetLocalScale();

	if (m_bScalecheck)
	{
		//MyScale.x -= 1000.f * _DeltaTime;
		MyScale.y -= 1000.f * _DeltaTime;
		//	MyScale.z -= 100.f * _DeltaTime;

		if (0.f >= MyScale.y)
		{
			Death();
		}

	}
	else
	{
		//MyScale.x += 1000.f * _DeltaTime;
		MyScale.y += 1000.f * _DeltaTime;
		//	MyScale.z += 100.f * _DeltaTime;

		if (m_fScaleMax <= MyScale.y)
		{
			m_bScalecheck = !m_bScalecheck;
		}
	}

	TexRenderer->GetTransform().SetWorldScale(MyScale);


	TexRenderer->GetTransform().SetWorldMove(TexRenderer->GetTransform().GetUpVector() * _DeltaTime * m_fSpeed);





}


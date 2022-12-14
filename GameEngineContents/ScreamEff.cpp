

#include "PreCompile.h"
#include "ScreamEff.h"
#include "BillboardRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"




ScreamEff::ScreamEff()
{
}

ScreamEff::~ScreamEff()
{
}

void ScreamEff::Start()
{

	m_fSpeed = 1200.f;



	float A = GameEngineRandom::MainRandom.RandomFloat(700.f, 1000.f) / 1000.f;


	float4 color = { 0.01f ,0.f,0.f,1.f };
	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("Soft.png");
	TexRenderer->GetTransform().SetLocalScale({ 10.f, 10.f, 1 });
	TexRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	TexRenderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
	TexRenderer->GetPixelData().MulColor = color;

	


	//Death(1.f);
}

void ScreamEff::Update(float _DeltaTime)
{



	float4 MyScale = TexRenderer->GetTransform().GetLocalScale();

	if (m_bScalecheck)
	{
		
		MyScale.y -= 1000.f * _DeltaTime;
		if (0.f >= MyScale.y)
		{
			Death();
		}

	}
	else
	{
		
		MyScale.y += 1000.f * _DeltaTime;
		if (m_fScaleMax <= MyScale.y)
		{
			m_bScalecheck = !m_bScalecheck;
		}
	}

	TexRenderer->GetTransform().SetWorldScale(MyScale);


	TexRenderer->GetTransform().SetWorldMove(TexRenderer->GetTransform().GetUpVector() * _DeltaTime * m_fSpeed);





}

//-436  218  43
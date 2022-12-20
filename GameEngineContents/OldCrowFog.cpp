
#include "PreCompile.h"
#include "OldCrowFog.h"
#include "BillboardRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"

OldCrowFog::OldCrowFog()
{
}

OldCrowFog::~OldCrowFog()
{
}

void OldCrowFog::Start()
{

	m_fSpeed = 800.f;




	float4 color = { 50.f ,50.f,50.f,1.f };
	sptrTestPicture = CreateComponent<BillboardRenderer>();
	sptrTestPicture->SetTexture("SimpleTestParticle.png");
	sptrTestPicture->GetTransform().SetLocalScale({ 10.f, 10.f, 1 });
	sptrTestPicture->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	sptrTestPicture->ChangeCamera(CAMERAORDER::MAINCAMERA);
	sptrTestPicture->GetPixelData().MulColor = color;
//	sptrTestPicture->RenderOptionInst.Temp1 = 15;
	sptrTestPicture->ChangeCamera(CAMERAORDER::USER1);



	//Death(1.f);
}

void OldCrowFog::Update(float _DeltaTime)
{


	
	float fScaleSpeed = GameEngineRandom::MainRandom.RandomFloat(100.f, 500.f);


	float4 MyScale = sptrTestPicture->GetTransform().GetLocalScale();

	if (m_bScalecheck)
	{
		MyScale.x -= fScaleSpeed * _DeltaTime;
		MyScale.y -= fScaleSpeed * _DeltaTime;
		//	MyScale.z -= 100.f * _DeltaTime;

		if (0.f >= MyScale.y)
		{
			m_bScalecheck = !m_bScalecheck;
			GetTransform().SetWorldPosition(m_fStartPos);
			sptrTestPicture->GetTransform().SetLocalScale({ 10.f, 10.f, 1 });

		}

	}
	else
	{
		MyScale.x += fScaleSpeed * _DeltaTime;
		MyScale.y += fScaleSpeed * _DeltaTime;

		if (m_fScaleMax <= MyScale.y)
		{
			m_bScalecheck = !m_bScalecheck;
		}
	}


	sptrTestPicture->GetTransform().SetWorldScale(MyScale);
	
}

void OldCrowFog::ChangeColorBlue()
{

	float4 color = { 255.f ,36.f,36.f,1.f };


	sptrTestPicture->GetPixelData().MulColor = color;

}


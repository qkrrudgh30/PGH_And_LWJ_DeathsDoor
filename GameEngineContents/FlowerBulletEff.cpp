
#include "PreCompile.h"
#include "FlowerBulletEff.h"
#include "BillboardRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"

FlowerBulletEff::FlowerBulletEff()
{
}

FlowerBulletEff::~FlowerBulletEff()
{
}

void FlowerBulletEff::Start()
{


	m_fSpeed = 300.f;


	float G = GameEngineRandom::MainRandom.RandomFloat(94.f, 228.f) / 255.f;
	float A = GameEngineRandom::MainRandom.RandomFloat(700.f, 1000.f) / 1000.f;


	float4 color = { 255.f ,G,0.f,A };
	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("fireparticle.png");
	TexRenderer->GetTransform().SetLocalScale({ 10.f, 10.f, 1 });

	TexRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	TexRenderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
	TexRenderer->GetPixelData().MulColor = color;
	TexRenderer->RenderOptionInst.Temp1 = 15;
	TexRenderer->ChangeCamera(CAMERAORDER::USER1);


}

void FlowerBulletEff::Update(float _DeltaTime)
{
	float fScaleSpeed = GameEngineRandom::MainRandom.RandomFloat(300.f, 500.f);


	float4 MyScale = TexRenderer->GetTransform().GetLocalScale();

	
	MyScale.x -= fScaleSpeed * _DeltaTime;
	MyScale.y -= fScaleSpeed * _DeltaTime;
	//	MyScale.z -= 100.f * _DeltaTime;

	if (0.f >= MyScale.y)
	{

		TexRenderer->GetTransform().SetWorldPosition(m_fStartPos);
		m_bScalecheck = !m_bScalecheck;
	}

	float4 MyRot = TexRenderer->GetTransform().GetLocalRotation();
	MyRot.z += fScaleSpeed * _DeltaTime;
	TexRenderer->GetTransform().SetLocalRotation(MyRot);


	TexRenderer->GetTransform().SetWorldScale(MyScale);

	

}


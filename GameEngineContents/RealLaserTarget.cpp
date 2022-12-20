

#include "PreCompile.h"
#include "RealLaserTarget.h"
#include "RealLaser.h"
#include"GameEngineBase/GameEngineRandom.h"

RealLaserTarget::RealLaserTarget()
{
}

RealLaserTarget::~RealLaserTarget()
{
}

void RealLaserTarget::Start()
{

	m_fSpeed = 1200.f;

	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("sword_slash_texture 1.png");
	TexRenderer->GetTransform().SetLocalScale({ 10.f, 380.f, 1.f });
	TexRenderer->SetPivot(PIVOTMODE::LEFT);
	TexRenderer->GetTransform().SetLocalRotation({ 90.f, 135.f,0.f });
	//TexRenderer->GetPixelData().MulColor.a = 0.1f;
	

	//Death(1.f);
}

void RealLaserTarget::Update(float _DeltaTime)
{


	float4 TexScale = TexRenderer->GetTransform().GetLocalScale();
	TexScale.x += 800.f * _DeltaTime;
	if (TexScale.x >= 2000.f)
	{
		TexScale.x = 2000.f;
	}
	TexRenderer->GetTransform().SetLocalScale(TexScale);

}

//-436  218  43





#include "PreCompile.h"
#include "TowerLaser.h"
#include "LaserTarget.h"
#include "GameEngineBase/GameEngineRandom.h"
TowerLaser::TowerLaser()
{
}

TowerLaser::~TowerLaser()
{
}

void TowerLaser::Start()
{

	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("LightningBoltTexture.png");
		TexRenderer->SetPivot(PIVOTMODE::RIGHT);
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 1.f });
		TexRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}



}

void TowerLaser::Update(float _DeltaTime)
{
	float4 TarGetPos = m_CLaserTarget.lock()->GetTransform().GetWorldPosition();
	float4 MyPos = GetTransform().GetWorldPosition();
	
	float4 LenFloat = TarGetPos - MyPos;
	float Len = LenFloat.Length();

	float RandomF = GameEngineRandom::MainRandom.RandomFloat(0,50.f);


	TexRenderer->GetTransform().SetLocalScale({ Len, RandomF, 1.f });
	

	float4 Angle = GetDegree3D(MyPos, TarGetPos);
	GetTransform().SetLocalRotation(Angle);


}




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
		TexRenderer->SetPivot(PIVOTMODE::LEFT);
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 1.f });
		TexRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}

	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("23_MiddleBossLaser.mp3");
	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer2->SetTexture("LightningBoltTexture.png");
		TexRenderer2->SetPivot(PIVOTMODE::LEFT);
		TexRenderer2->GetTransform().SetLocalScale({ 100.f, 100.f, 1.f });
		TexRenderer2->GetTransform().SetLocalRotation({ 90.f,0.f,0.f });
		TexRenderer2->GetPixelData().MulColor = color;

	}


}

void TowerLaser::Update(float _DeltaTime)
{
	float4 TarGetPos = m_CLaserTarget.lock()->GetTransform().GetWorldPosition();
	float4 MyPos = GetTransform().GetWorldPosition();

	float4 LenFloat = TarGetPos - MyPos;
	float Len = LenFloat.Length();

	float RandomF = GameEngineRandom::MainRandom.RandomFloat(0, 50.f);


	TexRenderer->GetTransform().SetLocalScale({ Len, RandomF, 1.f });
	TexRenderer2->GetTransform().SetLocalScale({ Len, RandomF, 1.f });




	float AngleY = DirToRotY(TarGetPos, MyPos);


	float AngleZ = DirToRotZ(TarGetPos, MyPos);


	float AngleX = DirToRotX(TarGetPos, MyPos);


	if (AngleZ >= 180.f)
	{
		AngleZ -= 360.f;
	}


	if (AngleX >= 180.f)
	{
		AngleX -= 360.f;
	}

	float Angle = 0.f;
	float Angle2 = 0.f;
	if (abs(AngleZ) > abs(AngleX))
	{
		Angle = AngleZ;
	
	}
	else
	{
		Angle = AngleX;
	
	}


	
	
	GetTransform().SetLocalRotation(float4{ 0.f , AngleY, Angle });

	
}






#include "PreCompile.h"
#include "PlayerFireEff.h"
#include "BillboardRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"

PlayerFireEff::PlayerFireEff()
{
}

PlayerFireEff::~PlayerFireEff()
{
}

void PlayerFireEff::Start()
{

	m_fSpeed = 800.f;



	float G = GameEngineRandom::MainRandom.RandomFloat(0.f, 216.f) / 255.f;
	float A = GameEngineRandom::MainRandom.RandomFloat(700.f, 1000.f) / 1000.f;


	float4 color = { 0.01f ,G,255.f,A };
	sptrTestPicture = CreateComponent<BillboardRenderer>();
	sptrTestPicture->SetTexture("ripple_alpha.png");
	sptrTestPicture->GetTransform().SetLocalScale({ 100.f, 100.f, 1 });
	//sptrTestPicture->SetPivot(PIVOTMODE::LEFT);
	sptrTestPicture->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	sptrTestPicture->ChangeCamera(CAMERAORDER::MAINCAMERA);
	sptrTestPicture->GetPixelData().MulColor = color;
	sptrTestPicture->SetBillboardInfo(1);


	//Death(1.f);
}

void PlayerFireEff::Update(float _DeltaTime)
{



	float4 MyScale = GetTransform().GetWorldScale();

	
	MyScale.x -= 1000.f * _DeltaTime;
	MyScale.y -= 1000.f * _DeltaTime;

	if (0.f >= MyScale.y)
	{
		Death();
	}


	GetTransform().SetWorldScale(MyScale);


	GetTransform().SetWorldMove(GetTransform().GetUpVector() * _DeltaTime * m_fSpeed);





}

//-436  218  43
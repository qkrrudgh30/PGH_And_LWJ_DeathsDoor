
#include "PreCompile.h"
#include "OldCrowFeather.h"
#include "BillboardRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"

OldCrowFeather::OldCrowFeather()
{
}

OldCrowFeather::~OldCrowFeather()
{
}

void OldCrowFeather::Start()
{


	//255	228
	//255	94


	m_fSpeed = 100.f;




	float4 color = { 0.1f ,0.f,0.f,1.f };
	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("fireparticle.png");
	TexRenderer->GetTransform().SetLocalScale({ 10.f, 50.f, 1 });
	TexRenderer->GetPixelData().MulColor = color;
	TexRenderer->RenderOptionInst.Temp1 = 15;





	m_fGoDir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
	m_fGoDir.y = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
	m_fGoDir.z = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);




	//Death(1.f);
}

void OldCrowFeather::Update(float _DeltaTime)
{

	if (!StartCheck)
		return;

	m_fTime += _DeltaTime;;

	if (m_fTime > 1.2f)
	{
		m_fTime -= 1.2f;



		m_fGoDir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
		m_fGoDir.y = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
		m_fGoDir.z = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);




		GetTransform().SetWorldPosition(m_fStartPos);

	}



	m_fSpeed = GameEngineRandom::MainRandom.RandomFloat(200.f, 500.f);

	float fRotSpeedx = GameEngineRandom::MainRandom.RandomFloat(300.f, 500.f);
	float fRotSpeedy = GameEngineRandom::MainRandom.RandomFloat(300.f, 500.f);
	float fRotSpeedz = GameEngineRandom::MainRandom.RandomFloat(300.f, 500.f);

	float4 MyRot = GetTransform().GetLocalRotation();

	
	MyRot.x -= fRotSpeedx * _DeltaTime;
	MyRot.y -= fRotSpeedy * _DeltaTime;
	MyRot.z -= fRotSpeedz * _DeltaTime;
	

	GetTransform().SetLocalRotation(MyRot);
	GetTransform().SetWorldMove(m_fGoDir * _DeltaTime * m_fSpeed);





}

//-436  218  43


#include "PreCompile.h"
#include "ArrowEff.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "BillboardRenderer.h"


ArrowEff::ArrowEff()
{
}

ArrowEff::~ArrowEff()
{
}

void ArrowEff::Start()
{

	m_fSpeed = 800.f;


	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("Soft.png");
	TexRenderer->GetTransform().SetLocalScale({ 10.f, 10.f, 1 });
	//sptrTestPicture->SetPivot(PIVOTMODE::LEFT);
	TexRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	TexRenderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
	

	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 10.f, 500.0f, 10.0f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);



	//Death(1.f);
}

void ArrowEff::Update(float _DeltaTime)
{



	float4 MyScale = TexRenderer->GetTransform().GetLocalScale();

	if(m_bScalecheck)
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


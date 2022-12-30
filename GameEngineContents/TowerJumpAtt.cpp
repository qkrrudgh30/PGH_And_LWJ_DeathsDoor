
#include "PreCompile.h"
#include "TowerJumpAtt.h"

TowerJumpAtt::TowerJumpAtt()
{
}

TowerJumpAtt::~TowerJumpAtt()
{
}

void TowerJumpAtt::Start()
{

	{
		//float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("iridecent.png");
		TexRenderer->SetRenderingOrder(10);
		TexRenderer->GetPixelData().MulColor.a = 0.3f;
		TexRenderer->GetTransform().SetLocalScale({ 500.f, 500.f, 10.f });
		TexRenderer->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
		//TexRenderer->GetPixelData().MulColor = color;
		TexRenderer->RenderOptionInst.Temp1 = 10;

	}
	m_fSpeed = 100.f;

	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 2000.f, 400.0f, 100.f });
	AttCollision->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);


	Death(3.f);


}

void TowerJumpAtt::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime * 40000.f;

	TexRenderer->GetTransform().SetLocalScale({ m_fSpeed, m_fSpeed, 10.f });

	AttCollision->GetTransform().SetWorldBackMove(40000.f,_DeltaTime);


	//if (m_fSpeed >= 2000.f)




}


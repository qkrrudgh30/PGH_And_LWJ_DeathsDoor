
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
		TexRenderer->GetTransform().SetLocalScale({ 500.f, 500.f, 10.f });
		TexRenderer->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
		//TexRenderer->GetPixelData().MulColor = color;
		TexRenderer->RenderOptionInst.Temp1 = 10;

	}
	m_fSpeed = 100.f;


	Death(3.f);


}

void TowerJumpAtt::Update(float _DeltaTime)
{
	m_fSpeed += _DeltaTime * 40000.f;

	TexRenderer->GetTransform().SetLocalScale({ m_fSpeed, m_fSpeed, 10.f });

	//if (m_fSpeed >= 2000.f)




}


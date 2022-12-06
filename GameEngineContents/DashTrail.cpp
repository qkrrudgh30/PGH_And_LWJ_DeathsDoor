
#include "PreCompile.h"
#include "DashTrail.h"
#include "DashBullet.h"
#include "OldCrow.h"

DashTrail::DashTrail() :
	m_cHook()
{
}

DashTrail::~DashTrail()
{
}

void DashTrail::Start()
{



	{
		float4 color = { 0.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("chain.png");
		TexRenderer->GetTransform().SetLocalScale({ 50.f, 100.0f, 10.f });
		TexRenderer->GetTransform().SetLocalRotation({ -90.f,90.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}




	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 500.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerHookTrail);



}

void DashTrail::Update(float _DeltaTime)
{

	//if (m_OldCorw.lock()->DashStartCheck == true)
	{
		float4 Dir = m_OldCorw.lock()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

		float Len = Dir.Length();

		if (Len <= 250.f)
		{
			m_cHook.reset();
			m_OldCorw.reset();

			Death();
		}

	}







}

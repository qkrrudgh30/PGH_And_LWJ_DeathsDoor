

#include "PreCompile.h"
#include "PlayerHookTrail.h"
#include "PlayerHookAtt.h"


PlayerHookTrail::PlayerHookTrail()	:
	m_cHook()
{
}

PlayerHookTrail::~PlayerHookTrail()
{
}

void PlayerHookTrail::Start()
{



	{
		float4 color = {1.f,0.f,0.f,1.f};

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

void PlayerHookTrail::Update(float _DeltaTime)
{

	if (Player::GetMainPlayer()->m_bHookHitcheck == true)
	{
		float4 Dir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

		float Len = Dir.Length();

		if (Len <= 70.f)
		{
			Death();
		}

	}



	if (m_cHook.lock()->m_bHookBack == true)
	{
		float4 Dir = m_cHook.lock()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

		float Len = Dir.Length();

		if (Len <= 70.f)
		{
			Death();
		}


	}




}

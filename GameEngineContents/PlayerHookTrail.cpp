

#include "PreCompile.h"
#include "PlayerHookTrail.h"
#include "PlayerHookAtt.h"


PlayerHookTrail::PlayerHookTrail()
{
}

PlayerHookTrail::~PlayerHookTrail()
{
}

void PlayerHookTrail::Start()
{



	{

		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,1.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 20.f, 20.0f, 50.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}




	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 20.0f, 50.0f });
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

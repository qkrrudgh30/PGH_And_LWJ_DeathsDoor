
#include "PreCompile.h"
#include "PlayerHookAtt.h"
#include "PlayerHookTrail.h"

PlayerHookAtt::PlayerHookAtt()
{
}

PlayerHookAtt::~PlayerHookAtt()
{
}

void PlayerHookAtt::Start()
{

	m_fSpeed = 2000.f;


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
	AttCollision->ChangeOrder(OBJECTORDER::PlayerHook);



}

void PlayerHookAtt::Update(float _DeltaTime)
{


	if (m_bHitCheck)
	{

		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
			std::bind(&PlayerHookAtt::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
		);


		return;

	}



	float4 MoveDir = Renderer->GetTransform().GetForwardVector();


	m_fLifeTime += _DeltaTime;
	m_ftrailTime += _DeltaTime;


	if (m_fLifeTime >= 0.5f)
	{
		MoveDir = MoveDir * -1.f;

		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
			std::bind(&PlayerHookAtt::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
		);


		m_bHookBack = true;




		if (m_fLifeTime >= 1.3f)
		{
			Death();
		}
	}
	else
	{
		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
			std::bind(&PlayerHookAtt::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
		);

		if (m_ftrailTime >= 0.1f)
		{
			PlayerHookTrail* HookTrail = GetLevel()->CreateActor<PlayerHookTrail>(OBJECTORDER::PlayerHookTrail);
			HookTrail->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			HookTrail->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());
			HookTrail->m_cHook = this;
		}


	}
	

	
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);




}

CollisionReturn PlayerHookAtt::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	Player::GetMainPlayer()->m_bHookHitcheck = true;
	m_bHitCheck = true;
	Player::GetMainPlayer()->m_fHookPoint = GetTransform().GetWorldPosition();


	return CollisionReturn::Break;
}

CollisionReturn PlayerHookAtt::PlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	Death();
	Player::GetMainPlayer()->m_bHookEndcheck = true;

	return CollisionReturn::Break;
}

CollisionReturn PlayerHookAtt::TrailCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	_Other->GetParent()->Death();


	return CollisionReturn::Break;
}


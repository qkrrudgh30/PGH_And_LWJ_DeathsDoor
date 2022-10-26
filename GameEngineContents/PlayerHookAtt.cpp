
#include "PreCompile.h"
#include "PlayerHookAtt.h"

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






	float4 MoveDir = Renderer->GetTransform().GetForwardVector();


	m_fLifeTime += _DeltaTime;

	if (m_fLifeTime >= 0.5f)
	{
		MoveDir = MoveDir * -1.f;

		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
			std::bind(&PlayerHookAtt::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
		);

		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::PlayerHookTrail, CollisionType::CT_OBB,
			std::bind(&PlayerHookAtt::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
		);

	}
	else
	{
		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
			std::bind(&PlayerHookAtt::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
		);

	}
	

	
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);




}

CollisionReturn PlayerHookAtt::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{


//	dynamic_cast<UnitBase*>(_Other->GetParent())->m_bHitCheck = true;
	

	
	return CollisionReturn::Break;
}

CollisionReturn PlayerHookAtt::PlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn();
}

CollisionReturn PlayerHookAtt::TrailCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn();
}



#include "PreCompile.h"
#include "PlayerArrowAtt.h"

PlayerArrowAtt::PlayerArrowAtt() 
{
}

PlayerArrowAtt::~PlayerArrowAtt()
{
}

void PlayerArrowAtt::Start()
{

	m_fSpeed = 3000.f;


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
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);



}

void PlayerArrowAtt::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;

	if (m_fLifeTime >= 2.f)
	{
		Death();
	}


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		std::bind(&PlayerArrowAtt::MonsterCollision, std::dynamic_pointer_cast<PlayerArrowAtt>(shared_from_this()), std::placeholders::_1, std::placeholders::_2)
	);



	float4 MoveDir = Renderer->GetTransform().GetForwardVector();
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);

}

CollisionReturn PlayerArrowAtt::MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_bHitCheck = true;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_fHitPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();


	Death();
	return CollisionReturn::Break;
}


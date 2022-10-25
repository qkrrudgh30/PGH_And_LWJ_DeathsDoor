#include "PreCompile.h"
#include "PlayerSWAtt3.h"

PlayerSWAtt3::PlayerSWAtt3()
{
}

PlayerSWAtt3::~PlayerSWAtt3()
{
}

void PlayerSWAtt3::Start()
{

	m_Info.Dammage = 2;
	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 150.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);
	{


		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,1.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 150.0f, 50.0f, 50.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}


}

void PlayerSWAtt3::Update(float _DeltaTime)
{

	//AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
	//	std::bind(&PlayerSWAtt3::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);



	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Monster), CollisionType::CT_OBB,
		std::bind(&PlayerSWAtt3::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	);

	


}

CollisionReturn PlayerSWAtt3::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	dynamic_cast<UnitBase*>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;
	dynamic_cast<UnitBase*>(_Other->GetParent())->m_bHitCheck = true;
	dynamic_cast<UnitBase*>(_Other->GetParent())->m_fHitPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();


	return CollisionReturn::Break;

}


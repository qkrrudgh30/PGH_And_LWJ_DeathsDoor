#include "PreCompile.h"
#include "PlayerSWAtt1.h"

PlayerSWAtt1::PlayerSWAtt1() 
{
}

PlayerSWAtt1::~PlayerSWAtt1() 
{
}

void PlayerSWAtt1::Start()
{
	m_Info.Dammage = 1;

	{


		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,1.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 50.0f, 50.0f, 50.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}





	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);


}

void PlayerSWAtt1::Update(float _DeltaTime)
{

	//AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
	//	std::bind(&PlayerSWAtt1::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);

	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB,static_cast<int>(OBJECTORDER::Monster), CollisionType::CT_OBB,
		std::bind(&PlayerSWAtt1::MonsterCollision, std::dynamic_pointer_cast<PlayerSWAtt1>(shared_from_this()), std::placeholders::_1, std::placeholders::_2)
	);



}

CollisionReturn PlayerSWAtt1::MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{


	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;


	return CollisionReturn::Break;
	
}


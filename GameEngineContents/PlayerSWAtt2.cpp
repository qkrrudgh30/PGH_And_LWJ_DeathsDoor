#include "PreCompile.h"
#include "PlayerSWAtt2.h"

PlayerSWAtt2::PlayerSWAtt2()
{
}

PlayerSWAtt2::~PlayerSWAtt2()
{
}

void PlayerSWAtt2::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 100.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	

	{


		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,1.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 100.0f, 50.0f, 50.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}




}

void PlayerSWAtt2::Update(float _DeltaTime)
{

	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		std::bind(&PlayerSWAtt2::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	);


}

CollisionReturn PlayerSWAtt2::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	dynamic_cast<UnitBase*>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;


	return CollisionReturn::Break;
}


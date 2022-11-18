

#include "PreCompile.h"
#include "FlowerBullet.h"

FlowerBullet::FlowerBullet()
{
}

FlowerBullet::~FlowerBullet()
{
}

void FlowerBullet::Start()
{

	m_fSpeed = 1000.f;


	{


		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,1.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 20.f, 20.0f, 50.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}




	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 500.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);



}

void FlowerBullet::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;

	if (m_fLifeTime >= 4.f)
	{
		Death();
	}


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&FlowerBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



	float4 MoveDir = Renderer->GetTransform().GetForwardVector();
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);

}

CollisionReturn FlowerBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	Player*  NewPlayer = Player::GetMainPlayer();

	NewPlayer->m_Info.m_Hp -= 1;


	Death();
	return CollisionReturn::Break;
}


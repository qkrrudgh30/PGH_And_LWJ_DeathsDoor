#include "PreCompile.h"
#include "PlayerSWAttSlide.h"

PlayerSWAttSlide::PlayerSWAttSlide()
{
}

PlayerSWAttSlide::~PlayerSWAttSlide()
{
}

void PlayerSWAttSlide::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 150.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	
	{


		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,1.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 50.0f, 50.0f, 150.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}


}

void PlayerSWAttSlide::Update(float _DeltaTime)
{



	//AttCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
	//	std::bind(&PlayerSWAttSlide::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);


	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Monster), CollisionType::CT_OBB,
		std::bind(&PlayerSWAttSlide::MonsterCollision, std::dynamic_pointer_cast<PlayerSWAttSlide>(shared_from_this()), std::placeholders::_1, std::placeholders::_2)
	);




}

CollisionReturn PlayerSWAttSlide::MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{


	

	return CollisionReturn::Break;
}


#include "PreCompile.h"
#include "ShopNPC.h"

ShopNPC::ShopNPC() 
{
}

ShopNPC::~ShopNPC() 
{
}

void ShopNPC::Start()
{


	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::NPC);


	{
		 
		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 1.f,0.f,1.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}

}

void ShopNPC::Update(float _DeltaTime)
{

	/*Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Player, CollisionType::CT_OBB2D,
		std::bind(&ShopNPC::CollisionPlayer, this, std::placeholders::_1, std::placeholders::_2)
	);*/


}

CollisionReturn ShopNPC::CollisionPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{






	return CollisionReturn::ContinueCheck;
}


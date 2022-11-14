#include "PreCompile.h"
#include "ShopNPC.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXStaticRenderer.h"

ShopNPC::ShopNPC() 
{
}

ShopNPC::~ShopNPC() 
{
}

void ShopNPC::Start()
{


	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 300.0f, 300.0f, 300.0f });
	Collision->ChangeOrder(OBJECTORDER::NPC);


	//{
	//	 
	//	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//	Renderer->SetPipeLine("Color");
	//	Renderer->GetRenderUnit().SetMesh("Box");
	//	float4 ResultColor = { 1.f,0.f,1.f,1.f };

	//	Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
	//	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	//}
	{
		//GameEngineFBXStaticRenderer* temp = CreateComponent<GameEngineFBXStaticRenderer>();
		//temp->GetTransform().SetLocalPosition(float4{ 200.f, 0.f, -800.f });
		//temp->GetTransform().SetLocalScale(float4{ 50.f, 50.f, 50.f });
		//temp->GetTransform().SetLocalRotation(float4{ 0.f, 45.f, 0.f });


		//for (int i = 0; i < 6; ++i)
		//{
		//	if (i == 5)
		//	{
		//		// temp->SetFBXMesh("Banker.FBX", "Color", i);
		//		continue;
		//	}
		//	temp->SetFBXMesh("Banker.FBX", "TextureAnimation", i);
		//}

		//temp->CreateFBXAnimation("Idle", "Banker_Idle");
		//temp->ChangeAnimation("Idle");
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


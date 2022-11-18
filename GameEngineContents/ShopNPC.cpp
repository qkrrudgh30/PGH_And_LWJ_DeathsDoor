#include "PreCompile.h"
#include "ShopNPC.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

ShopNPC::ShopNPC() 
{
}

ShopNPC::~ShopNPC() 
{
}

void ShopNPC::Start()
{


	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 300.0f, 500.0f, 300.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	Collision->ChangeOrder(OBJECTORDER::NPC);


	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 50.f, 50.f, 50.f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ -90.f, 180.f,0.f });
	FBXAnimationRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 100.f,0.f });
	FBXAnimationRenderer->SetFBXMesh("banker.fbx", "TextureAnimation");


	Event.ResourcesName = "banker_S_R.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_S_R", Event);



	Event.ResourcesName = "banker_W_P.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_W_P", Event);



	Event.ResourcesName = "banker_W_R.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_W_R", Event);



	Event.ResourcesName = "banker_WStart.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_WStart", Event);




	FBXAnimationRenderer->ChangeAnimation("banker_W_R");
	
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


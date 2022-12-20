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
	FBXAnimationRenderer->SetFBXMesh("banker.fbx", "DeferredTextureAnimation");


	Event.ResourcesName = "banker_S_R.FBX";
	Event.Loop = true;
	Event.Inter = 0.025f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_S_R", Event);



	Event.ResourcesName = "banker_W_P.FBX";
	Event.Loop = true;
	Event.Inter = 0.025f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_W_P", Event);
	FBXAnimationRenderer->AnimationBindEnd("banker_W_P", std::bind(&ShopNPC::Ani_I, this, std::placeholders::_1));



	Event.ResourcesName = "banker_W_R.FBX";
	Event.Loop = true;
	Event.Inter = 0.025f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_W_R", Event);



	Event.ResourcesName = "banker_WStart.FBX";
	Event.Loop = true;
	Event.Inter = 0.025f;
	FBXAnimationRenderer->CreateFBXAnimation("banker_WStart", Event);
	FBXAnimationRenderer->AnimationBindEnd("banker_WStart", std::bind(&ShopNPC::Ani_W, this, std::placeholders::_1));





	StateManager.CreateStateMember("Write"
		, std::bind(&ShopNPC::WriteUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ShopNPC::WriteStart, this, std::placeholders::_1)
		, std::bind(&ShopNPC::WriteEnd, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Idle"
		, std::bind(&ShopNPC::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ShopNPC::IdleStart, this, std::placeholders::_1)
		, std::bind(&ShopNPC::IdleEnd, this, std::placeholders::_1)
	);



	FBXAnimationRenderer->ChangeAnimation("banker_W_R");
	StateManager.ChangeState("Write");
}
void ShopNPC::Ani_W(const GameEngineRenderingEvent& _Data)
{
	FBXAnimationRenderer->ChangeAnimation("banker_W_R");
}
void ShopNPC::Ani_I(const GameEngineRenderingEvent& _Data)
{
	FBXAnimationRenderer->ChangeAnimation("banker_S_R");
}
void ShopNPC::Update(float _DeltaTime)
{

	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

	float4 MyPos = GetTransform().GetWorldPosition();


	float Len = (PlayerPos - MyPos).Length();

	if (Len <= 500.f)
	{
		if (StateManager.GetCurStateStateName() == "Write")
		{
			StateManager.ChangeState("Idle");


		}
	}
	else
	{
		
		if (StateManager.GetCurStateStateName() == "Idle")
		{
				StateManager.ChangeState("Write");
		}
	}


}
void ShopNPC::WriteStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("banker_WStart");
}
void ShopNPC::WriteEnd(const StateInfo& _Info)
{

}
void ShopNPC::WriteUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


void ShopNPC::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("banker_W_P");
}
void ShopNPC::IdleEnd(const StateInfo& _Info)
{

}
void ShopNPC::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

CollisionReturn ShopNPC::CollisionPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	



	return CollisionReturn::ContinueCheck;
}


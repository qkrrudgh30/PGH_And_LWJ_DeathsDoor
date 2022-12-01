
#include "PreCompile.h"
#include "OldCrow.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

OldCrow::OldCrow() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

OldCrow::~OldCrow()
{
}

void OldCrow::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;


	GetTransform().SetLocalRotation({0.f,180.f,0.f});
	GetTransform().SetWorldPosition({0.f,0.f,500.f});


	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("OldCrow.fbx", "TextureAnimation");


	Event.ResourcesName = "OldCrow_Run.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Run", Event);


	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 60.f, 60.f, 60.f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ 90.f, 0.f,0.f });

	FBXAnimationRenderer->ChangeAnimation("OldCrow_Run");






	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);

	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&OldCrow::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&OldCrow::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::MoveStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::MoveEnd, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Stun"
		, std::bind(&OldCrow::StunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::StunStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::StunEnd, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&OldCrow::AttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::AttStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::AttEnd, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void OldCrow::Update(float _DeltaTime)
{








	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

	StateManager.Update(_DeltaTime);

}






void OldCrow::MoveStart(const StateInfo& _Info)
{

}
void OldCrow::MoveEnd(const StateInfo& _Info)
{

}
void OldCrow::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{



}



void OldCrow::StunStart(const StateInfo& _Info)
{
}
void OldCrow::StunEnd(const StateInfo& _Info)
{



}
void OldCrow::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{




}






void OldCrow::AttStart(const StateInfo& _Info)
{
	
}
void OldCrow::AttEnd(const StateInfo& _Info)
{
	
}
void OldCrow::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{

}




void OldCrow::IdleStart(const StateInfo& _Info)
{

}
void OldCrow::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{


}

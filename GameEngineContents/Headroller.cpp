
#include "PreCompile.h"
#include "Headroller.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

Headroller::Headroller() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

Headroller::~Headroller()
{
}

void Headroller::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;



	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("HEADROLLER.fbx", "TextureAnimation");
	FBXAnimationRenderer->GetTransform().SetLocalScale({0.5f,0.5f,.5f});


	Event.ResourcesName = "HEADROLLER_Att.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Att", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Att", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));




	Event.ResourcesName = "HEADROLLER_Att2.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Att2", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Att2", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));


	Event.ResourcesName = "HEADROLLER_Dash.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Dash", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Dash", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Dash_E.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Dash_E", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Dash_E", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Dash_S.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Dash_S", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Dash_S", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Death.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Death", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Death", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Idle", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Idle", std::bind(&Headroller::AniSlime_Att, this, std::placeholders::_1));




	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Att");





	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);

	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&Headroller::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Headroller::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&Headroller::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Headroller::MoveStart, this, std::placeholders::_1)
		, std::bind(&Headroller::MoveEnd, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Stun"
		, std::bind(&Headroller::StunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Headroller::StunStart, this, std::placeholders::_1)
		, std::bind(&Headroller::StunEnd, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&Headroller::AttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Headroller::AttStart, this, std::placeholders::_1)
		, std::bind(&Headroller::AttEnd, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void Headroller::Update(float _DeltaTime)
{



	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

	StateManager.Update(_DeltaTime);

}






void Headroller::MoveStart(const StateInfo& _Info)
{
//	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Att");
}
void Headroller::MoveEnd(const StateInfo& _Info)
{

}
void Headroller::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{


	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}


	float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	float4 TarGetDirAngle = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	float Len = TarGetDir.Length();
	TarGetDir = TarGetDir.Normalize3DReturn();




	//각도 수정

	float4 MyPos = GetTransform().GetWorldPosition();

	TarGetDirAngle.y = -TarGetDirAngle.z;
	MyPos.y = -MyPos.z;


	TarGetDirAngle.z = 0.f;
	TarGetDirAngle.w = 0.f;

	MyPos.z = 0.f;
	MyPos.w = 0.f;

	float Angle = float4::VectorXYtoDegree(MyPos, TarGetDirAngle);

	Angle += 90.f;

	if (Angle >= 360.f)
	{
		Angle -= 360.f;
	}
	else if (Angle <= 0.f)
	{
		Angle -= 0.f;
	}

	FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });





	GetTransform().SetWorldMove(TarGetDir * m_fSpeed * _DeltaTime);


	if (Len <= 150.f)
	{
		StateManager.ChangeState("Att");
	}
	else if (Len >= 600.f)
	{
		StateManager.ChangeState("Idle");
	}






}



void Headroller::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void Headroller::StunEnd(const StateInfo& _Info)
{



}
void Headroller::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{

	hitTime += _DeltaTime;

	if (hitTime <= 0.2f)
	{
		//	hitTime = 0.f;
		GetTransform().SetWorldMove(m_fHitDir * 500.f * _DeltaTime);
		//	StateManager.ChangeState("Idle");
	}
	else if (hitTime >= 0.5f)
	{
		hitTime = 0.f;
		StateManager.ChangeState("Idle");
	}






}






void Headroller::AttStart(const StateInfo& _Info)
{

	//FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Att");

	m_bhitCheck = true;
}
void Headroller::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;
}
void Headroller::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{



	//삭제 예정
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}

}

void Headroller::AniSlime_Att(const GameEngineRenderingEvent& _Data)
{


	StateManager.ChangeState("Idle");



}

void Headroller::AniSlime_Idle(const GameEngineRenderingEvent& _Data)
{
}

void Headroller::AniSlime_Move(const GameEngineRenderingEvent& _Data)
{
}




void Headroller::IdleStart(const StateInfo& _Info)
{
	//FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Att");
}
void Headroller::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}





	float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

	float Len = TarGetDir.Length();
	TarGetDir = TarGetDir.Normalize3DReturn();


	if (Len <= 600.f)
	{
		StateManager.ChangeState("Move");
	}



}

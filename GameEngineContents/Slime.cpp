#include "PreCompile.h"
#include "Slime.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

Slime::Slime() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

Slime::~Slime()
{
}

void Slime::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;
	
	

	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("Slime.fbx", "TextureAnimation");


	Event.ResourcesName = "Slime_Att.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("Slime_Att", Event);
	FBXAnimationRenderer->AnimationBindEnd("Slime_Att", std::bind(&Slime::AniSlime_Att, this, Event));


	Event.ResourcesName = "Slime_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("Slime_Idle", Event);
	FBXAnimationRenderer->AnimationBindEnd("Slime_Idle", std::bind(&Slime::AniSlime_Idle, this, Event));



	Event.ResourcesName = "Slime_Move.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("Slime_Move", Event);
	FBXAnimationRenderer->AnimationBindEnd("Slime_Move", std::bind(&Slime::AniSlime_Move, this, Event));





	FBXAnimationRenderer->ChangeAnimation("Slime_Idle");





	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	
	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&Slime::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Slime::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&Slime::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Slime::MoveStart, this, std::placeholders::_1)
		, std::bind(&Slime::MoveEnd, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Stun"
		, std::bind(&Slime::StunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Slime::StunStart, this, std::placeholders::_1)
		, std::bind(&Slime::StunEnd, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&Slime::AttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Slime::AttStart, this, std::placeholders::_1)
		, std::bind(&Slime::AttEnd, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void Slime::Update(float _DeltaTime) 
{

	

	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

	StateManager.Update(_DeltaTime);

}






void Slime::MoveStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Slime_Idle");
}
void Slime::MoveEnd(const StateInfo& _Info)
{

}
void Slime::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
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



void Slime::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void Slime::StunEnd(const StateInfo& _Info)
{

	

}
void Slime::StunUpdate(float _DeltaTime, const StateInfo& _Info)
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
	 





void Slime::AttStart(const StateInfo& _Info)
{

	FBXAnimationRenderer->ChangeAnimation("Slime_Att");

	m_bhitCheck = true;
}
void Slime::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;
}
void Slime::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	


	//삭제 예정
	//if (m_bHitCheck)
	//{
	//	StateManager.ChangeState("Stun");
	//	m_bHitCheck = false;
	//}

}

void Slime::AniSlime_Att(const GameEngineRenderingEvent& _Data)
{
	

		StateManager.ChangeState("Idle");



}

void Slime::AniSlime_Idle(const GameEngineRenderingEvent& _Data)
{
}

void Slime::AniSlime_Move(const GameEngineRenderingEvent& _Data)
{
}




void Slime::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Slime_Idle");
}
void Slime::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
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

#include "PreCompile.h"
#include "HeadRoller.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

HeadRoller::HeadRoller() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

HeadRoller::~HeadRoller()
{
}

void HeadRoller::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;
	



	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("HEADROLLER.fbx", "TextureAnimation");


	Event.ResourcesName = "HEADROLLER_Roll.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Roll", Event);


	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 100.f, 100.f, 100.f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ -90.f, 0.f,0.f });

	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Roll");






	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	
	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&HeadRoller::IdleUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeadRoller::IdleStart,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&HeadRoller::MoveUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeadRoller::MoveStart,this, std::placeholders::_1)
		, std::bind(&HeadRoller::MoveEnd,this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Stun"
		, std::bind(&HeadRoller::StunUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeadRoller::StunStart,this, std::placeholders::_1)
		, std::bind(&HeadRoller::StunEnd,this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&HeadRoller::AttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeadRoller::AttStart,this, std::placeholders::_1)
		, std::bind(&HeadRoller::AttEnd,this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void HeadRoller::Update(float _DeltaTime)
{

	






	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

	StateManager.Update(_DeltaTime);

}






void HeadRoller::MoveStart(const StateInfo& _Info)
{

}
void HeadRoller::MoveEnd(const StateInfo& _Info)
{

}
void HeadRoller::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
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
	GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });





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



void HeadRoller::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void HeadRoller::StunEnd(const StateInfo& _Info)
{

	

}
void HeadRoller::StunUpdate(float _DeltaTime, const StateInfo& _Info)
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
	 





void HeadRoller::AttStart(const StateInfo& _Info)
{
	m_bhitCheck = true;
}
void HeadRoller::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;
}
void HeadRoller::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fHitTime += _DeltaTime;

	if (m_fHitTime >= 1.f)
	{
		m_fHitTime = 0.f;
		StateManager.ChangeState("Idle");

	}


	//삭제 예정
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}

}




void HeadRoller::IdleStart(const StateInfo& _Info)
{

}
void HeadRoller::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
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

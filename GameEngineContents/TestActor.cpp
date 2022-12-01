#include "PreCompile.h"
#include "TestActor.h"
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>


TestActor::TestActor()
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;

	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("Slime.fbx", "TextureAnimation");
	FBXAnimationRenderer->GetTransform().SetLocalMove(float4{0.f, 120.f, 0.f, 0.f});
	

	Event.ResourcesName = "Slime_Att.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("TestActor_Att", Event);
	FBXAnimationRenderer->AnimationBindEnd("TestActor_Att", std::bind(&TestActor::AniTestActor_Att, this, std::placeholders::_1));

	Event.ResourcesName = "Slime_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("TestActor_Idle", Event);
	FBXAnimationRenderer->AnimationBindEnd("TestActor_Idle", std::bind(&TestActor::AniTestActor_Idle, this, std::placeholders::_1));

	Event.ResourcesName = "Slime_Move.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("TestActor_Move", Event);
	FBXAnimationRenderer->AnimationBindEnd("TestActor_Move", std::bind(&TestActor::AniTestActor_Move, this, std::placeholders::_1));

	FBXAnimationRenderer->ChangeAnimation("TestActor_Idle");
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::Monster);

	StateManager.CreateStateMember("Idle"
		, std::bind(&TestActor::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TestActor::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&TestActor::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TestActor::MoveStart, this, std::placeholders::_1)
		, std::bind(&TestActor::MoveEnd, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Stun"
		, std::bind(&TestActor::StunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TestActor::StunStart, this, std::placeholders::_1)
		, std::bind(&TestActor::StunEnd, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Att"
		, std::bind(&TestActor::AttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TestActor::AttStart, this, std::placeholders::_1)
		, std::bind(&TestActor::AttEnd, this, std::placeholders::_1)
	);

	StateManager.ChangeState("Idle");
}

void TestActor::Update(float _DeltaTime)
{
	static bool bOnce = false, bOnDeath = false;

	StateManager.Update(_DeltaTime);
}

void TestActor::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("TestActor_Idle");
}

void TestActor::IdleStart(const StateInfo& _Info)
{
	if (m_bhitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bhitCheck = false;
	}

	float4 TargetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

	float Len = TargetDir.Length();
	TargetDir = TargetDir.Normalize3DReturn();

	if (Len <= 600.f)
	{
		StateManager.ChangeState("Move");
	}
}

void TestActor::MoveStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("TestActor_Idle");
}

void TestActor::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
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

void TestActor::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}

void TestActor::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	hitTime += _DeltaTime;

	if (hitTime <= 0.2f)
	{
		GetTransform().SetWorldMove(m_fHitDir * 500.f * _DeltaTime);
	}
	else if (hitTime >= 0.5f)
	{
		hitTime = 0.f;
		StateManager.ChangeState("Idle");
	}
}

void TestActor::AttStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("TestActor_Att");

	m_bhitCheck = true;
}

void TestActor::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;
}

void TestActor::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (m_bhitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}
}

void TestActor::AniTestActor_Att(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Idle");
}


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
	m_fSpeed = 600.f;



	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("HEADROLLER.fbx", "PaperBurn");
	FBXAnimationRenderer->GetTransform().SetLocalScale({0.5f,0.5f,.5f});

#pragma region PaperBurn

	InitializePaperBurn(FBXAnimationRenderer);
	m_fAccTimeForPaperburn = 0.f;
	mfPaperburnDeathTime = 4.f;

#pragma endregion

	Event.ResourcesName = "HEADROLLER_Att.FBX";
	Event.Loop = false;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Att", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Att", std::bind(&Headroller::Ani_Att, this, std::placeholders::_1));




	Event.ResourcesName = "HEADROLLER_Att2.FBX";
	Event.Loop = false;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Att2", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Att2", std::bind(&Headroller::Ani_Att2, this, std::placeholders::_1));


	Event.ResourcesName = "HEADROLLER_Dash.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Dash", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Dash", std::bind(&Headroller::Ani_Dash, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Dash_E.FBX";
	Event.Loop = false;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Dash_E", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Dash_E", std::bind(&Headroller::Ani_Dash_E, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Dash_S.FBX";
	Event.Loop = false;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Dash_S", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Dash_S", std::bind(&Headroller::Ani_Dash_S, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Death.FBX";
	Event.Loop = false;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Death", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Death", std::bind(&Headroller::Ani_Death, this, std::placeholders::_1));

	Event.ResourcesName = "HEADROLLER_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.03f;
	FBXAnimationRenderer->CreateFBXAnimation("HEADROLLER_Idle", Event);
	FBXAnimationRenderer->AnimationBindEnd("HEADROLLER_Idle", std::bind(&Headroller::Ani_Idle, this, std::placeholders::_1));




	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Idle");





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



	StateManager.CreateStateMember("Death"
		, std::bind(&Headroller::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Headroller::DeathStart, this, std::placeholders::_1)
		, std::bind(&Headroller::DeathEnd, this, std::placeholders::_1)
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
		StateManager.ChangeState("Death");
	}
	else
	{

		float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
		float4 TarGetDirAngle = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
		m_Len = TarGetDir.Length();
		TarGetDir = TarGetDir.Normalize3DReturn();




		//각도 수정

		float4 MyPos = GetTransform().GetWorldPosition();

		TarGetDirAngle.y = -TarGetDirAngle.z;
		MyPos.y = -MyPos.z;


		TarGetDirAngle.z = 0.f;
		TarGetDirAngle.w = 0.f;

		MyPos.z = 0.f;
		MyPos.w = 0.f;

		Angle = float4::VectorXYtoDegree(MyPos, TarGetDirAngle);

		Angle += 90.f;

		if (Angle >= 360.f)
		{
			Angle -= 360.f;
		}
		else if (Angle <= 0.f)
		{
			Angle -= 0.f;
		}




		if (m_Len <= 200.f)
		{
			if (m_bAtt)
				StateManager.ChangeState("Att");
		}
		else if (m_Len <= 700.f)
		{
			if (StateManager.GetCurStateStateName() == "Idle")
				StateManager.ChangeState("Move");
		}
		else
		{
			//StateManager.ChangeState("Idle");
		}




	}

	StateManager.Update(_DeltaTime);

#pragma region PaperBurn
	if (m_Info.m_Hp <= 0 && false == mbOnce)
	{
		Death(mfPaperburnDeathTime);
		mbOnce = true;
		mbOnDeath = true;
	}

	if (m_Info.m_Hp <= 0 && true == mbOnDeath && true == m_bDeathEnd)
	{
		m_fAccTimeForPaperburn += _DeltaTime;
		SetPaperBurnInfo(1u, m_fAccTimeForPaperburn);
	}
#pragma endregion

}






void Headroller::MoveStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });
	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Dash_S");
	m_bMove = false;
	m_bAtt = false;
}
void Headroller::MoveEnd(const StateInfo& _Info)
{
	
	m_bMove = false;
}
void Headroller::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (m_bMove)
	{
		//이동
		FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });
		float4 TarGetDir = FBXAnimationRenderer->GetTransform().GetForwardVector();
	
		if (m_Len <= 200.f)
		{
			FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Dash_E");
		}
		else
		{
			GetTransform().SetWorldMove(TarGetDir * m_fSpeed * _DeltaTime);

		}

	}
	

}



void Headroller::DeathStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Death");
}
void Headroller::DeathEnd(const StateInfo& _Info)
{



}
void Headroller::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

	


}






void Headroller::AttStart(const StateInfo& _Info)
{
	m_bAtt = false;
	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Att");
	FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });
}
void Headroller::AttEnd(const StateInfo& _Info)
{
	m_bAtt = true;
}
void Headroller::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{



}





void Headroller::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Idle");

}
void Headroller::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	

}
void Headroller::Ani_Att(const GameEngineRenderingEvent& _Data)
{
	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Att2");

}

void Headroller::Ani_Att2(const GameEngineRenderingEvent& _Data)
{

	StateManager.ChangeState("Idle");
}


void Headroller::Ani_Idle(const GameEngineRenderingEvent& _Data)
{
}


void Headroller::Ani_Dash(const GameEngineRenderingEvent& _Data)
{
}


void Headroller::Ani_Dash_E(const GameEngineRenderingEvent& _Data)
{
	m_bAtt = true;
	StateManager.ChangeState("Idle");
}


void Headroller::Ani_Dash_S(const GameEngineRenderingEvent& _Data)
{
	FBXAnimationRenderer->ChangeAnimation("HEADROLLER_Dash");
	m_bMove = true;
}


void Headroller::Ani_Death(const GameEngineRenderingEvent& _Data)
{
	// Death();
	m_bDeathEnd = true;
}



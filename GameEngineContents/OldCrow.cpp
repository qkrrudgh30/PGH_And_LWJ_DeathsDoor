
#include "PreCompile.h"
#include "OldCrow.h"
#include "Player.h"
#include "UnitBase.h"
#include "OldCrowBullet.h"

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


	m_Info.m_Hp = 10500;
	m_Info.m_MaxHp = 10500;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;


	GetTransform().SetLocalRotation({0.f,180.f,0.f});
	GetTransform().SetWorldPosition({0.f,0.f,500.f});


	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("OldCrow.fbx", "PaperBurn");
	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 90.f, 90.f, 90.f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ 90.f, 0.f,0.f });



#pragma region PaperBurn

	InitializePaperBurn(FBXAnimationRenderer);
	m_fAccTimeForPaperburn = 0.f;
	mfPaperburnDeathTime = 6.0f;

#pragma endregion


	{
		Event.ResourcesName = "OldCrow_Dash.FBX";
		Event.Loop = true;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Dash", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Dash", std::bind(&OldCrow::AniDashEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Dash_Start.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Dash_Start", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Dash_Start", std::bind(&OldCrow::AniDashStartEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Death_Run.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Death_Run", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Death_Run", std::bind(&OldCrow::AniDeathRunEnd, this, std::placeholders::_1));
	

	}

	{
		Event.ResourcesName = "OldCrow_Death_Stand.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Death_Stand", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Death_Stand", std::bind(&OldCrow::AniDeathStandEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Idle.FBX";
		Event.Loop = true;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Idle", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Idle", std::bind(&OldCrow::AniIdleEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Jump_Start.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Jump_Start", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Jump_Start", std::bind(&OldCrow::AniJumpStartEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Run.FBX";
		Event.Loop = true;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Run", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Run", std::bind(&OldCrow::AniRunEnd, this, std::placeholders::_1));
		FBXAnimationRenderer->AnimationBindFrame("OldCrow_Run", std::bind(&OldCrow::AniRunFrame, this, std::placeholders::_1));
	}

	{
		Event.ResourcesName = "OldCrow_Run_S.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Run_S", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Run_S", std::bind(&OldCrow::AniRunStartEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Scream.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Scream", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Scream", std::bind(&OldCrow::AniScreamEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Slam.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Slam", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Slam", std::bind(&OldCrow::AniSlamEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Slam_End.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Slam_End", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Slam_End", std::bind(&OldCrow::AniSlamEndEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Turn_Left.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Turn_Left", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Turn_Left", std::bind(&OldCrow::AniTurnLeftEnd, this, std::placeholders::_1));

	}

	{
		Event.ResourcesName = "OldCrow_Turn_Right.FBX";
		Event.Loop = false;
		Event.Inter = 0.025f;
		FBXAnimationRenderer->CreateFBXAnimation("OldCrow_Turn_Right", Event);
		FBXAnimationRenderer->AnimationBindEnd("OldCrow_Turn_Right", std::bind(&OldCrow::AniTurnRightEnd, this, std::placeholders::_1));

	}


	FBXAnimationRenderer->ChangeAnimation("OldCrow_Idle");






	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 300.0f, 500.0f, 300.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);

	}

	StateManager.CreateStateMember("StartAct"
		, std::bind(&OldCrow::StartActUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::StartActStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::StartActEnd, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Idle"
		, std::bind(&OldCrow::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("MoveReady"
		, std::bind(&OldCrow::MoveReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::MoveReadyStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::MoveReadyEnd, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&OldCrow::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::MoveStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::MoveEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("TurnLeft"
		, std::bind(&OldCrow::TurnLUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::TurnLStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::TurnLEnd, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("TurnRight"
		, std::bind(&OldCrow::TurnRUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::TurnRStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::TurnREnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("DashReady"
		, std::bind(&OldCrow::DashReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::DashReadyStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::DashReadyEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Dash"
		, std::bind(&OldCrow::DashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::DashStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::DashEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Dash2Ready"
		, std::bind(&OldCrow::DashReady2Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::DashReady2Start, this, std::placeholders::_1)
		, std::bind(&OldCrow::DashReady2End, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Dash2"
		, std::bind(&OldCrow::Dash2Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::Dash2Start, this, std::placeholders::_1)
		, std::bind(&OldCrow::Dash2End, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Dash3Ready"
		, std::bind(&OldCrow::DashReady3Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::DashReady3Start, this, std::placeholders::_1)
		, std::bind(&OldCrow::DashReady3End, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Dash3"
		, std::bind(&OldCrow::Dash3Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::Dash3Start, this, std::placeholders::_1)
		, std::bind(&OldCrow::Dash3End, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Jump"
		, std::bind(&OldCrow::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::JumpStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::JumpEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("JumpReady"
		, std::bind(&OldCrow::JumpReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::JumpReadyStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::JumpReadyEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("JumpEnd"
		, std::bind(&OldCrow::JumpEndUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::JumpEndStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::JumpEndEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Scream"
		, std::bind(&OldCrow::ScreamUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::ScreamStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::ScreamEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("DashDeath"
		, std::bind(&OldCrow::DashDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::DashDeathStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::DashDeathEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("StandDeath"
		, std::bind(&OldCrow::StandDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&OldCrow::StandDeathStart, this, std::placeholders::_1)
		, std::bind(&OldCrow::StandDeathEnd, this, std::placeholders::_1)
	);







	StateManager.ChangeState("StartAct");
}

void OldCrow::Update(float _DeltaTime)
{



	BaseUpdate(_DeltaTime);

	//맞을때 이 함수만 추가해 주세요
	HitUpdate(_DeltaTime, 0.5f);


	Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&OldCrow::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



	if (m_Info.m_Hp != m_Info.m_MaxHp)
	{
		m_Info.m_MaxHp = m_Info.m_Hp;
		//타격시 생성

		std::weak_ptr<OldCrowBullet> m_Bullet = GetLevel()->CreateActor<OldCrowBullet>(OBJECTORDER::CrowBullet);
		m_Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());


	}




	if (m_Info.m_Hp <= 0)
	{
		m_bDeathEnd = true;
		StateManager.ChangeState("StandDeath");
	}

	StateManager.Update(_DeltaTime);

#pragma region PaperBurn
	if (m_Info.m_Hp <= 0 && false == mbOnce)
	{
		Death(mfPaperburnDeathTime);
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("33_LastBossDeath.mp3");
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




CollisionReturn OldCrow::PlayerCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{
	Player::GetMainPlayer()->m_bHitBackCheck = true;


	return CollisionReturn::Break;
}

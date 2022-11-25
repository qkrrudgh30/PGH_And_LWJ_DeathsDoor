#include "PreCompile.h"
#include "Tower.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"
#include "Spike.h"
Tower::Tower() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

Tower::~Tower()
{
}

void Tower::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 100.f;
	
	//GetTransform().SetLocalRotation({0.f,-45.f,0.f});
	GetTransform().SetWorldPosition({ 356.f,3000.F,25.f });


	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("Tower.fbx", "TextureAnimation");


	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 0.005f, 0.005f, 0.005f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ 90.f, 225.f,0.f });

	Event.ResourcesName = "Tower_Laser.FBX";
	Event.Loop = true;
	Event.Inter = 0.2f;
	FBXAnimationRenderer->CreateFBXAnimation("Tower_Laser", Event);

	FBXAnimationRenderer->ChangeAnimation("Tower_Laser");

	                                                                                                                                                                     


	{
		StartCollision = CreateComponent<GameEngineCollision>();
		StartCollision->GetTransform().SetLocalScale({ 500.0f, 500.0f, 200.0f });
		StartCollision->GetTransform().SetWorldPosition({-1010.f, 0.f , -1200.f});
		StartCollision->ChangeOrder(OBJECTORDER::Monster);

	}



	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	
	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&Tower::IdleUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::IdleStart,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&Tower::MoveUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::MoveStart,this, std::placeholders::_1)
		, std::bind(&Tower::MoveEnd,this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Stun"
		, std::bind(&Tower::StunUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::StunStart,this, std::placeholders::_1)
		, std::bind(&Tower::StunEnd,this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&Tower::AttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tower::AttStart,this, std::placeholders::_1)
		, std::bind(&Tower::AttEnd,this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void Tower::Update(float _DeltaTime)
{


	if (!m_bstart)
	{
		if (true == StartCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB))
		{

			m_bstart = true;

		}
	}








	if (m_Info.m_Hp <= 0)
	{
		Death();
		m_cSpike.lock()->Death();
	}
	else
	{


	}

	StateManager.Update(_DeltaTime);

}






void Tower::MoveStart(const StateInfo& _Info)
{
	Player::GetMainPlayer()->m_bTowerCameraCheck = true;
	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ -12.f,43.f,0.f });
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({-1185.f,68.f,-1445.f });


}
void Tower::MoveEnd(const StateInfo& _Info)
{

	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	PlayerPos.y +=  1700.f;
	PlayerPos.z -=  1700.f;
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(PlayerPos);




	Player::GetMainPlayer()->m_bTowerCameraCheck = false;
	m_bstart = false;
}
void Tower::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fSpeed += _DeltaTime * 600.f;

	//GetTransform().SetWorldDownMove(m_fSpeed, _DeltaTime);

	float4 MyPos = GetTransform().GetWorldPosition();
	if (MyPos.y <= 0.f)
	{
		MyPos.y = 0.f;
		GetTransform().SetWorldPosition(MyPos);
		

		m_fLifeTime += _DeltaTime;
		if (m_fLifeTime >= 5.f)
		{
			StateManager.ChangeState("Idle");

		}


	}
	else
	{
		GetTransform().SetWorldDownMove(m_fSpeed, _DeltaTime);
	}


}



void Tower::StunStart(const StateInfo& _Info)
{
	//m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	//m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void Tower::StunEnd(const StateInfo& _Info)
{

	

}
void Tower::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{

	//hitTime += _DeltaTime;

	//if (hitTime <= 0.2f)
	//{
	////	hitTime = 0.f;
	//	GetTransform().SetWorldMove(m_fHitDir * 500.f * _DeltaTime);
	////	StateManager.ChangeState("Idle");
	//}
	//else if (hitTime >= 0.5f)
	//{
	//	hitTime = 0.f;
	//	StateManager.ChangeState("Idle");
	//}
	//

	



}
	 





void Tower::AttStart(const StateInfo& _Info)
{
	m_bhitCheck = true;
}
void Tower::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;
}
void Tower::AttUpdate(float _DeltaTime, const StateInfo& _Info)
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




void Tower::IdleStart(const StateInfo& _Info)
{

}
void Tower::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{




	float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

	float Len = TarGetDir.Length();
	TarGetDir = TarGetDir.Normalize3DReturn();


	if (Len <= 2000.f)
	{
		if(StateManager.GetCurStateStateName() != "Move")
			StateManager.ChangeState("Att");
	}
	else
	{
		if (!m_bstart)
		{
			if (true == StartCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB))
			{

				m_bstart = true;

			}
		}

	}

	if (m_bstart)
	{
		StateManager.ChangeState("Move");
	}


}

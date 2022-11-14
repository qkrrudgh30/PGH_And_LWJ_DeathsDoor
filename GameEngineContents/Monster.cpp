#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

Monster::Monster() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;
	


	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();

		{
			FBXStaticRenderer->SetFBXMesh("_E_BAT_White.FBX", "Texture");
		}
		FBXStaticRenderer->GetTransform().SetLocalScale({ 0.25f, 0.25f, 0.25f });
		FBXStaticRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	}







	//{


	//	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//	Renderer->SetPipeLine("Color");
	//	Renderer->GetRenderUnit().SetMesh("Box");
	//	float4 ResultColor = { 0.f,1.f,0.f,1.f };

	//	Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	//	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	//}



	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	
	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&Monster::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Monster::IdleStart, this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&Monster::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Monster::MoveStart, this, std::placeholders::_1)
		, std::bind(&Monster::MoveEnd, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Stun"
		, std::bind(&Monster::StunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Monster::StunStart, this, std::placeholders::_1)
		, std::bind(&Monster::StunEnd, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&Monster::AttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Monster::AttStart, this, std::placeholders::_1)
		, std::bind(&Monster::AttEnd, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void Monster::Update(float _DeltaTime) 
{

	






	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

	StateManager.Update(_DeltaTime);

}






void Monster::MoveStart(const StateInfo& _Info)
{

}
void Monster::MoveEnd(const StateInfo& _Info)
{

}
void Monster::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{


	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}


	float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

	float Len = TarGetDir.Length();
	TarGetDir = TarGetDir.Normalize3DReturn();


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



void Monster::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void Monster::StunEnd(const StateInfo& _Info)
{

	

}
void Monster::StunUpdate(float _DeltaTime, const StateInfo& _Info)
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
	 





void Monster::AttStart(const StateInfo& _Info)
{
	m_bhitCheck = true;
}
void Monster::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;
}
void Monster::AttUpdate(float _DeltaTime, const StateInfo& _Info)
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




void Monster::IdleStart(const StateInfo& _Info)
{

}
void Monster::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
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

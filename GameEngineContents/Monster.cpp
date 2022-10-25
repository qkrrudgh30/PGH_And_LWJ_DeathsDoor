#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

Monster::Monster()
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




	{


		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		float4 ResultColor = { 0.f,1.f,0.f,1.f };

		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	}



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

	StateManager.Update(_DeltaTime);



	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

}






void Monster::MoveStart(const StateInfo& _Info)
{

}
void Monster::MoveEnd(const StateInfo& _Info)
{

}
void Monster::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{

}



void Monster::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.NormalizeReturn();
}
void Monster::StunEnd(const StateInfo& _Info)
{

	

}
void Monster::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{

	hitTime += _DeltaTime;

	if (hitTime >= 0.1f)
	{
		hitTime = 0.f;

		StateManager.ChangeState("Idle");
	}

	GetTransform().SetWorldMove(m_fHitDir * 500.f * _DeltaTime);



}
	 





void Monster::AttStart(const StateInfo& _Info)
{

}
void Monster::AttEnd(const StateInfo& _Info)
{

}
void Monster::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{

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

}

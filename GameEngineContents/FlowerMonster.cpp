

#include "PreCompile.h"
#include "FlowerMonster.h"
#include "Player.h"
#include "FlowerBullet.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>

FlowerMonster::FlowerMonster()	:
	StartPostion()
	, DirPower()
	, Pos()
{
}

FlowerMonster::~FlowerMonster()
{
}

void FlowerMonster::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;



	//{


	//	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//	Renderer->SetPipeLine("Color");
	//	Renderer->GetRenderUnit().SetMesh("Box");
	//	float4 ResultColor = { 0.f,0.f,1.f,1.f };

	//	Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	//	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	//}


	{
		FBXAnimationRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXAnimationRenderer->SetFBXMesh("Flower.FBX", "Texture");
	}
	FBXAnimationRenderer->GetTransform().SetLocalScale({ 0.25f, 0.25f, 0.25f });
	FBXAnimationRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	// Idle_16



	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);

	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&FlowerMonster::IdleUpdate, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::IdleStart, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1)
	);




	StateManager.CreateStateMember("Stun"
		, std::bind(&FlowerMonster::StunUpdate, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::StunStart, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1)
		, std::bind(&FlowerMonster::StunEnd, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&FlowerMonster::AttUpdate, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::AttStart, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1)
		, std::bind(&FlowerMonster::AttEnd, std::dynamic_pointer_cast<FlowerMonster>(shared_from_this()), std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void FlowerMonster::Update(float _DeltaTime)
{



	if (m_Info.m_Hp <= 0)
	{
		Death();
	}

	StateManager.Update(_DeltaTime);

}







void FlowerMonster::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void FlowerMonster::StunEnd(const StateInfo& _Info)
{



}
void FlowerMonster::StunUpdate(float _DeltaTime, const StateInfo& _Info)
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






void FlowerMonster::AttStart(const StateInfo& _Info)
{
	m_bhitCheck = true;
}
void FlowerMonster::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;

	//총알 생성
	std::shared_ptr < FlowerBullet> m_ArrowAtt = GetLevel()->CreateActor<FlowerBullet>(OBJECTORDER::MonsterAtt);
	m_ArrowAtt->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	m_ArrowAtt->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());
	


}
void FlowerMonster::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fHitTime += _DeltaTime;

	if (m_fHitTime >= 2.f)
	{
		m_fHitTime = 0.f;


		float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

		float4 MyPos = GetTransform().GetWorldPosition();

		TarGetDir.y = -TarGetDir.z;
		MyPos.y = -MyPos.z;


		TarGetDir.z = 0.f;
		TarGetDir.w = 0.f;

		MyPos.z = 0.f;
		MyPos.w = 0.f;

		float Angle = float4::VectorXYtoDegree(MyPos, TarGetDir);

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



		StateManager.ChangeState("Idle");

	}


	//삭제 예정
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}


}




void FlowerMonster::IdleStart(const StateInfo& _Info)
{

}
void FlowerMonster::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}




	float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

	float Len = TarGetDir.Length();
	TarGetDir = TarGetDir.Normalize3DReturn();


	
	if (Len <= 1000.f)
	{
		StateManager.ChangeState("Att");
	}



}

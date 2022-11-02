

#include "PreCompile.h"
#include "FlowerMonster.h"
#include "Player.h"
#include "FlowerBullet.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>

FlowerMonster::FlowerMonster()
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
		FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
		
		{
			FBXRenderer->SetFBXMesh("_E_FIREPLANT.FBX", "Texture");
		}
		FBXRenderer->GetTransform().SetLocalScale({ 1.0f, 1.0f, 1.0f });
		FBXRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	}





	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);

	}



	StateManager.CreateStateMember("Idle"
		, std::bind(&FlowerMonster::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::IdleStart, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Stun"
		, std::bind(&FlowerMonster::StunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::StunStart, this, std::placeholders::_1)
		, std::bind(&FlowerMonster::StunEnd, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Att"
		, std::bind(&FlowerMonster::AttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::AttStart, this, std::placeholders::_1)
		, std::bind(&FlowerMonster::AttEnd, this, std::placeholders::_1)
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
	FlowerBullet* m_ArrowAtt = GetLevel()->CreateActor<FlowerBullet>(OBJECTORDER::MonsterAtt);
	m_ArrowAtt->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	m_ArrowAtt->GetTransform().SetLocalRotation(FBXRenderer->GetTransform().GetLocalRotation());
	


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

		FBXRenderer->GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });



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

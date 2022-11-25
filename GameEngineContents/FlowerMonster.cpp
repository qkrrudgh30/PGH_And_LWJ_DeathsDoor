

#include "PreCompile.h"
#include "FlowerMonster.h"
#include "Player.h"
#include "FlowerBullet.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

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


	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ -90.f, 0.f,0.f });

	FBXAnimationRenderer->SetFBXMesh("Flower.fbx", "TextureAnimation");
	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 5000.f, 5000.f, 5000.f });
	//FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ -90.f, 180.f,0.f });


	Event.ResourcesName = "Flower_Att.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	Event.CurFrame = 0;
	FBXAnimationRenderer->CreateFBXAnimation("Flower_Att", Event);
	FBXAnimationRenderer->AnimationBindEnd("Flower_Att", std::bind(&FlowerMonster::AniFlower_Att, this, std::placeholders::_1));
	FBXAnimationRenderer->AnimationBindFrame("Flower_Att", std::bind(&FlowerMonster::AniFlower_AttFrame, this, std::placeholders::_1));

	
	Event.ResourcesName = "Flower_Death.FBX";
	Event.Loop = false;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("Flower_Death", Event);
	FBXAnimationRenderer->AnimationBindEnd("Flower_Death", std::bind(&FlowerMonster::AniFlower_Death, this, std::placeholders::_1));


	Event.ResourcesName = "Flower_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("Flower_Idle", Event);
	FBXAnimationRenderer->AnimationBindEnd("Flower_Idle", std::bind(&FlowerMonster::AniFlower_Idle, this, std::placeholders::_1));





	FBXAnimationRenderer->ChangeAnimation("Flower_Idle");



	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
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

	StateManager.CreateStateMember("Death"
		, std::bind(&FlowerMonster::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&FlowerMonster::DeathStart, this, std::placeholders::_1)
		, std::bind(&FlowerMonster::DeathEnd, this, std::placeholders::_1)
	);


	StateManager.ChangeState("Idle");
}

void FlowerMonster::Update(float _DeltaTime)
{





	if (m_Info.m_Hp <= 0)
	{
		StateManager.ChangeState("Death");
	}
	else
	{

		float4 TarGetDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();

		float Len = TarGetDir.Length();
		TarGetDir = TarGetDir.Normalize3DReturn();


		if (Len <= 800.f)
		{

			if (StateManager.GetCurStateStateName() != "Att")
				StateManager.ChangeState("Att");

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

			GetTransform().SetLocalRotation({ 0.0f, Angle, 0.0f });


		}



	}

	StateManager.Update(_DeltaTime);

}







void FlowerMonster::DeathStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Flower_Death");
}
void FlowerMonster::DeathEnd(const StateInfo& _Info)
{



}
void FlowerMonster::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

	

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
	FBXAnimationRenderer->ChangeAnimation("Flower_Att");
	m_bhitCheck = true;
}
void FlowerMonster::AttEnd(const StateInfo& _Info)
{
	m_bhitCheck = false;





}
void FlowerMonster::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
	
	

	//
	////삭제 예정
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}


}

void FlowerMonster::AniFlower_Att(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Idle");

}


void FlowerMonster::AniFlower_AttFrame(const GameEngineRenderingEvent& _Data)
{


	if (_Data.CurFrame == 50)
	{
		float4 ArrowDir = GetTransform().GetLocalRotation();
		float4 RenderFront = GetTransform().GetForwardVector();
		float4 ArrowPos = GetTransform().GetWorldPosition() + (RenderFront.Normalize3DReturn() * 200.f);

		ArrowPos.y += 70.f;

		//총알 생성
		std::weak_ptr < FlowerBullet> m_ArrowAtt = GetLevel()->CreateActor<FlowerBullet>(OBJECTORDER::MonsterAtt);
		m_ArrowAtt.lock()->GetTransform().SetWorldPosition(ArrowPos);
		m_ArrowAtt.lock()->GetTransform().SetLocalRotation(ArrowDir);




	}

}

void FlowerMonster::AniFlower_Idle(const GameEngineRenderingEvent& _Data)
{
}

void FlowerMonster::AniFlower_Death(const GameEngineRenderingEvent& _Data)
{
	Death();
}




void FlowerMonster::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Flower_Idle");
}
void FlowerMonster::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (m_bHitCheck)
	{
		StateManager.ChangeState("Stun");
		m_bHitCheck = false;
	}




}


#include "PreCompile.h"
#include "OldCrow.h"
#include "Player.h"
#include "UnitBase.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"
#include "GameEngineBase/GameEngineRandom.h"
#include "OldCrowScreamBase.h"

#include "DashBullet.h"
#include "ScreamMgr.h"


#include "OldCrowUI.h"


void OldCrow::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

}
void OldCrow::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Idle");
}




void OldCrow::StartActStart(const StateInfo& _Info)
{
	

	Player::GetMainPlayer()->m_bOldCrowCameraCheck = true;
	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 1.9f,-2.2f,0.f });
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ 25.f,181.f,-1300.f });
//	FBXAnimationRenderer->ChangeAnimation("OldCrow_Scream");
	
	
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Idle");

}
void OldCrow::StartActEnd(const StateInfo& _Info)
{
	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	PlayerPos.y += 1700.f;
	PlayerPos.z -= 1700.f;
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(PlayerPos);

	TexRenderer->Off();
	MainUI.lock()->Off();
	Player::GetMainPlayer()->m_bOldCrowCameraCheck = false;
	
}
void OldCrow::StartActUpdate(float _DeltaTime, const StateInfo& _Info)
{

	GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 1.9f,-2.2f,0.f });
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ 25.f,181.f,-1300.f });


	m_fStartTime += _DeltaTime;

	if (m_fStartTime >= 1.5f)
	{
		if (!ScreamAnicheck)
		{
			MainUI.lock()->m_bStartCheck = true;
			FBXAnimationRenderer->ChangeAnimation("OldCrow_Scream");
			CameraShake(1.f);
			ScreamAnicheck = true;

			float4 MyPos = GetTransform().GetWorldPosition();
			std::weak_ptr < ScreamMgr> ScreamBullet = GetLevel()->CreateActor<ScreamMgr>(OBJECTORDER::MonsterAtt);
			MyPos.y = 200.f;

			MyPos.x = MyPos.x + GetTransform().GetForwardVector().x * 200.f;
			ScreamBullet.lock()->GetTransform().SetWorldPosition(MyPos);


		}
	}

	

	if (m_fStartTime >= 5.f)
	{
		StateManager.ChangeState("MoveReady");
	}


}





void OldCrow::MoveReadyStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Run_S");
}
void OldCrow::MoveReadyEnd(const StateInfo& _Info)
{

}

void OldCrow::MoveReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{

}




void OldCrow::MoveStart(const StateInfo& _Info)
{
	//FBXAnimationRenderer->ChangeAnimation("OldCrow_Run");
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Run");
	m_fSpeed = 650.f;
	m_fAttCTime = 0.f;


	m_vMovePlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	m_vMoveMyPos = GetTransform().GetWorldPosition();

	m_vMovePlayerPos.y = 10.f;
	m_vMoveMyPos.y = 10.f;



	m_vMoveTarGetDir = (m_vMovePlayerPos - m_vMoveMyPos).Normalize3DReturn();

	m_vMoveGoPos = m_vMovePlayerPos + m_vMoveTarGetDir * 1200.f;

	m_vMoveGoDir = GetTransform().GetForwardVector();


	AttAngle = DirToRot(m_vMoveGoPos, m_vMoveMyPos);

	GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });



	

	
}
void OldCrow::MoveEnd(const StateInfo& _Info)
{
	
}
void OldCrow::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{

	m_fAttCTime += _DeltaTime;

	//여기서부터 플레이어 추적 

	MoveLen = (m_vMovePlayerPos - m_vMoveMyPos).Length();

	m_vMoveMyPos = GetTransform().GetWorldPosition();
	m_vMoveTarGetDir = (m_vMovePlayerPos - m_vMoveMyPos).Normalize3DReturn();
	m_vMoveGoDir = GetTransform().GetForwardVector();



	float4 Cross = float4::Cross3D(m_vMoveGoDir, m_vMoveTarGetDir);


	float4 LerpPos = float4::Lerp(m_vMoveMyPos, m_vMoveGoPos, _DeltaTime * 1.f);

	GetTransform().SetWorldPosition(LerpPos);


	float TarGetLen = (m_vMoveMyPos - m_vMoveGoPos).Length();


	if (TarGetLen <= 700.f)
	{
		if (Cross.y > 0)
		{
			if(FBXAnimationRenderer->CheckCurrentAnimation("OldCrow_Run"))
			{

				FBXAnimationRenderer->ChangeAnimation("OldCrow_Turn_Left");

			}
			
		}
		// 오른쪽
		else
		{
			if (FBXAnimationRenderer->CheckCurrentAnimation("OldCrow_Run"))
			{

				FBXAnimationRenderer->ChangeAnimation("OldCrow_Turn_Right");
			}


		}

	}
	


	

	if (AttType == 1)
	{
		AttAngle = DirToRot(m_vMovePlayerPos, m_vMoveMyPos);
		GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f});
		StateManager.ChangeState("DashReady");


		AttType = 0;
	}
	else if (AttType == 2)
	{
		StateManager.ChangeState("Scream");
		AttType = 0;
	}
	else if (AttType == 3)
	{
		StateManager.ChangeState("JumpReady");
		m_fJumpSpeed = 800.f;
		AttType = 0;
	}



}






void OldCrow::TurnLStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Turn_Left");
}
void OldCrow::TurnLEnd(const StateInfo& _Info)
{

}
void OldCrow::TurnLUpdate(float _DeltaTime, const StateInfo& _Info)
{

}






void OldCrow::TurnRStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Turn_Right");
}
void OldCrow::TurnREnd(const StateInfo& _Info)
{

}
void OldCrow::TurnRUpdate(float _DeltaTime, const StateInfo& _Info)
{

}






void OldCrow::DashReadyStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Dash_Start");


	DashStartCheck = false;
	DashEndCheck = false;

	float4 Pos = GetTransform().GetWorldPosition();
	Pos.y = 50.f;
	m_cHook = GetLevel()->CreateActor<DashBullet>(OBJECTORDER::MonsterAtt);
	m_cHook.lock()->GetTransform().SetWorldPosition(Pos);
	m_cHook.lock()->GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });
	m_cHook.lock()->m_OldCorw = std::dynamic_pointer_cast<OldCrow>(shared_from_this());


}
void OldCrow::DashReadyEnd(const StateInfo& _Info)
{
	DashStartCheck = false;
	DashEndCheck = false;
}
void OldCrow::DashReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (DashStartCheck)
	{
		StateManager.ChangeState("Dash");
	}
}






void OldCrow::DashStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Dash");
	AttCount = 0;
	DashEndCheck = false;

}
void OldCrow::DashEnd(const StateInfo& _Info)
{
	DashStartCheck = true;
	DashEndCheck = false;
}
void OldCrow::DashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
		float4 MoveDir = GetTransform().GetForwardVector();

		GetTransform().SetWorldMove(MoveDir * 4000.f * _DeltaTime);


		if (DashEndCheck)
		{
			//끝
			//총알 삭제 + 스테이트 변경

			m_cHook.lock()->Death();
			m_cHook.reset();
			StateManager.ChangeState("Dash2Ready");

		}



}

void OldCrow::DashReady2Start(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Dash_Start");
	++AttCount;

	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	float4 PlayerRight = PlayerPos +  Player::GetMainPlayer()->FBXAnimationRenderer->GetTransform().GetRightVector() * 2000.f;
	GetTransform().SetWorldPosition(PlayerRight);

	DashStartCheck = false;
	DashEndCheck = false;

	
	PlayerRight.y = 50.f;
	m_cHook = GetLevel()->CreateActor<DashBullet>(OBJECTORDER::MonsterAtt);
	m_cHook.lock()->GetTransform().SetWorldPosition(PlayerRight);

	AttAngle = DirToRot(PlayerPos, PlayerRight);

	GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });
	m_cHook.lock()->GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });
	m_cHook.lock()->m_OldCorw = std::dynamic_pointer_cast<OldCrow>(shared_from_this());



}
void OldCrow::DashReady2End(const StateInfo& _Info)
{
	DashStartCheck = false;
	DashEndCheck = false;
}
void OldCrow::DashReady2Update(float _DeltaTime, const StateInfo& _Info)
{
	if (DashStartCheck)
	{
		StateManager.ChangeState("Dash2");
	}
}


void OldCrow::Dash2Start(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Dash");
	

	DashEndCheck = false;
}
void OldCrow::Dash2End(const StateInfo& _Info)
{
	DashStartCheck = true;
	DashEndCheck = false;
}
void OldCrow::Dash2Update(float _DeltaTime, const StateInfo& _Info)
{

	float4 MoveDir = GetTransform().GetForwardVector();

	GetTransform().SetWorldMove(MoveDir * 4000.f * _DeltaTime);


	if (DashEndCheck)
	{
		//끝
		//총알 삭제 + 스테이트 변경

		m_cHook.lock()->Death();
		m_cHook.reset();

		if (AttCount < 3)
		{
			StateManager.ChangeState("Dash2Ready");
		}
		else
		{
			StateManager.ChangeState("JumpReady");
			m_fJumpSpeed = 1500.f;
		}
	}

}


void OldCrow::DashReady3Start(const StateInfo& _Info)
{

}
void OldCrow::DashReady3End(const StateInfo& _Info)
{

}
void OldCrow::DashReady3Update(float _DeltaTime, const StateInfo& _Info)
{

}


void OldCrow::Dash3Start(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Dash");
}
void OldCrow::Dash3End(const StateInfo& _Info)
{

}
void OldCrow::Dash3Update(float _DeltaTime, const StateInfo& _Info)
{

}





void OldCrow::JumpStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Slam");
}
void OldCrow::JumpEnd(const StateInfo& _Info)
{

}
void OldCrow::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	static float fAccDeltatime = 0.f;
	fAccDeltatime += _DeltaTime;

	if (0.4f < fAccDeltatime)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("31_LastBossJump.mp3");
		fAccDeltatime = 0.f;
	}

	GetTransform().SetWorldForwardMove(m_fJumpSpeed, _DeltaTime);
	GetTransform().SetWorldDownMove(2000.f, _DeltaTime);

	float4 MyPos = GetTransform().GetWorldPosition();

	if (MyPos.y <= 10.f)
	{
		

		MyPos.y = 10.f;
		GetTransform().SetWorldPosition(MyPos);
		StateManager.ChangeState("JumpEnd");
	}


}





void OldCrow::JumpReadyStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Jump_Start");

	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	float4 MyPos = GetTransform().GetWorldPosition();
	
	AttAngle = DirToRot(PlayerPos, MyPos);

	GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });




}
void OldCrow::JumpReadyEnd(const StateInfo& _Info)
{

}
void OldCrow::JumpReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldForwardMove(m_fJumpSpeed,_DeltaTime);
	GetTransform().SetWorldUpMove(2000.f, _DeltaTime);




}





void OldCrow::JumpEndStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Slam_End");
	CameraShake(0.5f);
}
void OldCrow::JumpEndEnd(const StateInfo& _Info)
{

}
void OldCrow::JumpEndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//GetTransform().SetWorldDownMove(3000.f, _DeltaTime);

	float4 MyPos = GetTransform().GetWorldPosition();

	if (MyPos.y <= 10.f)
	{

		MyPos.y = 10.f;
		GetTransform().SetWorldPosition(MyPos);

	}
}





void OldCrow::ScreamStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Scream");

	std::weak_ptr < OldCrowScreamBase> Bullet = GetLevel()->CreateActor<OldCrowScreamBase>(OBJECTORDER::MonsterAtt);
	float4 MyPos = GetTransform().GetWorldPosition();
	MyPos.y = 50.f;
	Bullet.lock()->GetTransform().SetWorldPosition(MyPos);

	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("28_LastBossScream.mp3");

	//스크림 이펙트 생성


	std::weak_ptr < ScreamMgr> ScreamBullet = GetLevel()->CreateActor<ScreamMgr>(OBJECTORDER::MonsterAtt);
	MyPos.y = 200.f;

	MyPos.x = MyPos.x + GetTransform().GetForwardVector().x * 200.f;
	ScreamBullet.lock()->GetTransform().SetWorldPosition(MyPos);

}
void OldCrow::ScreamEnd(const StateInfo& _Info)
{

}
void OldCrow::ScreamUpdate(float _DeltaTime, const StateInfo& _Info)
{

}
//


//
void OldCrow::DashDeathStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Death_Run");
}
void OldCrow::DashDeathEnd(const StateInfo& _Info)
{

}
void OldCrow::DashDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}





void OldCrow::StandDeathStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Death_Stand");
}
void OldCrow::StandDeathEnd(const StateInfo& _Info)
{


}
void OldCrow::StandDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{


}




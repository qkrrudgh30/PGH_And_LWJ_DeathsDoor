#include "PreCompile.h"
#include "OldCrow.h"
#include "Player.h"
#include "UnitBase.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"
#include "GameEngineBase/GameEngineRandom.h"

void OldCrow::AniDashEnd(const GameEngineRenderingEvent& _Data)
{
	
}
void OldCrow::AniDashStartEnd(const GameEngineRenderingEvent& _Data)
{
//	StateManager.ChangeState("Dash");
}
void OldCrow::AniDeathRunEnd(const GameEngineRenderingEvent& _Data)
{
	Death();
}
void OldCrow::AniDeathStandEnd(const GameEngineRenderingEvent& _Data)
{
	Death();
}
void OldCrow::AniIdleEnd(const GameEngineRenderingEvent& _Data)
{
	//StateManager.ChangeState("MoveReady");
}
void OldCrow::AniJumpStartEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Jump");
}
void OldCrow::AniRunEnd(const GameEngineRenderingEvent& _Data)
{


}

void OldCrow::AniRunFrame(const GameEngineRenderingEvent& _Data)
{

	
}


void OldCrow::AniRunStartEnd(const GameEngineRenderingEvent& _Data)
{


	if (StartAnicheck)
	{
		StateManager.ChangeState("Move");
	}
	else
	{
		FBXAnimationRenderer->ChangeAnimation("OldCrow_Idle");
		StartAnicheck = true;
	}



}
void OldCrow::AniScreamEnd(const GameEngineRenderingEvent& _Data)
{
	if (StartAnicheck)
	{
		StateManager.ChangeState("MoveReady");
	}
	else
	{
		FBXAnimationRenderer->ChangeAnimation("OldCrow_Run_S");
		
	}
	
}
void OldCrow::AniScreamFrame(const GameEngineRenderingEvent& _Data)
{
	if (5u == _Data.CurFrame)
	{
		m_structSoundPlayer.Stop();
		m_structSoundPlayer = GameEngineSound::SoundPlayControl("28_LastBossScream.mp3");
		
	}
}
void OldCrow::AniSlamEnd(const GameEngineRenderingEvent& _Data)
{

}
void OldCrow::AniSlamEndEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");
}
void OldCrow::AniTurnLeftEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");

	AttType = GameEngineRandom::MainRandom.RandomInt(0, 4);
}
void OldCrow::AniTurnRightEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");

	AttType = GameEngineRandom::MainRandom.RandomInt(0, 4);
}
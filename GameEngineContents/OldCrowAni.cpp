#include "PreCompile.h"
#include "OldCrow.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"


void OldCrow::AniDashEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Jump");
}
void OldCrow::AniDashStartEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Dash");
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
	StateManager.ChangeState("MoveReady");
}
void OldCrow::AniJumpStartEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Jump");
}
void OldCrow::AniRunEnd(const GameEngineRenderingEvent& _Data)
{
	//StateManager.ChangeState("StartAct");
}
void OldCrow::AniRunStartEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");
}
void OldCrow::AniScreamEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("MoveReady");
}
void OldCrow::AniSlamEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("JumpEnd");
}
void OldCrow::AniSlamEndEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");
}
void OldCrow::AniTurnLeftEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");
}
void OldCrow::AniTurnRightEnd(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Move");
}
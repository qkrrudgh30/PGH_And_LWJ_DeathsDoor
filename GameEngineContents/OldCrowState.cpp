
#include "PreCompile.h"
#include "OldCrow.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"

void OldCrow::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

}
void OldCrow::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Idle");
}




void OldCrow::StartActStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Scream");
}
void OldCrow::StartActEnd(const StateInfo& _Info)
{

}
void OldCrow::StartActUpdate(float _DeltaTime, const StateInfo& _Info)
{

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
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Run");
}
void OldCrow::MoveEnd(const StateInfo& _Info)
{

}
void OldCrow::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{

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
}
void OldCrow::DashReadyEnd(const StateInfo& _Info)
{

}
void OldCrow::DashReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{

}






void OldCrow::DashStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Dash");
}
void OldCrow::DashEnd(const StateInfo& _Info)
{

}
void OldCrow::DashUpdate(float _DeltaTime, const StateInfo& _Info)
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

}





void OldCrow::JumpReadyStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Jump_Start");
}
void OldCrow::JumpReadyEnd(const StateInfo& _Info)
{

}
void OldCrow::JumpReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{

}





void OldCrow::JumpEndStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Slam_End");
}
void OldCrow::JumpEndEnd(const StateInfo& _Info)
{

}
void OldCrow::JumpEndUpdate(float _DeltaTime, const StateInfo& _Info)
{

}





void OldCrow::ScreamStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("OldCrow_Scream");
}
void OldCrow::ScreamEnd(const StateInfo& _Info)
{

}
void OldCrow::ScreamUpdate(float _DeltaTime, const StateInfo& _Info)
{

}





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




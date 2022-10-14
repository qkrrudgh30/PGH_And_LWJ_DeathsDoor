#include "PreCompile.h"
#include "GEngine.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

bool GEngine::CollisionDebug = false;

GEngine::GEngine() 
{
}

GEngine::~GEngine() 
{
}

bool GEngine::IsCollisionDebug()
{
	return CollisionDebug;
}

void GEngine::CollisionDebugSwitch()
{
	CollisionDebug = !CollisionDebug;
}

void GEngine::CollisionDebugOn()
{
	CollisionDebug = true;
}
void GEngine::CollisionDebugOff()
{
	CollisionDebug = false;
}


GameEngineLevel* GEngine::GetCurrentLevel()
{
	return GameEngineCore::GetCurLevel();
}

void GEngine::ChangeLevel(std::string _Name)
{
	GameEngineCore::ChangeLevel(_Name);
}

#include "PreCompile.h"
#include "GameEngineStateManager.h"

GameEngineStateManager::GameEngineStateManager() 
{
}

GameEngineStateManager::~GameEngineStateManager() 
{
}

void GameEngineStateManager::Update(float _DeltaTime)
{
	CurState->StateUpdate(_DeltaTime);
}
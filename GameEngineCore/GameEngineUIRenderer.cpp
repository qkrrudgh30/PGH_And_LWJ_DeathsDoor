#include "PreCompile.h"
#include "GameEngineUIRenderer.h"

GameEngineUIRenderer::GameEngineUIRenderer() 
{
}

GameEngineUIRenderer::~GameEngineUIRenderer() 
{
}

void GameEngineUIRenderer::Start() 
{
	GameEngineDefaultRenderer::Start();

	PushRendererToUICamera();

	SetTextureRendererSetting();
}
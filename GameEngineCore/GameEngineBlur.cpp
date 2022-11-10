#include "PreCompile.h"
#include "GameEngineBlur.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineBlur::GameEngineBlur() 
	: CopyTarget(nullptr)
{
}

GameEngineBlur::~GameEngineBlur() 
{
	//if (nullptr != CopyTarget)
	//{
	//	//delete CopyTarget;
	//	// CopyTarget = nullptr;
	//}
}

void GameEngineBlur::EffectInit() 
{
	CopyTarget = std::make_shared<GameEngineRenderTarget>();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet.SetPipeLine("Blur");

	// EffetSet
}

void GameEngineBlur::Effect(std::shared_ptr<GameEngineRenderTarget> _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}
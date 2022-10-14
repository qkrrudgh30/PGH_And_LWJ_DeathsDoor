#pragma once
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderSet.h"

// Ό³Έν :
class GameEngineBlur : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	GameEngineBlur();
	~GameEngineBlur();

	// delete Function
	GameEngineBlur(const GameEngineBlur& _Other) = delete;
	GameEngineBlur(GameEngineBlur&& _Other) noexcept = delete;
	GameEngineBlur& operator=(const GameEngineBlur& _Other) = delete;
	GameEngineBlur& operator=(GameEngineBlur&& _Other) noexcept = delete;

	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Render);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;

private:
};


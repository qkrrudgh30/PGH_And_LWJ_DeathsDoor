#pragma once
#include "GameEngineRenderTarget.h"

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
	virtual void Effect(std::shared_ptr < GameEngineRenderTarget> _Render);

protected:
	std::shared_ptr<GameEngineRenderTarget> CopyTarget;
	GameEngineRenderUnit EffectSet;

private:
};


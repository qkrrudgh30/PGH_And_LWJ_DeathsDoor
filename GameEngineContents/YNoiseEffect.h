#pragma once
#include <GameEngineCore\GameEngineRenderTarget.h>
#include <GameEngineCore\GameEngineRenderSet.h>

// Ό³Έν :
class YNoiseEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	YNoiseEffect();
	~YNoiseEffect();

	// delete Function
	YNoiseEffect(const YNoiseEffect& _Other) = delete;
	YNoiseEffect(YNoiseEffect&& _Other) noexcept = delete;
	YNoiseEffect& operator=(const YNoiseEffect& _Other) = delete;
	YNoiseEffect& operator=(YNoiseEffect&& _Other) noexcept = delete;

	GameEngineRenderTarget* CopyTarget;
protected:
	void EffectInit() override;
	void Effect(GameEngineRenderTarget* _Render) override;

	RenderOption Option;

private:
	GameEngineRenderSet EffectSet;

};


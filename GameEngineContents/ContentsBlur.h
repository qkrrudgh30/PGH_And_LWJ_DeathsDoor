#pragma once

#include <GameEngineCore/GameEngineRenderTarget.h>

struct BlurInfo
{
	unsigned int	muAppliedType;
	unsigned int	muAppliedCount;
	float			mfRadius;
	float4			mf4WindowSize;
};

// Ό³Έν :
class ContentsBlur : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	ContentsBlur();
	~ContentsBlur();

	// delete Function
	ContentsBlur(const ContentsBlur& _Other) = delete;
	ContentsBlur(ContentsBlur&& _Other) noexcept = delete;
	ContentsBlur& operator=(const ContentsBlur& _Other) = delete;
	ContentsBlur& operator=(ContentsBlur&& _Other) noexcept = delete;

	virtual void EffectInit();
	virtual void Effect(std::shared_ptr<GameEngineRenderTarget> _sptrRenderTarget);

	void SetBlurInfo(unsigned int _uBlurType, unsigned int _uAppliedCount = 1u, float _fRadius = 0.f, int _iIsUnityTexture = 0);

protected:

private:
	void InitializeBlurInfo(void);

public:

protected:

private:
	std::shared_ptr<GameEngineRenderTarget>	msptrRenderTargetForBlur;
	GameEngineRenderUnit					mAppliedRenderUnit;
	BlurInfo								mBlurInfo;

};


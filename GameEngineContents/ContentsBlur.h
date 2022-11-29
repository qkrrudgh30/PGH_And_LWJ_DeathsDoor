#pragma once

#include <GameEngineCore/GameEngineRenderTarget.h>

struct BlurInfo
{
	unsigned int	muOnOff;
	unsigned int	muAppliedArea;
	float           mfIntence;
	float4          mf4WindowSize;
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

	static void SetBlurInfo(unsigned int _uOnOff, unsigned int _uAppliedArea = 3u, float _fIntence = 0.f);

	static std::weak_ptr<ContentsBlur> GetBlurInstance(void) 
	{ 
		if (nullptr == mwptrContentsBlur.lock())
		{
			mwptrContentsBlur = GEngine::GetCurrentLevel()->GetCamera(CAMERAORDER::USER0)->GetCameraRenderTarget()->AddEffect<ContentsBlur>();
		}
		return mwptrContentsBlur; 
	}

protected:

private:
	void InitializeBlurInfo(void);

public:

protected:

private:
	static std::weak_ptr<ContentsBlur>		mwptrContentsBlur;
	std::shared_ptr<GameEngineRenderTarget>	msptrRenderTargetForBlur;
	GameEngineRenderUnit					mAppliedRenderUnit;
	static BlurInfo							mBlurInfo;

};


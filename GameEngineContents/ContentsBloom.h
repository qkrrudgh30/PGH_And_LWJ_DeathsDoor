#pragma once

#include <GameEngineCore/GameEngineRenderTarget.h>

struct BloomInfo
{
	unsigned int muOnOff;
	unsigned int muAppliedArea;
	float mfLuminance;
	float mfIntence;
	float4 mf4WindowSize;
};

// Ό³Έν :
class ContentsBloom : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	ContentsBloom();
	~ContentsBloom();

	// delete Function
	ContentsBloom(const ContentsBloom& _Other) = delete;
	ContentsBloom(ContentsBloom&& _Other) noexcept = delete;
	ContentsBloom& operator=(const ContentsBloom& _Other) = delete;
	ContentsBloom& operator=(ContentsBloom&& _Other) noexcept = delete;
	virtual void EffectInit();
	virtual void Effect(std::shared_ptr<GameEngineRenderTarget> _sptrRenderTarget);

	static void SetBloomInfo(unsigned int _uOnOff, unsigned int muAppliedArea = 30u, float _fLuminance = 0.3f, float _fIntence = 0.f);

	static std::weak_ptr<ContentsBloom> GetBloomInstance(void)
	{
		if (nullptr == mwptrContentsBloom.lock())
		{
#pragma region TemporaryCode

			mwptrContentsBloom = GEngine::GetCurrentLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<ContentsBloom>();

#pragma endregion

			// sptrContentsBlur = GEngine::GetCurrentLevel()->GetBlurCamera()->GetCameraRenderTarget()->AddEffect<ContentsBlur>();

		}
		return mwptrContentsBloom;
	}

protected:

private:
	void InitializeBloomInfo(void);

public:

protected:

private:
	static std::weak_ptr<ContentsBloom>		mwptrContentsBloom;
	static BloomInfo						mBloomInfo;
	std::shared_ptr<GameEngineRenderTarget>	msptrRenderTargetForBloom;
	GameEngineRenderUnit					mAppliedRenderUnit;

};


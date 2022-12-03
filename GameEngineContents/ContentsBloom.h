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

	void SetBloomInfo(unsigned int _uOnOff, unsigned int muAppliedArea = 1u, float _fLuminance = 0.3f, float _fIntence = 0.f);

	void InitializeBloom(std::shared_ptr<ContentsBloom>& _sptrContentsBloom)
	{
		_sptrContentsBloom = GEngine::GetCurrentLevel()->GetCamera(CAMERAORDER::USER1)->GetCameraRenderTarget()->AddEffect<ContentsBloom>();
		// _sptrContentsBloom = GEngine::GetCurrentLevel()->GetCamera(CAMERAORDER::MAINCAMERA)->GetCameraRenderTarget()->AddEffect<ContentsBloom>();
	}

protected:

private:
	void InitializeBloomInfo(void);

public:

protected:

private:
	std::weak_ptr<ContentsBloom>		mwptrContentsBloom;
	BloomInfo						mBloomInfo;
	std::shared_ptr<GameEngineRenderTarget>	msptrRenderTargetForBloom;
	GameEngineRenderUnit					mAppliedRenderUnit;

};


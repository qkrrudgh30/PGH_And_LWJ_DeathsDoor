#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

struct FadeInfo
{
	float4  mf4FrameData;
	float4	mf4PivotPos;
	float   mfAccValue;
	int		miIsUnityTexture;
};

// Ό³Έν :
class GameEngineTexture;
class FadeRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	FadeRenderer();
	~FadeRenderer();

	// delete Function
	FadeRenderer(const FadeRenderer& _Other) = delete;
	FadeRenderer(FadeRenderer&& _Other) noexcept = delete;
	FadeRenderer& operator=(const FadeRenderer& _Other) = delete;
	FadeRenderer& operator=(FadeRenderer&& _Other) noexcept = delete;

	void SetPivot(PIVOTMODE _mode);
	void SetFadeInfo(int _iInAndOut, float _fHoldingTime, bool _bIsLooped, int _iIsUnityTexture = 0);
	void SetTexture(const std::string& _strTextureName);

protected:
	void Start() override;
	void Update(float _fDeltatime) override;

private:
	void InitializeFadeInfo(void);
	void SetFadeRendererSetting(void);

	FadeInfo mFadeInfo;
	std::weak_ptr<GameEngineTexture> mwpCurrTexture;

	float	mfHoldingAccTimeForFade;
	float	mfCurrentAccTimeForFade;
	bool	mbIsLooped;
	int     miInAndOut;	

};

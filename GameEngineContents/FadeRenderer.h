#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

struct FadeInfo
{
	float4  mf4FrameData;
	float4	mf4PivotPos;
	float	mfFromAlphaValue;
	float	mfToAlphaValue;
	float   mfSpeed;
	float   mfDeltatime;
	int		miIsWrapping;
	int		miIsLoop;
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
	void SetFadeInfo(float _fFromAlphaValue, float _fToAlphaValue, float _fSpeed, int _iIsWrapping = 0, int _iIsLoop = 0, int _iIsUnityTexture = 0);
	void SetTexture(const std::string& _strTextureName);

protected:
	void Start() override;
	void Update(float _fDeltatime) override;

private:
	void InitializeFadeInfo(void);
	void SetFadeRendererSetting(void);

	FadeInfo mFadeInfo;
	std::weak_ptr<GameEngineTexture> mwpCurrTexture;

};

#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

struct FadeInfo
{
	float	mfFrom;
	float	mfTo;
	int		miWrapping;
	int		miLoop;
	int		miIsUnityTexture;
	float4	mf4PivotPos;
};

// Ό³Έν :
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

protected:
	void Start() override;

private:
	void InitializeFadeInfo(void);
	void SetFadeRendererSetting(void);

	FadeInfo mFadeInfo;

};

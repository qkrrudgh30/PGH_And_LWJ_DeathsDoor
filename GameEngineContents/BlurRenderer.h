#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

struct BlurInfo
{
	float4 mf4FrameData;
	float4 mf4PivotPos;
	unsigned int muAppliedType;
	unsigned int muAppliedCount;
	int miIsUnityTexture;
};

// Ό³Έν :
class GameEngineTexture;
class BlurRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	BlurRenderer();
	~BlurRenderer();

	// delete Function
	BlurRenderer(const BlurRenderer& _Other) = delete;
	BlurRenderer(BlurRenderer&& _Other) noexcept = delete;
	BlurRenderer& operator=(const BlurRenderer& _Other) = delete;
	BlurRenderer& operator=(BlurRenderer&& _Other) noexcept = delete;

	void SetPivot(PIVOTMODE _ePivotMode);
	void SetBlurInfo(unsigned int _uBlurType, unsigned int _uAppliedCount = 1u, int _iIsUnityTexture = 0);
	void SetTexture(const std::string& _strTextureName);

protected:
	void Start(void) override;
	void Update(float _fDetatime) override;

private:
	void InitializeBlurInfo(void);
	void SetBlurRenderingPipeline(void);

	BlurInfo								mBlurInfo;
	std::weak_ptr<GameEngineTexture>		mwptrCurrentTexture;

};


#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

struct WaveInfo
{
	float m_fAccTime;
	float4 m_f4PivotPos;
};

// Ό³Έν :
class WaveRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	WaveRenderer();
	~WaveRenderer();

	// delete Function
	WaveRenderer(const WaveRenderer& _Other) = delete;
	WaveRenderer(WaveRenderer&& _Other) noexcept = delete;
	WaveRenderer& operator=(const WaveRenderer& _Other) = delete;
	WaveRenderer& operator=(WaveRenderer&& _Other) noexcept = delete;

	void SetPivot(PIVOTMODE _eMode);
	void SetWaveInfo();
	void SetTexture(const std::string& _strTextureName);
	PixelData& GetPixelData(void) { return m_structPixelData; }

protected:
	void Start() override;	
	void Update(float _fDeltatime) override;
	void End() {}

private:
	void InitializeWave();
	void SetWaveRenderingSetting();

public:

protected:

private:
	std::weak_ptr<GameEngineTexture> m_wptrCurrentTexture;

	WaveInfo m_structWaveInfo;
	PixelData m_structPixelData;
};


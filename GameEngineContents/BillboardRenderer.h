#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

struct BillboardInfo
{
	float4  mf4FrameData;
	float4	mf4PivotPos;
	unsigned int muOnOffBillboard;
	float4x4 mf4x4MainCameraRotation;
};

// Ό³Έν :
class BillboardRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	BillboardRenderer();
	~BillboardRenderer();

	// delete Function
	BillboardRenderer(const BillboardRenderer& _Other) = delete;
	BillboardRenderer(BillboardRenderer&& _Other) noexcept = delete;
	BillboardRenderer& operator=(const BillboardRenderer& _Other) = delete;
	BillboardRenderer& operator=(BillboardRenderer&& _Other) noexcept = delete;

	void SetPivot(PIVOTMODE _mode);
	void SetBillboardInfo(unsigned int _uOnOffBillboard);
	void SetTexture(const std::string& _strTextureName);
	PixelData& GetPixelData() { return mPixelData; }

protected:
	void Start() override;
	void Update(float _fDeltatime) override;
	void End() {}

private:
	void InitializeBillboard();
	void SetBillboardRenderingSetting();
	float4x4 GetMainCameraRotation(const float4& _f4EyePosition, const float4& _f4EyeFocus, const float4& _f4Up);

public:

protected:

private:
	std::weak_ptr<GameEngineTexture> mwpCurrTexture;

	BillboardInfo mBillboardInfo;
	float4x4 mf4x4MainCameraRotation;

	PixelData mPixelData;

};


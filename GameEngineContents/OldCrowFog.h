#pragma once
#pragma once
#include <GameEngineCore/CoreMinimal.h>
#
#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class OldCrowFog : public UnitBase
{
public:
	// constrcuter destructer
	OldCrowFog();
	~OldCrowFog();

	// delete Function
	OldCrowFog(const OldCrowFog& _Other) = delete;
	OldCrowFog(OldCrowFog&& _Other) noexcept = delete;
	OldCrowFog& operator=(const OldCrowFog& _Other) = delete;
	OldCrowFog& operator=(OldCrowFog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:

	void ChangeColorBlue();
	std::shared_ptr<BillboardRenderer> sptrTestPicture;
public:
	float m_fScaleMax = 0.f;
	float m_fTime = 0.f;
	bool  m_bScalecheck = false;
	bool m_bScaleZero = false;


	float4 m_fStartPos = {};

	float4 m_fGoDir = {};


};


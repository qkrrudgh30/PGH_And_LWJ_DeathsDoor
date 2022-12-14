
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class SWEff : public UnitBase
{
public:
	// constrcuter destructer
	SWEff();
	~SWEff();

	// delete Function
	SWEff(const SWEff& _Other) = delete;
	SWEff(SWEff&& _Other) noexcept = delete;
	SWEff& operator=(const SWEff& _Other) = delete;
	SWEff& operator=(SWEff&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:

	std::shared_ptr<BillboardRenderer> sptrTestPicture;
public:
	float m_fScaleMax = 0.f;
	float m_fTime = 0.f;
	bool  m_bScalecheck = false;


	float4 m_fGoDir = {};


};




#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class ArrowEff : public UnitBase
{
public:
	// constrcuter destructer
	ArrowEff();
	~ArrowEff();

	// delete Function
	ArrowEff(const ArrowEff& _Other) = delete;
	ArrowEff(ArrowEff&& _Other) noexcept = delete;
	ArrowEff& operator=(const ArrowEff& _Other) = delete;
	ArrowEff& operator=(ArrowEff&& _Other) noexcept = delete;

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


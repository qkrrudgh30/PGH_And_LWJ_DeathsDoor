
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class FlowerBulletEff : public UnitBase
{
public:
	// constrcuter destructer
	FlowerBulletEff();
	~FlowerBulletEff();

	// delete Function
	FlowerBulletEff(const FlowerBulletEff& _Other) = delete;
	FlowerBulletEff(FlowerBulletEff&& _Other) noexcept = delete;
	FlowerBulletEff& operator=(const FlowerBulletEff& _Other) = delete;
	FlowerBulletEff& operator=(FlowerBulletEff&& _Other) noexcept = delete;

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


	float4 m_fStartPos = {};

	float4 m_fGoDir = {};


};


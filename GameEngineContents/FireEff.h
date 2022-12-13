
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class FireEff : public UnitBase
{
public:
	// constrcuter destructer
	FireEff();
	~FireEff();

	// delete Function
	FireEff(const FireEff& _Other) = delete;
	FireEff(FireEff&& _Other) noexcept = delete;
	FireEff& operator=(const FireEff& _Other) = delete;
	FireEff& operator=(FireEff&& _Other) noexcept = delete;

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


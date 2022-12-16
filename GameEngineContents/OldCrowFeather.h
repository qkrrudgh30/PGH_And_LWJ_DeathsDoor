#pragma once

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class OldCrowFeather : public UnitBase
{
public:
	// constrcuter destructer
	OldCrowFeather();
	~OldCrowFeather();

	// delete Function
	OldCrowFeather(const OldCrowFeather& _Other) = delete;
	OldCrowFeather(OldCrowFeather&& _Other) noexcept = delete;
	OldCrowFeather& operator=(const OldCrowFeather& _Other) = delete;
	OldCrowFeather& operator=(OldCrowFeather&& _Other) noexcept = delete;

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


	bool StartCheck = false;

};


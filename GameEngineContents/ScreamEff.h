


#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class ScreamEff : public UnitBase
{
public:
	// constrcuter destructer
	ScreamEff();
	~ScreamEff();

	// delete Function
	ScreamEff(const ScreamEff& _Other) = delete;
	ScreamEff(ScreamEff&& _Other) noexcept = delete;
	ScreamEff& operator=(const ScreamEff& _Other) = delete;
	ScreamEff& operator=(ScreamEff&& _Other) noexcept = delete;

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


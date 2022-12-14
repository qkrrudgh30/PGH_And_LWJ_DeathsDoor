

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class BillboardRenderer;
class PlayerFireEff : public UnitBase
{
public:
	// constrcuter destructer
	PlayerFireEff();
	~PlayerFireEff();

	// delete Function
	PlayerFireEff(const PlayerFireEff& _Other) = delete;
	PlayerFireEff(PlayerFireEff&& _Other) noexcept = delete;
	PlayerFireEff& operator=(const PlayerFireEff& _Other) = delete;
	PlayerFireEff& operator=(PlayerFireEff&& _Other) noexcept = delete;

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


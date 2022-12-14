

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :

class PlayerFireBulletEff : public UnitBase
{
public:
	// constrcuter destructer
	PlayerFireBulletEff();
	~PlayerFireBulletEff();

	// delete Function
	PlayerFireBulletEff(const PlayerFireBulletEff& _Other) = delete;
	PlayerFireBulletEff(PlayerFireBulletEff&& _Other) noexcept = delete;
	PlayerFireBulletEff& operator=(const PlayerFireBulletEff& _Other) = delete;
	PlayerFireBulletEff& operator=(PlayerFireBulletEff&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:


public:
	float m_fScaleMax = 0.f;
	float m_fTime = 0.f;
	bool  m_bScalecheck = false;

	bool m_bScaleZero = true;
	float4 m_fStartPos = {};

	float4 m_fGoDir = {};


};


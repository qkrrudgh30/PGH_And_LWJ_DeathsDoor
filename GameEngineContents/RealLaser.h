


#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class RealLaser : public UnitBase
{
public:
	// constrcuter destructer
	RealLaser();
	~RealLaser();

	// delete Function
	RealLaser(const RealLaser& _Other) = delete;
	RealLaser(RealLaser&& _Other) noexcept = delete;
	RealLaser& operator=(const RealLaser& _Other) = delete;
	RealLaser& operator=(RealLaser&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:

public:
	float m_fScaleMax = 0.f;
	float m_fTime = 0.f;
	bool  m_bScalecheck = false;
	CollisionReturn PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);


	float4 m_fGoDir = {};


};


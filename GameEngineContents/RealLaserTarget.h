
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :

class RealLaserTarget : public UnitBase
{
public:
	// constrcuter destructer
	RealLaserTarget();
	~RealLaserTarget();

	// delete Function
	RealLaserTarget(const RealLaserTarget& _Other) = delete;
	RealLaserTarget(RealLaserTarget&& _Other) noexcept = delete;
	RealLaserTarget& operator=(const RealLaserTarget& _Other) = delete;
	RealLaserTarget& operator=(RealLaserTarget&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:



};




#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class FlowerBullet : public UnitBase
{
public:
	// constrcuter destructer
	FlowerBullet();
	~FlowerBullet();

	// delete Function
	FlowerBullet(const FlowerBullet& _Other) = delete;
	FlowerBullet(FlowerBullet&& _Other) noexcept = delete;
	FlowerBullet& operator=(const FlowerBullet& _Other) = delete;
	FlowerBullet& operator=(FlowerBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn PlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other);



};


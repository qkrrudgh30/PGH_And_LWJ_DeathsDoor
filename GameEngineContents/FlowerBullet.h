

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class FlowerBulletEff;
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

	std::vector<std::shared_ptr<FlowerBulletEff>> m_vFlowerEff = {};
	CollisionReturn PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);



};


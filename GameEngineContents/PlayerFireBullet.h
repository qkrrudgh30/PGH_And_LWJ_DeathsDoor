
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerFireBulletEff;
class PlayerFireBullet : public UnitBase
{
public:
	// constrcuter destructer
	PlayerFireBullet();
	~PlayerFireBullet();

	// delete Function
	PlayerFireBullet(const PlayerFireBullet& _Other) = delete;
	PlayerFireBullet(PlayerFireBullet&& _Other) noexcept = delete;
	PlayerFireBullet& operator=(const PlayerFireBullet& _Other) = delete;
	PlayerFireBullet& operator=(PlayerFireBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:

	float m_fEffTime = 0.1f;

	std::vector<std::shared_ptr<PlayerFireBulletEff>> m_vFlowerEff = {};
	CollisionReturn PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);



};


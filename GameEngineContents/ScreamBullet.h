
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class ScreamBullet : public UnitBase
{
public:
	// constrcuter destructer
	ScreamBullet();
	~ScreamBullet();

	// delete Function
	ScreamBullet(const ScreamBullet& _Other) = delete;
	ScreamBullet(ScreamBullet&& _Other) noexcept = delete;
	ScreamBullet& operator=(const ScreamBullet& _Other) = delete;
	ScreamBullet& operator=(ScreamBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);



};



#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class SnapBullet : public UnitBase
{
public:
	// constrcuter destructer
	SnapBullet();
	~SnapBullet();

	// delete Function
	SnapBullet(const SnapBullet& _Other) = delete;
	SnapBullet(SnapBullet&& _Other) noexcept = delete;
	SnapBullet& operator=(const SnapBullet& _Other) = delete;
	SnapBullet& operator=(SnapBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn PlayerCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);



};


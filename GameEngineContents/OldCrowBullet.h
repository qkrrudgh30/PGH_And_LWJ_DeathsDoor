

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class OldCrowFog;
class OldCrowBullet : public UnitBase
{
public:
	// constrcuter destructer
	OldCrowBullet();
	~OldCrowBullet();

	// delete Function
	OldCrowBullet(const OldCrowBullet& _Other) = delete;
	OldCrowBullet(OldCrowBullet&& _Other) noexcept = delete;
	OldCrowBullet& operator=(const OldCrowBullet& _Other) = delete;
	OldCrowBullet& operator=(OldCrowBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	int CorwCount = 0;
	float4 MoveDir = {};
	bool m_bAttCheck = false;

	std::vector<std::shared_ptr<OldCrowFog>> m_vOldCrowFog = {};



	CollisionReturn MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);

	CollisionReturn PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);



};


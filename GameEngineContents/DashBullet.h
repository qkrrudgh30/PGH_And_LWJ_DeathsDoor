

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class OldCrow;
class DashBullet : public UnitBase
{
public:
	// constrcuter destructer
	DashBullet();
	~DashBullet();

	// delete Function
	DashBullet(const DashBullet& _Other) = delete;
	DashBullet(DashBullet&& _Other) noexcept = delete;
	DashBullet& operator=(const DashBullet& _Other) = delete;
	DashBullet& operator=(DashBullet&& _Other) noexcept = delete;
public:
	bool m_bHookBack = false;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:

	std::weak_ptr<OldCrow> m_OldCorw;

	int A = 0;


	bool m_bGoCheck = false;
	bool m_bBackCheck = false;


	bool	m_bHitCheck = false;
	float m_ftrailTime = 0.f;
	CollisionReturn PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);


};


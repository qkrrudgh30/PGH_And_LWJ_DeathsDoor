
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class SnapTarGet;
class BillboardRenderer;
class FlowerBulletEff;
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
	std::shared_ptr<BillboardRenderer> sptrTestPicture;
	std::vector<std::shared_ptr<FlowerBulletEff>> m_vFlowerEff = {};
	CollisionReturn PlayerCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);

public:
	float m_fTime = 0.f;
	float m_fDownSpeed = 0.f;
	std::weak_ptr<SnapTarGet> m_pTarget = {};
	float m_fEffTime = 0.1f;
};


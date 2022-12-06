


#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class DashBullet;
class OldCrow;
class PlayerHookAtt;
class DashTrail : public UnitBase
{
public:
	// constrcuter destructer
	DashTrail();
	~DashTrail();

	// delete Function
	DashTrail(const DashTrail& _Other) = delete;
	DashTrail(DashTrail&& _Other) noexcept = delete;
	DashTrail& operator=(const DashTrail& _Other) = delete;
	DashTrail& operator=(DashTrail&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:
	std::weak_ptr<DashBullet> m_cHook;
	std::weak_ptr<OldCrow> m_OldCorw;
};


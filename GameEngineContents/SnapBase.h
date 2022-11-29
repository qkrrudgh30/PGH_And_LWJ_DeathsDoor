
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class SnapBase : public UnitBase
{
public:
	// constrcuter destructer
	SnapBase();
	~SnapBase();

	// delete Function
	SnapBase(const SnapBase& _Other) = delete;
	SnapBase(SnapBase&& _Other) noexcept = delete;
	SnapBase& operator=(const SnapBase& _Other) = delete;
	SnapBase& operator=(SnapBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	bool m_bBulletcheck[10] = {};
	float m_fMakeTime = 0.f;


};


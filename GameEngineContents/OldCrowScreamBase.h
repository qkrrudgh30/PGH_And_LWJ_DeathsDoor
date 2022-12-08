

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class OldCrowScreamBase : public UnitBase
{
public:
	// constrcuter destructer
	OldCrowScreamBase();
	~OldCrowScreamBase();

	// delete Function
	OldCrowScreamBase(const OldCrowScreamBase& _Other) = delete;
	OldCrowScreamBase(OldCrowScreamBase&& _Other) noexcept = delete;
	OldCrowScreamBase& operator=(const OldCrowScreamBase& _Other) = delete;
	OldCrowScreamBase& operator=(OldCrowScreamBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:

	int m_iCount = 0;
	int m_iCountMax = 20;


	bool m_bBulletcheck[10] = {};
	float m_fMakeTime = 0.f;


};


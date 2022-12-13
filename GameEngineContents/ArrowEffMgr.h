

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class ArrowEffMgr : public UnitBase
{
public:
	// constrcuter destructer
	ArrowEffMgr();
	~ArrowEffMgr();

	// delete Function
	ArrowEffMgr(const ArrowEffMgr& _Other) = delete;
	ArrowEffMgr(ArrowEffMgr&& _Other) noexcept = delete;
	ArrowEffMgr& operator=(const ArrowEffMgr& _Other) = delete;
	ArrowEffMgr& operator=(ArrowEffMgr&& _Other) noexcept = delete;

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


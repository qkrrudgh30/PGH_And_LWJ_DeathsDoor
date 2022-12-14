
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class SWEffMgr : public UnitBase
{
public:
	// constrcuter destructer
	SWEffMgr();
	~SWEffMgr();

	// delete Function
	SWEffMgr(const SWEffMgr& _Other) = delete;
	SWEffMgr(SWEffMgr&& _Other) noexcept = delete;
	SWEffMgr& operator=(const SWEffMgr& _Other) = delete;
	SWEffMgr& operator=(SWEffMgr&& _Other) noexcept = delete;

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


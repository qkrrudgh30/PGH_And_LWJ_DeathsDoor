


#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class ScreamMgr : public UnitBase
{
public:
	// constrcuter destructer
	ScreamMgr();
	~ScreamMgr();

	// delete Function
	ScreamMgr(const ScreamMgr& _Other) = delete;
	ScreamMgr(ScreamMgr&& _Other) noexcept = delete;
	ScreamMgr& operator=(const ScreamMgr& _Other) = delete;
	ScreamMgr& operator=(ScreamMgr&& _Other) noexcept = delete;

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


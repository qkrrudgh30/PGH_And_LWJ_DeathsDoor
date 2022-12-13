
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class Firemgr : public UnitBase
{
public:
	// constrcuter destructer
	Firemgr();
	~Firemgr();

	// delete Function
	Firemgr(const Firemgr& _Other) = delete;
	Firemgr(Firemgr&& _Other) noexcept = delete;
	Firemgr& operator=(const Firemgr& _Other) = delete;
	Firemgr& operator=(Firemgr&& _Other) noexcept = delete;

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


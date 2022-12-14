

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PalyerFireMgr : public UnitBase
{
public:
	// constrcuter destructer
	PalyerFireMgr();
	~PalyerFireMgr();

	// delete Function
	PalyerFireMgr(const PalyerFireMgr& _Other) = delete;
	PalyerFireMgr(PalyerFireMgr&& _Other) noexcept = delete;
	PalyerFireMgr& operator=(const PalyerFireMgr& _Other) = delete;
	PalyerFireMgr& operator=(PalyerFireMgr&& _Other) noexcept = delete;



	bool	m_bColorBlue = false;
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


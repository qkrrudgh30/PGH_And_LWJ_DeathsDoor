
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class OldCrowFeather;
class FeatherMgr : public UnitBase
{
public:
	// constrcuter destructer
	FeatherMgr();
	~FeatherMgr();

	// delete Function
	FeatherMgr(const FeatherMgr& _Other) = delete;
	FeatherMgr(FeatherMgr&& _Other) noexcept = delete;
	FeatherMgr& operator=(const FeatherMgr& _Other) = delete;
	FeatherMgr& operator=(FeatherMgr&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:

public:
	float4 m_StartPos = {};

	std::vector<std::shared_ptr<OldCrowFeather>> m_vFeather = {};
	std::vector<std::shared_ptr<OldCrowFeather>> m_vFeather2 = {};

	bool DeathCheck = false;

	int m_iFeatherCount = 0;
	bool StartTimeCheck = false;
};


#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalContentsValue.h"







// Ό³Έν :
class UnitBase : public GameEngineActor
{
public:
	// constrcuter destructer
	UnitBase();
	~UnitBase();

	// delete Function
	UnitBase(const UnitBase& _Other) = delete;
	UnitBase(UnitBase&& _Other) noexcept = delete;
	UnitBase& operator=(const UnitBase& _Other) = delete;
	UnitBase& operator=(UnitBase&& _Other) noexcept = delete;

protected:
	GameEngineDefaultRenderer* Renderer;
	GameEngineCollision* Collision;
	GameEngineCollision* AttCollision;
public:
	GameEngineStateManager StateManager;

public:
	UINFO	m_Info;
	float m_fLifeTime;
	float m_fSpeed;


	float4 m_fHitPos = {0};
	bool m_bHitCheck = false;
	float4 m_fHitDir = {0};
	float hitTime = 0.f;

private:

};


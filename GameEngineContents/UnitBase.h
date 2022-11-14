#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalContentsValue.h"







// Ό³Έν :
class GameEngineFBXStaticRenderer;
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
	std::shared_ptr < GameEngineDefaultRenderer> Renderer;
	std::shared_ptr < GameEngineFBXStaticRenderer> FBXStaticRenderer;
	std::shared_ptr <GameEngineFBXAnimationRenderer> FBXAnimationRenderer;
	std::shared_ptr < GameEngineCollision> Collision;
	std::shared_ptr < GameEngineCollision> AttCollision;
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


	float m_fHitTime = 0.f;
	bool m_bhitCheck = false;

private:

};


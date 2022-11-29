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
	
	void BaseUpdate(float _DeltaTime);




public:
	std::shared_ptr < GameEngineDefaultRenderer> Renderer;
	std::shared_ptr < GameEngineFBXStaticRenderer> FBXStaticRenderer;
	std::shared_ptr <GameEngineFBXAnimationRenderer> FBXAnimationRenderer;
	std::shared_ptr < GameEngineTextureRenderer> TexRenderer;
	std::shared_ptr < GameEngineCollision> Collision;
	std::shared_ptr < GameEngineCollision> AttCollision;
	GameEngineRenderingEvent Event;
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

public:
	void CameraShake(float _Time);


private:
	float ShakeMaxTime = 0.f;
	float ShakeTime = 0.f;

	float ShakeForce = 1000.f;
	float ShakeTCheck = 0.f;
	bool ShakeDirCheck = false;


	bool ShakeCheck = false;

	float4 CameraLastDir = {};


};


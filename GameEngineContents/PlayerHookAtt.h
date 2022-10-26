
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerHookAtt : public UnitBase
{
public:
	// constrcuter destructer
	PlayerHookAtt();
	~PlayerHookAtt();

	// delete Function
	PlayerHookAtt(const PlayerHookAtt& _Other) = delete;
	PlayerHookAtt(PlayerHookAtt&& _Other) noexcept = delete;
	PlayerHookAtt& operator=(const PlayerHookAtt& _Other) = delete;
	PlayerHookAtt& operator=(PlayerHookAtt&& _Other) noexcept = delete;
public:
	bool m_bHookBack = false;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	bool	m_bHitCheck = false;
	float m_ftrailTime = 0.f;
	CollisionReturn MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn PlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn TrailCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


};


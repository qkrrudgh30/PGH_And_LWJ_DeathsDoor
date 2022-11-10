

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerHookAtt;
class PlayerHookTrail : public UnitBase
{
public:
	// constrcuter destructer
	PlayerHookTrail();
	~PlayerHookTrail();

	// delete Function
	PlayerHookTrail(const PlayerHookTrail& _Other) = delete;
	PlayerHookTrail(PlayerHookTrail&& _Other) noexcept = delete;
	PlayerHookTrail& operator=(const PlayerHookTrail& _Other) = delete;
	PlayerHookTrail& operator=(PlayerHookTrail&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
public:
	std::weak_ptr<PlayerHookAtt> m_cHook;
};


#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerSWAttSlide : public UnitBase
{
public:
	// constrcuter destructer
	PlayerSWAttSlide();
	~PlayerSWAttSlide();

	// delete Function
	PlayerSWAttSlide(const PlayerSWAttSlide& _Other) = delete;
	PlayerSWAttSlide(PlayerSWAttSlide&& _Other) noexcept = delete;
	PlayerSWAttSlide& operator=(const PlayerSWAttSlide& _Other) = delete;
	PlayerSWAttSlide& operator=(PlayerSWAttSlide&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);



};


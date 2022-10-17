#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerSWAtt3 : public UnitBase
{
public:
	// constrcuter destructer
	PlayerSWAtt3();
	~PlayerSWAtt3();

	// delete Function
	PlayerSWAtt3(const PlayerSWAtt3& _Other) = delete;
	PlayerSWAtt3(PlayerSWAtt3&& _Other) noexcept = delete;
	PlayerSWAtt3& operator=(const PlayerSWAtt3& _Other) = delete;
	PlayerSWAtt3& operator=(PlayerSWAtt3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);



};


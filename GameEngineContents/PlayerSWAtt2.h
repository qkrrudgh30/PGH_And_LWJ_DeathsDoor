#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerSWAtt2 : public UnitBase
{
public:
	// constrcuter destructer
	PlayerSWAtt2();
	~PlayerSWAtt2();

	// delete Function
	PlayerSWAtt2(const PlayerSWAtt2& _Other) = delete;
	PlayerSWAtt2(PlayerSWAtt2&& _Other) noexcept = delete;
	PlayerSWAtt2& operator=(const PlayerSWAtt2& _Other) = delete;
	PlayerSWAtt2& operator=(PlayerSWAtt2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);



};


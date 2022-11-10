#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerSWAtt1 : public UnitBase
{
public:
	// constrcuter destructer
	PlayerSWAtt1();
	~PlayerSWAtt1();

	// delete Function
	PlayerSWAtt1(const PlayerSWAtt1& _Other) = delete;
	PlayerSWAtt1(PlayerSWAtt1&& _Other) noexcept = delete;
	PlayerSWAtt1& operator=(const PlayerSWAtt1& _Other) = delete;
	PlayerSWAtt1& operator=(PlayerSWAtt1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:


	CollisionReturn MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);



};


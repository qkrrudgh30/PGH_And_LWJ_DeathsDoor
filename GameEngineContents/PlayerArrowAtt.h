
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerArrowAtt : public UnitBase
{
public:
	// constrcuter destructer
	PlayerArrowAtt();
	~PlayerArrowAtt();

	// delete Function
	PlayerArrowAtt(const PlayerArrowAtt& _Other) = delete;
	PlayerArrowAtt(PlayerArrowAtt&& _Other) noexcept = delete;
	PlayerArrowAtt& operator=(const PlayerArrowAtt& _Other) = delete;
	PlayerArrowAtt& operator=(PlayerArrowAtt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	

	CollisionReturn MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);



};


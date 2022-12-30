
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :
class PlayerShadow : public UnitBase
{
public:
	// constrcuter destructer
	PlayerShadow();
	~PlayerShadow();

	// delete Function
	PlayerShadow(const PlayerShadow& _Other) = delete;
	PlayerShadow(PlayerShadow&& _Other) noexcept = delete;
	PlayerShadow& operator=(const PlayerShadow& _Other) = delete;
	PlayerShadow& operator=(PlayerShadow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:



};


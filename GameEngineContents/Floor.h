#pragma once
#include "UnitBase.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class UnitBase;
class Floor : public UnitBase
{
public:
	// constrcuter destructer
	Floor();
	~Floor();

	// delete Function
	Floor(const Floor& _Other) = delete;
	Floor(Floor&& _Other) noexcept = delete;
	Floor& operator=(const Floor& _Other) = delete;
	Floor& operator=(Floor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


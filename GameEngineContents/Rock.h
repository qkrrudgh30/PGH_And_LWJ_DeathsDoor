#pragma once
#include "UnitBase.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class UnitBase;
class Rock : public UnitBase
{
public:
	// constrcuter destructer
	Rock();
	~Rock();

	// delete Function
	Rock(const Rock& _Other) = delete;
	Rock(Rock&& _Other) noexcept = delete;
	Rock& operator=(const Rock& _Other) = delete;
	Rock& operator=(Rock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


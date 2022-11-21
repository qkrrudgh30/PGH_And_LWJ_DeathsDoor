#pragma once
#include "UnitBase.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class UnitBase;
class Hall : public UnitBase
{
public:
	// constrcuter destructer
	Hall();
	~Hall();

	// delete Function
	Hall(const Hall& _Other) = delete;
	Hall(Hall&& _Other) noexcept = delete;
	Hall& operator=(const Hall& _Other) = delete;
	Hall& operator=(Hall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


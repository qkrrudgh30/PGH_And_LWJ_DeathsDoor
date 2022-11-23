
#pragma once
#include "UnitBase.h"

// Ό³Έν :
class Spike : public UnitBase
{
public:
	// constrcuter destructer
	Spike();
	~Spike();

	// delete Function
	Spike(const Spike& _Other) = delete;
	Spike(Spike&& _Other) noexcept = delete;
	Spike& operator=(const Spike& _Other) = delete;
	Spike& operator=(Spike&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


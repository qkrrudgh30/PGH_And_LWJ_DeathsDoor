#pragma once
#include "UnitBase.h"

// Ό³Έν :
class TestStaticActor : public UnitBase
{
public:
	// constrcuter destructer
	TestStaticActor();
	~TestStaticActor();

	// delete Function
	TestStaticActor(const TestStaticActor& _Other) = delete;
	TestStaticActor(TestStaticActor&& _Other) noexcept = delete;
	TestStaticActor& operator=(const TestStaticActor& _Other) = delete;
	TestStaticActor& operator=(TestStaticActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};


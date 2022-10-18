#pragma once
#include "UnitBase.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class UnitBase;
class TestActor : public UnitBase
{
public:
	// constrcuter destructer
	TestActor();
	~TestActor();

	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float m_fHeight;
	float m_fWidth;
	float m_fDepth;

	GameEngineDefaultRenderer* m_ptrRenderer;

};


#pragma once
#include "UnitBase.h"

// Ό³Έν :
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

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleStart(const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info) {}
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void StunStart(const StateInfo& _Info);
	void StunEnd(const StateInfo& _Info) {}
	void StunUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttStart(const StateInfo& _Info);
	void AttEnd(const StateInfo& _Info);
	void AttUpdate(float _DeltaTime, const StateInfo& _Info);

	void AniTestActor_Att(const GameEngineRenderingEvent& _Data);
	void AniTestActor_Idle(const GameEngineRenderingEvent& _Data) {}
	void AniTestActor_Move(const GameEngineRenderingEvent& _Data) {}


private:

};


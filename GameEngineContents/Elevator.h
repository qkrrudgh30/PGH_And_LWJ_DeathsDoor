
#pragma once
#include "UnitBase.h"



// Ό³Έν :
class Elevator : public UnitBase
{
public:
	// constrcuter destructer
	Elevator();
	~Elevator();

	// delete Function
	Elevator(const Elevator& _Other) = delete;
	Elevator(Elevator&& _Other) noexcept = delete;
	Elevator& operator=(const Elevator& _Other) = delete;
	Elevator& operator=(Elevator&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}



	float m_fColTime = 0.f;

private:
	CollisionReturn CollisionPlayer(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);

};


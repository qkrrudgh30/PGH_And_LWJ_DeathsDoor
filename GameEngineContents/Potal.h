

#pragma once
#include "UnitBase.h"


enum class PotalType
{
	LoginToStage1,
	Stage1ToStage2,
	Stage2ToStage3,
	Stage3ToStage4,
	Stage4ToStage5,
	Stage5ToStageBoss,
	Stage5ToStage4,
	Stage4ToStage3,
	Stage3ToStage2,
	Stage2ToStage1,
	Stage1ToSLogin,

};


// Ό³Έν :
class Potal : public UnitBase
{
public:
	// constrcuter destructer
	Potal();
	~Potal();

	// delete Function
	Potal(const Potal& _Other) = delete;
	Potal(Potal&& _Other) noexcept = delete;
	Potal& operator=(const Potal& _Other) = delete;
	Potal& operator=(Potal&& _Other) noexcept = delete;


	PotalType m_PotalType;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}


private:
	CollisionReturn CollisionPlayer(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);

};


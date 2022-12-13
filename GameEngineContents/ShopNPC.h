#pragma once
#include "UnitBase.h"



// Ό³Έν :
class ShopNPC : public UnitBase
{
public:
	// constrcuter destructer
	ShopNPC();
	~ShopNPC();

	// delete Function
	ShopNPC(const ShopNPC& _Other) = delete;
	ShopNPC(ShopNPC&& _Other) noexcept = delete;
	ShopNPC& operator=(const ShopNPC& _Other) = delete;
	ShopNPC& operator=(ShopNPC&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void WriteStart(const StateInfo& _Info);
	void WriteEnd(const StateInfo& _Info);
	void WriteUpdate(float _DeltaTime, const StateInfo& _Info);


	void IdleStart(const StateInfo& _Info);
	void IdleEnd(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);


	void Ani_W(const GameEngineRenderingEvent& _Data);
	void Ani_I(const GameEngineRenderingEvent& _Data);
private:
	CollisionReturn CollisionPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

};


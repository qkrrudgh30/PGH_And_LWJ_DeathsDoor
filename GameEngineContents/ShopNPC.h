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


private:
	CollisionReturn CollisionPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

};


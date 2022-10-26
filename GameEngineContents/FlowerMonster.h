#pragma once

// Ό³Έν :
class FlowerMonster
{
public:
	// constrcuter destructer
	FlowerMonster();
	~FlowerMonster();

	// delete Function
	FlowerMonster(const FlowerMonster& _Other) = delete;
	FlowerMonster(FlowerMonster&& _Other) noexcept = delete;
	FlowerMonster& operator=(const FlowerMonster& _Other) = delete;
	FlowerMonster& operator=(FlowerMonster&& _Other) noexcept = delete;

protected:

private:

};


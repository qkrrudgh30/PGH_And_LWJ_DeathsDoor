#pragma once

// Ό³Έν :
class playerFireBoom
{
public:
	// constrcuter destructer
	playerFireBoom();
	~playerFireBoom();

	// delete Function
	playerFireBoom(const playerFireBoom& _Other) = delete;
	playerFireBoom(playerFireBoom&& _Other) noexcept = delete;
	playerFireBoom& operator=(const playerFireBoom& _Other) = delete;
	playerFireBoom& operator=(playerFireBoom&& _Other) noexcept = delete;

protected:

private:

};


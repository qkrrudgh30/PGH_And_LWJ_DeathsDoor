#pragma once

// Ό³Έν :
class PlayerHookTrail
{
public:
	// constrcuter destructer
	PlayerHookTrail();
	~PlayerHookTrail();

	// delete Function
	PlayerHookTrail(const PlayerHookTrail& _Other) = delete;
	PlayerHookTrail(PlayerHookTrail&& _Other) noexcept = delete;
	PlayerHookTrail& operator=(const PlayerHookTrail& _Other) = delete;
	PlayerHookTrail& operator=(PlayerHookTrail&& _Other) noexcept = delete;

protected:

private:

};


#pragma once
#include "UnitBase.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class UnitBase;
class ROOM_Enter : public UnitBase
{
public:
	// constrcuter destructer
	ROOM_Enter();
	~ROOM_Enter();

	// delete Function
	ROOM_Enter(const ROOM_Enter& _Other) = delete;
	ROOM_Enter(ROOM_Enter&& _Other) noexcept = delete;
	ROOM_Enter& operator=(const ROOM_Enter& _Other) = delete;
	ROOM_Enter& operator=(ROOM_Enter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


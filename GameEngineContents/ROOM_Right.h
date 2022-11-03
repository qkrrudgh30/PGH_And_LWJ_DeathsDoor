#pragma once
#include "UnitBase.h"

// Ό³Έν :
class ROOM_Right : public UnitBase
{
public:
	// constrcuter destructer
	ROOM_Right();
	~ROOM_Right();

	// delete Function
	ROOM_Right(const ROOM_Right& _Other) = delete;
	ROOM_Right(ROOM_Right&& _Other) noexcept = delete;
	ROOM_Right& operator=(const ROOM_Right& _Other) = delete;
	ROOM_Right& operator=(ROOM_Right&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


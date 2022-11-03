#pragma once
#include "UnitBase.h"

// Ό³Έν :
class ROOM_Left : public UnitBase
{
public:
	// constrcuter destructer
	ROOM_Left();
	~ROOM_Left();

	// delete Function
	ROOM_Left(const ROOM_Left& _Other) = delete;
	ROOM_Left(ROOM_Left&& _Other) noexcept = delete;
	ROOM_Left& operator=(const ROOM_Left& _Other) = delete;
	ROOM_Left& operator=(ROOM_Left&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


#pragma once
#include "UnitBase.h"

// Ό³Έν :
class ROOM_Far : public UnitBase
{
public:
	// constrcuter destructer
	ROOM_Far();
	~ROOM_Far();

	// delete Function
	ROOM_Far(const ROOM_Far& _Other) = delete;
	ROOM_Far(ROOM_Far&& _Other) noexcept = delete;
	ROOM_Far& operator=(const ROOM_Far& _Other) = delete;
	ROOM_Far& operator=(ROOM_Far&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


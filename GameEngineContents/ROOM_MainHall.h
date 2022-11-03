#pragma once
#include "UnitBase.h"

// Ό³Έν :
class ROOM_MainHall : public UnitBase
{
public:
	// constrcuter destructer
	ROOM_MainHall();
	~ROOM_MainHall();

	// delete Function
	ROOM_MainHall(const ROOM_MainHall& _Other) = delete;
	ROOM_MainHall(ROOM_MainHall&& _Other) noexcept = delete;
	ROOM_MainHall& operator=(const ROOM_MainHall& _Other) = delete;
	ROOM_MainHall& operator=(ROOM_MainHall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 ResultColor;

};


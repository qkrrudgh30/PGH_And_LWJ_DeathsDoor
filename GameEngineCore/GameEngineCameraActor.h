#pragma once
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

// Ό³Έν :
class GameEngineLevel;
class GameEngineCameraActor : public GameEngineActor
{

public:
	// constrcuter destructer
	GameEngineCameraActor();
	~GameEngineCameraActor();

	// delete Function
	GameEngineCameraActor(const GameEngineCameraActor& _Other) = delete;
	GameEngineCameraActor(GameEngineCameraActor&& _Other) noexcept = delete;
	GameEngineCameraActor& operator=(const GameEngineCameraActor& _Other) = delete;
	GameEngineCameraActor& operator=(GameEngineCameraActor&& _Other) noexcept = delete;

	GameEngineCamera* GetCameraComponent()
	{
		return CameraComponent;
	}

	void FreeCameraModeOnOff();

	inline bool IsFreeCameraMode() 
	{
		return FreeCameraMode;
	}

	void Update(float _DeltaTime) override;

protected:
	void Start() override;
	void End() override;

private:
	bool FreeCameraMode;
	float Speed;
	float RotSpeed;

	GameEngineCamera* CameraComponent;
	GameEngineTransform OriginTrans;
	CAMERAPROJECTIONMODE PrevMode;
};


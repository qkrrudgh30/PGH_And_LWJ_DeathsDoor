#pragma once
#include "GameEngineTransformComponent.h"

class GameEngineLight;
struct LightData
{
	friend GameEngineLight;

	float4x4 LightViewMatrix;
	float4x4 LightProjectionMatrix;
	float LightTargetSizeX;
	float LightTargetSizeY;
	float LightNear;
	float LightFar;

	float4 LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
	float DifLightPower = 1.0f;
	float SpcLightPower = 1.0f;
	float AmbLightPower = 1.0f;
	float SpcPow = 50.0f;
	float4 LightPos;
	float4 LightDir;

private:
	float4 LightRevDir;

	float4 ViewLightPos;
	float4 ViewLightDir;
	float4 ViewLightRevDir;

	float4 CameraPosition;

};

struct LightDatas
{
	int Count;
	LightData Lights[128];
};

// Ό³Έν :
class GameEngineCamera;
class GameEngineLight
	: public GameEngineActor
{
	friend GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineLight();
	~GameEngineLight();

	// delete Function
	GameEngineLight(const GameEngineLight& _Other) = delete;
	GameEngineLight(GameEngineLight&& _Other) noexcept = delete;
	GameEngineLight& operator=(const GameEngineLight& _Other) = delete;
	GameEngineLight& operator=(GameEngineLight&& _Other) noexcept = delete;

	LightData& GetLightData()
	{
		return Data;
	}

	void Start() override;

	void Update(float _DeltaTime) override;

	void ShadowTargetSetting();

protected:

private:
	void LightDataUpdate(GameEngineCamera* _Camera);

	std::shared_ptr<class GameEngineRenderTarget> ShadowTarget;

	LightData Data;
};


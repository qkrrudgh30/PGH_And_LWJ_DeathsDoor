#pragma once
#include "GameEngineTransformComponent.h"

struct LightData
{
	float4 LightPos;
	float4 LightDir;
	float4 LightRevDir;
};

// Ό³Έν :
class GameEngineLight
	: public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineLight();
	~GameEngineLight();

	// delete Function
	GameEngineLight(const GameEngineLight& _Other) = delete;
	GameEngineLight(GameEngineLight&& _Other) noexcept = delete;
	GameEngineLight& operator=(const GameEngineLight& _Other) = delete;
	GameEngineLight& operator=(GameEngineLight&& _Other) noexcept = delete;

protected:

private:
	LightData Data;
};


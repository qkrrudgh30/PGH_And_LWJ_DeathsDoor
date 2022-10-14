#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

// Ό³Έν :
class GameEngineSampler : public GameEngineRes<GameEngineSampler>
{
public:
	static GameEngineSampler* Create(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info);

public:
	// constrcuter destructer
	GameEngineSampler();
	~GameEngineSampler();

	// delete Function
	GameEngineSampler(const GameEngineSampler& _Other) = delete;
	GameEngineSampler(GameEngineSampler&& _Other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(GameEngineSampler&& _Other) noexcept = delete;

	void VSSetting(int _BindPoint);
	void PSSetting(int _BindPoint);

protected:
	void Create(const D3D11_SAMPLER_DESC& _Info);

private:
	ID3D11SamplerState* State;
	D3D11_SAMPLER_DESC Desc;
};


#pragma once
#include "GameEngineShader.h"
#include "GameEngineRes.h"

// Ό³Έν :
class GameEnginePixelShader 
	: public GameEngineShader
	, public GameEngineRes<GameEnginePixelShader>
{
	friend GameEngineShader;
	friend GameEngineRes<GameEnginePixelShader>;

public:
	static GameEnginePixelShader* Load(
		const std::string& _Path, 
		const std::string& _EntryPoint, 
		UINT _VersionHigh = 5, UINT _VersionLow = 0);

	static GameEnginePixelShader* Load(
		const std::string& _Path, 
		const std::string& _Name,
		const std::string& _EntryPoint,
		UINT _VersionHigh, UINT _VersionLow);

private:
	// constrcuter destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();

	// delete Function
	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;

public:
	void Setting();

protected:
	void ShaderCompile(
		const std::string& _Path,
		const std::string& _EntryPoint,
		UINT _VersionHigh, UINT _VersionLow);

private:
	ID3D11PixelShader* ShaderPtr;
};


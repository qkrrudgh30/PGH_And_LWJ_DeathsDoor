#pragma once
#include "GameEngineDevice.h"
#include "GameEngineRes.h"

// Ό³Έν :
class GameEngineLayOutDesc;
class GameEngineVertexShader;
class GameEngineInputLayOut 
	: public GameEngineRes<GameEngineInputLayOut>
	, public std::enable_shared_from_this<GameEngineInputLayOut>
{
public:
	static std::shared_ptr < GameEngineInputLayOut> Create(const GameEngineLayOutDesc& _Desc, std::shared_ptr<GameEngineVertexShader> _Shader);

public:
	// constrcuter destructer
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void CreateRes(const GameEngineLayOutDesc& _Desc, std::shared_ptr<GameEngineVertexShader> _Shader);

	void CreateRes(const GameEngineLayOutDesc& _Desc);

	void Setting();

protected:

private:
	ID3D11InputLayout* InputLayOut;

	
};


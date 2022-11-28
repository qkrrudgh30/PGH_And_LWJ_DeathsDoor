#pragma once
#include "GameEngineNet.h"


// Ό³Έν :
class GameEngineNetClient : public GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNetClient();
	~GameEngineNetClient();

	// delete Function
	GameEngineNetClient(const GameEngineNetClient& _Other) = delete;
	GameEngineNetClient(GameEngineNetClient&& _Other) noexcept = delete;
	GameEngineNetClient& operator=(const GameEngineNetClient& _Other) = delete;
	GameEngineNetClient& operator=(GameEngineNetClient&& _Other) noexcept = delete;

	void Connect(std::string _Ip, int Port);

protected:

private:

};


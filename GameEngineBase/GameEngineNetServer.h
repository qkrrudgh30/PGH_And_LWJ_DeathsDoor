#pragma once
#include "GameEngineNet.h"
// 설명 :
class GameEngineNetServer : public GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNetServer();
	~GameEngineNetServer();

	// delete Function
	GameEngineNetServer(const GameEngineNetServer& _Other) = delete;
	GameEngineNetServer(GameEngineNetServer&& _Other) noexcept = delete;
	GameEngineNetServer& operator=(const GameEngineNetServer& _Other) = delete;
	GameEngineNetServer& operator=(GameEngineNetServer&& _Other) noexcept = delete;

	void Accept(int Port);

protected:


private:
	// 접속자를 받고 서버를 기동시키겠다.
	// 3대 약속
	// SOCKET
	// accpet가 있고
	// connect가 있다.

	// SOCKET의 역할은 크게 2가지가 존재하는데.
	// 1. 내가 어떤 컴퓨터와의 연결이 되어있는지에 대한 핸들
	// 2. 내가 만든 서버를 대표하는 
	SOCKET ServerAccpetSocket;

};


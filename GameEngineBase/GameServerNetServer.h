#pragma once
#include "GameServerNet.h"
#include "GameEngineThread.h"
#include "GameServerDispatcher.h"
// 설명 :
class GameServerNetServer : public GameServerNet
{
public:

	// constrcuter destructer
	GameServerNetServer();
	~GameServerNetServer();

	// delete Function
	//GameServerNetServer(const GameServerNetServer& _Other) = delete;
	//GameServerNetServer(GameServerNetServer&& _Other) noexcept = delete;
	//GameServerNetServer& operator=(const GameServerNetServer& _Other) = delete;
	//GameServerNetServer& operator=(GameServerNetServer&& _Other) noexcept = delete;

	// 이제부터 내가 접속자를 받겠다.
	void Accept(int Port);

	int Send(const char* Data, size_t _Size) {
		return 0;
	}

	int SendPacket(std::shared_ptr<GameServerPacket> _Packet) {
		return 0;
	}

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

	std::atomic<bool> IsRun;

	SOCKET ServerAccpetSocket;

	GameEngineThread AcceptThread;

	std::vector<SOCKET> UserSockets;
	std::vector<GameEngineThread> UserThreads;

	void AcceptFunction(GameEngineThread* Thread);

	void UserFunction(GameEngineThread* Thread, SOCKET _Socket);

};


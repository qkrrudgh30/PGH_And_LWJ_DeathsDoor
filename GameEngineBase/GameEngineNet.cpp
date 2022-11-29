#include "PreCompile.h"
#include "GameEngineNet.h"
#include "GameEngineDebug.h"

GameEngineNet::GameEngineNet() 
{
}

GameEngineNet::~GameEngineNet() 
{
}

void GameEngineNet::WindowNetStartUp()
{
	static bool IsStart = false;

	if (true == IsStart)
	{
		return;
	}

	WSAData wsaData;
	int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	// winapi에서는 이걸 실행하지 않으면 소켓통신 자체를 못하게 막아놨다.
	if (SOCKET_ERROR == errorCode)
	{
		MsgBoxAssert("winapi server socket startup fail");
		return;
	}

	IsStart = true;
}

int GameEngineNet::Send(SOCKET _Socket, const char* Data, size_t _Size)
{
	return send(_Socket, Data, static_cast<int>(_Size), 0);
}

int GameEngineNet::Send(const char* Data, size_t _Size)
{
	return 0;
}
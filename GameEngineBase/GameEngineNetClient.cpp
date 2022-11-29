#include "PreCompile.h"
#include "GameEngineNetClient.h"
#include "GameEngineDebug.h"

GameEngineNetClient::GameEngineNetClient() 
{
}

GameEngineNetClient::~GameEngineNetClient() 
{
}

void GameEngineNetClient::Connect(std::string _Ip, int Port)
{
	GameEngineNet::WindowNetStartUp();

	if (0 == SessionSocket)
	{
		SessionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (INVALID_SOCKET == SessionSocket)
		{
			return;
		}
	}

	SOCKADDR_IN Add;
	Add.sin_family = AF_INET; 
	Add.sin_port = htons(Port);

	const char* IP = _Ip.c_str();

	if (SOCKET_ERROR == inet_pton(AF_INET, IP, &Add.sin_addr))
	{
		return;
	}

	int Len = sizeof(SOCKADDR_IN);
	if (SOCKET_ERROR == connect(SessionSocket, (const sockaddr*)&Add, Len))
	{
		MsgBoxAssert("서버 접속에 실패했습니다");
		return;
	}

	int a = 0;
}

int GameEngineNetClient::Send(const char* Data, size_t _Size)
{
	return GameEngineNet::Send(SessionSocket, Data, _Size);
}
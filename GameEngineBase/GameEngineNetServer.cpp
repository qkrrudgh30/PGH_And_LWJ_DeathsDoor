#include "PreCompile.h"
#include "GameEngineNetServer.h"


GameEngineNetServer::GameEngineNetServer()
{
}

GameEngineNetServer::~GameEngineNetServer()
{
}

void GameEngineNetServer::Accept(int Port)
{
	GameEngineNet::WindowNetStartUp();

	// windowapi에서 서버통신을 하려면 무조건 소켓을 우선적으로 만들어줘야 한다.

	// 00000001 00000000 00000000 00000000
	// int a = 1;

	// 
	SOCKADDR_IN Add;
	Add.sin_family = AF_INET; // ip4 주소

	// 1   1   1   1     2
	// 255.255.255.255 + 30001
	// 127.0.0.1 + 30001
	// 1.0.0.127 + 30001

	Add.sin_port = htons(Port);

	// sin_addr
	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
	{
		return;
	}

	// 위에서 만든 주소로 서버를 열 소켓
	// ServerAccpetSocket = socket(AF_INET, SOCKET_);

}
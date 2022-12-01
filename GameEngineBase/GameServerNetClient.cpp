#include "PreCompile.h"
#include "GameServerNetClient.h"
#include "GameEngineDebug.h"

GameServerNetClient::GameServerNetClient() 
{
}

GameServerNetClient::~GameServerNetClient() 
{
}

void GameServerNetClient::Connect(std::string _Ip, int Port)
{
	GameServerNet::WindowNetStartUp();

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

int GameServerNetClient::Send(const char* Data, size_t _Size)
{
	return GameServerNet::Send(SessionSocket, Data, _Size);
}

int GameServerNetClient::SendPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	GameServerSerializer Ser = PacketSerializ(_Packet);
	return Send(Ser.GetDataPtrConvert<const char*>(), Ser.GetOffSet());
}
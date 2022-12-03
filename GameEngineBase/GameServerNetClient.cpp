#include "PreCompile.h"
#include "GameServerNetClient.h"
#include "GameEngineDebug.h"

GameServerNetClient::GameServerNetClient() 
{
	IsHost = false;
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

	RecvThread.Start("RecvThread", std::bind(&GameServerNetClient::RecvThreadFunction, this, &RecvThread));
}

int GameServerNetClient::Send(const char* Data, size_t _Size)
{
	return GameServerNet::NetSend(SessionSocket, Data, _Size);
}

int GameServerNetClient::SendPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	GameServerSerializer Ser = PacketSerializ(_Packet);
	return Send(Ser.GetDataPtrConvert<const char*>(), Ser.GetOffSet());
}

void GameServerNetClient::RecvThreadFunction(GameEngineThread* _Thread)
{
	char Packet[1024] = { 0 };

	while (true)
	{
		int Result = recv(SessionSocket, Packet, sizeof(Packet), 0);

		if (-1 == Result)
		{
			// MsgBoxAssert("네트워크 에러");
			// 서버가 꺼졌어.
			// 상대가 꺼졌어.
			return;
		}

		GameServerSerializer Ser = GameServerSerializer(Packet, 1024);

		int PacketType;
		int PacketSize;

		memcpy_s(&PacketType, sizeof(int), Ser.GetDataPtr(), sizeof(int));
		memcpy_s(&PacketSize, sizeof(int), Ser.GetDataPtr() + 4, sizeof(int));

		std::shared_ptr<GameServerPacket> Packet = Dis.PacketReturnCallBack(PacketType, PacketSize, Ser);

		Dis.ProcessPacket(Packet);
	}
}
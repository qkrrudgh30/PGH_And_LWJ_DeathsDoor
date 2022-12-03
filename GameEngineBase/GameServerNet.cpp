#include "PreCompile.h"
#include "GameServerNet.h"
#include "GameEngineDebug.h"
#include "GameServerSerializer.h"

GameServerNet::GameServerNet() 
{
}

GameServerNet::~GameServerNet() 
{
}

void GameServerNet::WindowNetStartUp()
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

int GameServerNet::NetSend(SOCKET _Socket, const char* Data, size_t _Size)
{
	return send(_Socket, Data, static_cast<int>(_Size), 0);
}


GameServerSerializer GameServerNet::PacketSerializ(std::shared_ptr<GameServerPacket> _Packet)
{
	GameServerSerializer NewSer = GameServerSerializer();
	_Packet->SerializePacket(NewSer);
	return NewSer;
}

int GameServerNet::NetSendPacket(SOCKET _Socket, std::shared_ptr<GameServerPacket> _Packet)
{
	GameServerSerializer NewSer = PacketSerializ(_Packet);
	return NetSend(_Socket, reinterpret_cast<char*>(NewSer.GetDataPtr()), NewSer.GetOffSet());
}
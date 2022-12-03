#pragma once
#include "GameServerPacket.h"
#include "GameServerDispatcher.h"

// Ό³Έν :
class GameServerNet
{
public:
	static void WindowNetStartUp();

public:
	GameServerDispatcher Dis;
	// constrcuter destructer
	GameServerNet();
	~GameServerNet();

	// delete Function
	GameServerNet(const GameServerNet& _Other) = delete;
	GameServerNet(GameServerNet&& _Other) noexcept = delete;
	GameServerNet& operator=(const GameServerNet& _Other) = delete;
	GameServerNet& operator=(GameServerNet&& _Other) noexcept = delete;

	int NetSend(SOCKET _Socket, const char* Data, size_t _Size);
	int NetSendPacket(SOCKET _Socket, std::shared_ptr<GameServerPacket> _Packet);

	virtual int Send(const char* Data, size_t _Size) = 0;
	virtual int SendPacket(std::shared_ptr<GameServerPacket> _Packet) = 0;

	GameServerSerializer PacketSerializ(std::shared_ptr<GameServerPacket> _Packet);

	bool GetIsHost()
	{
		return IsHost;
	}


protected:
	bool IsHost;


private:

};


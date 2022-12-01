#pragma once
#include "GameServerNet.h"


// Ό³Έν :
class GameServerNetClient : public GameServerNet
{
public:
	// constrcuter destructer
	GameServerNetClient();
	~GameServerNetClient();

	// delete Function
	GameServerNetClient(const GameServerNetClient& _Other) = delete;
	GameServerNetClient(GameServerNetClient&& _Other) noexcept = delete;
	GameServerNetClient& operator=(const GameServerNetClient& _Other) = delete;
	GameServerNetClient& operator=(GameServerNetClient&& _Other) noexcept = delete;

	void Connect(std::string _Ip, int Port);

	int Send(const char* Data, size_t _Size) override;

	int SendPacket(std::shared_ptr<GameServerPacket> _Packet) override;

protected:

private:
	SOCKET SessionSocket;
};


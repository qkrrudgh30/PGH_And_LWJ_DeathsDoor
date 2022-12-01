#pragma once
#include "GameServerSerializer.h"
#include "GameServerPacket.h"
#include <functional>

// 설명 :
class GameServerDispatcher
{
public:
	// constrcuter destructer
	GameServerDispatcher();
	~GameServerDispatcher();

	// delete Function
	GameServerDispatcher(const GameServerDispatcher& _Other) = delete;
	GameServerDispatcher(GameServerDispatcher&& _Other) noexcept = delete;
	GameServerDispatcher& operator=(const GameServerDispatcher& _Other) = delete;
	GameServerDispatcher& operator=(GameServerDispatcher&& _Other) noexcept = delete;

	std::function<std::shared_ptr<GameServerPacket>(int _PacketType, int _PacketSize, GameServerSerializer& Data)> PacketReturnCallBack;

	template<typename EnumType>
	void AddHandler(EnumType _Type, std::function<void(std::shared_ptr<GameServerPacket>)> _CallBack)
	{
		AddHandler(static_cast<int>(_Type), _CallBack);
	}

	void AddHandler(int _Type, std::function<void(std::shared_ptr<GameServerPacket>)> _CallBack)
	{
		PacketProcessMap[_Type] = _CallBack;
	}

	void ProcessPacket(std::shared_ptr<GameServerPacket> _Packet)
	{
		if (PacketProcessMap.end() == PacketProcessMap.find(_Packet->GetPacketID()))
		{
			MsgBoxAssert("처리 방식을 결정하지 않은 패킷입니다");
		}

		PacketProcessMap[_Packet->GetPacketID()](_Packet);
	}

private:
	std::map<int, std::function<void(std::shared_ptr<GameServerPacket>)>> PacketProcessMap;
};


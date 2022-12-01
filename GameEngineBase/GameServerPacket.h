#pragma once
#include "GameServerSerializer.h"
#include "GameEngineDebug.h"

#define	GameServerPacketError -1

// MonsterMovePacket : public GameServerPacket
// PlayerReady : public GameServerPacket

// 설명 :
class GameServerPacket : public std::enable_shared_from_this<GameServerPacket>
{
public:

	// delete Function
	GameServerPacket(const GameServerPacket& _Other) = delete;
	GameServerPacket(GameServerPacket&& _Other) noexcept = delete;
	GameServerPacket& operator=(const GameServerPacket& _Other) = delete;
	GameServerPacket& operator=(GameServerPacket&& _Other) noexcept = delete;


	template<typename ConvertType>
	std::shared_ptr<ConvertType> DynamicConvert()
	{
		return std::dynamic_pointer_cast<ConvertType>(shared_from_this());
	}


	unsigned int GetPacketID()
	{
		return PacketID;
	}

	template<typename EnumType>
	EnumType GetPacketIDToEnum()
	{
		return static_cast<EnumType>(PacketID);
	}

	template<typename EnumType>
	void SetPacketID(EnumType _Enum)
	{
		PacketID = static_cast<int>(_Enum);
	}

	void SerializePacket(GameServerSerializer& _Ser)
	{
		Serialize(_Ser);
		SerializeEnd(_Ser);
	}

	void DeSerializePacket(GameServerSerializer& _Ser)
	{
		DeSerialize(_Ser);
	}


	GameServerPacket() 
		: PacketID(GameServerPacketError)
	{

	}

	GameServerPacket(int _PacketType)
		: PacketID(_PacketType)
	{

	}

	~GameServerPacket() 
	{

	}

protected:

	virtual void Serialize(GameServerSerializer& _Ser)  = 0
	{
		_Ser << PacketID;
		_Ser << Size;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser) = 0
	{
		_Ser >> PacketID;
		_Ser >> Size;
	}



private:
	unsigned int PacketID; // 패킷의 종류
	unsigned int Size; // 패킷의 크기


	void SerializeEnd(GameServerSerializer& _Ser) 
	{
		Size = _Ser.GetOffSet();

		if (Size == 0)
		{
			MsgBoxAssert("0바이트 패킷이 감지되었습니다.");
		}

		unsigned char* Ptr = _Ser.GetDataPtr();

		memcpy_s(&Ptr[4], sizeof(int), &Size, sizeof(int));

		// _Ser.GetDataPtr[]
	}
};


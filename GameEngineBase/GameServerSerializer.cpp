#include "PreCompile.h"
#include "GameServerSerializer.h"

GameServerSerializer::GameServerSerializer()
	: Offset(0)
{
	Data.resize(1024);
}

GameServerSerializer::GameServerSerializer(const char* _Data, unsigned int _Size)
	: Offset(0)
{

	Data.resize(_Size);
	memcpy_s(&Data[0], _Size, _Data, _Size);
}

GameServerSerializer::~GameServerSerializer() 
{
}

void GameServerSerializer::Read(void* _Data, unsigned int _Size)
{
	memcpy_s(_Data, _Size, &Data[Offset], _Size);
	Offset += _Size;
}

void GameServerSerializer::Write(const void* _Data, unsigned int _Size)
{
	if (Offset + _Size >= Data.size())
	{
		Data.resize(Data.capacity() * 2);
	}

	memcpy_s(&Data[Offset], _Size, _Data, _Size);
	Offset += _Size;

}

void GameServerSerializer::operator<<(const int _Value)
{
	Write(&_Value, sizeof(int));
}

void GameServerSerializer::operator<<(const float _Value)
{
	Write(&_Value, sizeof(float));
}

void GameServerSerializer::operator<<(const std::string& _Value)
{
	operator<<(static_cast<int>(_Value.size()));
	Write(reinterpret_cast<const void*>(&_Value[0]), static_cast<unsigned int>(_Value.size()));
}

void GameServerSerializer::operator<<(const unsigned int _Value)
{
	Write(&_Value, sizeof(unsigned int));
}

void GameServerSerializer::operator<<(const uint64_t& _Value)
{
	Write(&_Value, sizeof(uint64_t));
}

void GameServerSerializer::operator<<(const float4& _Value)
{
	Write(&_Value, sizeof(float4));
}




void GameServerSerializer::operator>>(std::string& _Value)
{
	int Size;
	operator>>(Size);
	_Value.resize(Size);
	Read(&_Value[0], Size);
}

void GameServerSerializer::operator>>(int& _Value)
{
	Read(&_Value, sizeof(int));
}

void GameServerSerializer::operator>>(unsigned int& _Value)
{
	Read(&_Value, sizeof(unsigned int));
}

void GameServerSerializer::operator>>(float& _Value)
{
	Read(&_Value, sizeof(float));
}

void GameServerSerializer::operator>>(float4& _Value)
{
	Read(&_Value, sizeof(float4));
}

void GameServerSerializer::operator>>(uint64_t& _Value)
{
	Read(&_Value, sizeof(uint64_t));
}
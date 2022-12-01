#pragma once
#include "GameEngineMath.h"

// 일반적으로 클래스를 만들게 되면 가상함수니 포인터니 이런애들이 너무 많아서
// 저장한다는것이 의미가 없다.
// 의미있는 데이터만 직렬화 작업을 거쳐서 순수하게 바이트 덩어리로 만들어주는 애입니다.

// 설명 :
class GameServerSerializer
{
public:
	// constrcuter destructer
	GameServerSerializer();
	GameServerSerializer(const char* _Data, unsigned int _Size);
	~GameServerSerializer();

	//// delete Function
	//GameServerSerializer(const GameServerSerializer& _Other) = delete;
	//GameServerSerializer(GameServerSerializer&& _Other) noexcept = delete;
	//GameServerSerializer& operator=(const GameServerSerializer& _Other) = delete;
	//GameServerSerializer& operator=(GameServerSerializer&& _Other) noexcept = delete;

	unsigned int GetOffSet()
	{
		return Offset;
	}

	void OffsetReset()
	{
		Offset = 0;
	}

	void Reset()
	{
		Offset = 0;
		Data.clear();
		Data.resize(1024);
	}

	const std::vector<unsigned char>& GetData() {
		return Data;
	}

	unsigned char* GetDataPtr() {
		return &Data[0];
	}

	template<typename Type>
	Type GetDataPtrConvert() {
		return reinterpret_cast<Type>(& Data[0]);
	}

	void Write(const void* Data, unsigned int _Size);

	void Read(void* Data, unsigned int _Size);

	void operator<<(const std::string& _Value);
	void operator<<(const int _Value);
	void operator<<(const unsigned int _Value);
	void operator<<(const uint64_t& _Value);
	void operator<<(const float _Value);
	void operator<<(const float4& _Value);

	template<typename T>
	void WriteEnum(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void WriteUserData(const T _Value)
	{
		Write(reinterpret_cast<const void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}


	void operator>>(std::string& _Value);
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
	void operator>>(uint64_t& _Value);
	void operator>>(float& _Value);
	void operator>>(float4& _Value);

	template<typename T>
	void ReadEnum(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

	template<typename T>
	void ReadUserData(T& _Value)
	{
		Read(reinterpret_cast<void*>(&_Value), static_cast<unsigned int>(sizeof(T)));
	}

protected:

private:
	unsigned int Offset;
	std::vector<unsigned char> Data;

};


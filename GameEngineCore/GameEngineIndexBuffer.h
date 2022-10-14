#pragma once
#include "GameEngineRes.h"
#include <GameEngineBase/GameEngineMath.h>
#include <vector>
#include <string>
#include <map>
#include <list>

// Ό³Έν :
class GameEngineIndexBuffer : public GameEngineRes<GameEngineIndexBuffer>
{
	friend GameEngineRes<GameEngineIndexBuffer>;

public:
	template<typename IndexType>
	static GameEngineIndexBuffer* Create(const std::string& _Name, const std::vector<IndexType>& _Vertex)
	{
		return Create(_Name, &_Vertex[0] , sizeof(IndexType), static_cast<unsigned int>(_Vertex.size()));
	}


	static GameEngineIndexBuffer* Create(const std::string& _Name, const void* _Data, UINT _IndexSize, UINT _IndexCount);

private:
	// constrcuter destructer
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	// delete Function
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _Other) noexcept = delete;

public:
	void Setting();

	inline UINT GetIndexCount() 
	{
		return IndexCount;
	}

protected:
	void BufferCreate(const void* _Data, UINT _IndexSize, UINT _IndexCount);


private:
	// nullptr
	D3D11_BUFFER_DESC BufferDesc;

	D3D11_SUBRESOURCE_DATA Data;

	ID3D11Buffer* Buffer;

	UINT IndexSize;

	UINT IndexCount;

	UINT Offset;
};


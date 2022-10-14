#pragma once
#include "GameEngineRes.h"
#include <vector>
#include <string>
#include <map>
#include <list>
#include "GameEngineVertexs.h"

// Ό³Έν :
class GameEngineInstancingBuffer : public GameEngineRes<GameEngineInstancingBuffer>
{
public:
	// constrcuter destructer
	GameEngineInstancingBuffer();
	~GameEngineInstancingBuffer();

	// delete Function
	GameEngineInstancingBuffer(const GameEngineInstancingBuffer& _Other) = delete;
	GameEngineInstancingBuffer(GameEngineInstancingBuffer&& _Other) noexcept = delete;
	GameEngineInstancingBuffer& operator=(const GameEngineInstancingBuffer& _Other) = delete;
	GameEngineInstancingBuffer& operator=(GameEngineInstancingBuffer&& _Other) noexcept = delete;

	static GameEngineInstancingBuffer* Create(unsigned int _Count, unsigned int _Size);

	ID3D11Buffer* GetBuffer()
	{
		return Buffer;
	}

	unsigned int GetBufferCount()
	{
		return BufferCount;
	}

	unsigned int GetDataSize()
	{
		return Size;
	}

	void ChangeData(const void* _Data, size_t _Size) const;

	void BufferCreate(unsigned int _Count, unsigned int _Size);

protected:

private:
	D3D11_BUFFER_DESC BufferDesc;
	ID3D11Buffer* Buffer;
	unsigned int BufferCount;
	unsigned int Size;

	void BufferRelease();

};


#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"
#include <vector>
#include <string>
#include <map>
#include <list>
#include "GameEngineVertexs.h"

// 설명 :
class GameEngineVertexBuffer : public GameEngineRes<GameEngineVertexBuffer>
{
public:
	friend GameEngineRes<GameEngineVertexBuffer>;
	
public:
	template<typename VertexType>
	static GameEngineVertexBuffer* Create(const std::string& _Name, const std::vector<VertexType>& _Vertex)
	{
		return Create(_Name, &_Vertex[0], static_cast<UINT>(sizeof(VertexType)), static_cast<UINT>(_Vertex.size()), VertexType::LayOut);
	}


	static GameEngineVertexBuffer* Create(const std::string& _Name, const void* _Data, UINT _VertexSize, UINT _VertexCount, const GameEngineLayOutDesc& _LayOut);

public:
	const GameEngineLayOutDesc& GetLayOutDesc()
	{
		if (nullptr == LayOutDesc)
		{
			MsgBoxAssert("버텍스 레이아웃 정보가 존재하지 않는 매쉬입니다");
		}

		return *LayOutDesc;
	}

	void Setting();

	inline ID3D11Buffer* GetBuffer() 
	{
		return Buffer;
	}

	inline UINT GetVertexSize()
	{
		return VertexSize;
	}


protected:
	void BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount);


private:
	// nullptr
	D3D11_BUFFER_DESC BufferDesc;

	ID3D11Buffer* Buffer;

	UINT VertexCount;

	UINT VertexSize;

	UINT OffSet;

	const GameEngineLayOutDesc* LayOutDesc;

	// constrcuter destructer
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

	// delete Function
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;


};


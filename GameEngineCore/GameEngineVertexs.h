#pragma once
#include <GameEngineBase/GameEngineMath.h>

class GameEngineLayOutDesc 
{
	// 일반적인 맴버변수를 가지면 안됩니다.

	friend class GameEngineInputLayOut;

public:
	unsigned int InstancingSize;
	unsigned int LayOutOffset;
	std::map<const char*, int> SemanticIndexData;
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutDesc;
	void AddInputLayOut(
		const char* _SemanticName,
		// unsigned int _AlignedByteOffset,
		DXGI_FORMAT _Format,
		unsigned int _InputSlot = 0,
		D3D11_INPUT_CLASSIFICATION _inputClass = D3D11_INPUT_PER_VERTEX_DATA,
		unsigned int _InstanceDataStepRate = 0,
		unsigned int _Index = -1
	);

public:
	void OffsetReset() 
	{
		LayOutOffset = 0;
	}

public:
	GameEngineLayOutDesc()
		: LayOutOffset(0)
	{

	}
};

struct GameEngineVertex 
{
public:
	static GameEngineLayOutDesc LayOut;

public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
};


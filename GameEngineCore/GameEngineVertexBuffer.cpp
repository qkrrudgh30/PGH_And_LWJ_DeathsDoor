#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexBuffer::GameEngineVertexBuffer() 
	: Buffer(nullptr)
	, BufferDesc{}
	, OffSet(0)
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() 
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
	}
}


GameEngineVertexBuffer* GameEngineVertexBuffer::Create(
	const std::string& _Name, 
	const void* _Data, UINT _VertexSize,
	UINT _VertexCount,
	const GameEngineLayOutDesc& _LayOut
)
{
	GameEngineVertexBuffer* NewRes = CreateResName(_Name);
	NewRes->LayOutDesc = &_LayOut;
	NewRes->BufferCreate(_Data, _VertexSize, _VertexCount);
	return NewRes;
}

void GameEngineVertexBuffer::BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	//UINT ByteWidth; // 할당하려는 버퍼의 크기
	//D3D11_USAGE Usage; // 할당하려는 버퍼의 액세스 권한과 용도
	//UINT BindFlags; // 버퍼의 랜더링적 용도
	//UINT CPUAccessFlags; // CPU에서 액세스 할수 있는지
	//UINT MiscFlags; // 
	//UINT StructureByteStride;

	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.ByteWidth = _VertexSize * _VertexCount;

	// VertexCount = _Size / 

	BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	// BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	BufferDesc.CPUAccessFlags = 0;

	// 추가 옵션인데 쓰지 않을겁니다.
	BufferDesc.MiscFlags = 0;
	// 버텍스 버퍼에서는 세팅해줄 필요도 없다.
	BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}

// 이 세팅은 1개의 매쉬를 그리는 세팅 세팅
void GameEngineVertexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("버텍스 버퍼에 문제가 있습니다.");
	}

	// 0, 1,

	// [버텍스버퍼] 0번부터 쓰겠다. 32바이트
	// [버텍스버퍼]                10
	// [버텍스버퍼]                
	// [버텍스버퍼]
	// [버텍스버퍼]
	// [버텍스버퍼]

	//             
	// [버텍스버퍼] [32][32][32][32]
	//              128, 

	// 나눠서 그릴수 있는 기능을 지원하지만
	GameEngineDevice::GetContext()->IASetVertexBuffers(
		0, // 버텍스 버퍼를 이중포인터로 세팅해줬을대의 사용시작 인덱스
		1, &Buffer, &VertexSize, &OffSet);
}
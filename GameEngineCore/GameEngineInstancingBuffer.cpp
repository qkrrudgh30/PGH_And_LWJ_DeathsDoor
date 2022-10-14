#include "PreCompile.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineDevice.h"

GameEngineInstancingBuffer::GameEngineInstancingBuffer() 
{
}

GameEngineInstancingBuffer::~GameEngineInstancingBuffer() 
{
	BufferRelease();
}

void GameEngineInstancingBuffer::BufferRelease()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}


GameEngineInstancingBuffer* GameEngineInstancingBuffer::Create(unsigned int _Count, unsigned int _Size)
{
	GameEngineInstancingBuffer* Buffer = CreateResUnName();

	Buffer->BufferCreate(_Count, _Size);

	return Buffer;
}

void GameEngineInstancingBuffer::BufferCreate(unsigned int _Count, unsigned int _Size)
{
	BufferRelease();

	BufferCount = _Count;
	Size = _Size;
	BufferDesc = {};
	BufferDesc.ByteWidth = _Count * Size;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, nullptr, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}


void GameEngineInstancingBuffer::ChangeData(const void* _Data, size_t _Size) const
{
	if (_Data == nullptr)
	{
		MsgBoxAssertString(GetNameCopy() + "  데이터를 세팅해주지 않았습니다.");
	}

	if (BufferDesc.ByteWidth != _Size)
	{
		MsgBoxAssertString(GetNameCopy() + "  상수버퍼의 바이트 크기가 서로 맞지 않습니다.");
	}

	D3D11_MAPPED_SUBRESOURCE SettingResources = {};
	memset(&SettingResources, 0, sizeof(SettingResources));

	// 어떤 그래픽 리소스를 이제부터 아무도 건들지 못하게 해.
	// 그래픽카드를 느리게 만듭니다.
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("그래픽카드 버퍼에 접근하지 못했습니다..");
	}

	memcpy_s(SettingResources.pData, BufferDesc.ByteWidth, _Data, BufferDesc.ByteWidth);


	// 무조건 다시 닫아줘야 합니다.
	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
}
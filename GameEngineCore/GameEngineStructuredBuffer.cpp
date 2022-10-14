#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"

// 데이터 1개의 사이즈.
std::map<std::string, std::map<int, GameEngineStructuredBuffer*>> GameEngineStructuredBuffer::StructuredBufferRes;


GameEngineStructuredBuffer::GameEngineStructuredBuffer() 
	: Buffer(nullptr)
	,BufferDesc()
	,ShaderDesc()
	,SettingResources()
	, ShaderResourceView(nullptr)
	, DataSize(0)
	, DataCount(0)
	, IsInit(false)
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer() 
{
	Release();
}

void GameEngineStructuredBuffer::Release() 
{
	if (nullptr != ShaderResourceView)
	{
		ShaderResourceView->Release();
		ShaderResourceView = nullptr;
	}

	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}


void GameEngineStructuredBuffer::CreateResize(const D3D11_SHADER_BUFFER_DESC& _Desc, int Count, void* _StartData)
{
	if (false == IsInit)
	{
		ShaderDesc = _Desc;
		IsInit = true;
	}

	CreateResize(ShaderDesc.Size, Count, _StartData);
}

void GameEngineStructuredBuffer::CreateResize(int Count, void* _StartData /*= nullptr*/)
{
	CreateResize(DataSize, Count, _StartData);
}

void GameEngineStructuredBuffer::CreateResize(int _DataSize, int Count, void* _StartData/* = nullptr*/)
{
	if (0 == _DataSize)
	{
		MsgBoxAssert("데이터 사이즈가 0인 구조화 버퍼를 만들수는 없습니다.");
	}

	DataSize = _DataSize;

	if (0 == Count)
	{
		return;
	}

	if (DataCount >= Count)
	{
		return;
	}

	Release();
	DataCount = Count;

	BufferDesc.ByteWidth = ShaderDesc.Size * DataCount; // GPU 에 생성할 구조화 버퍼 메모리 크기(최소단위 ??)
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	BufferDesc.StructureByteStride = ShaderDesc.Size; // 1개 크기도 넣어줘야 한다.

	D3D11_SUBRESOURCE_DATA* StartDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA StartData = {0};
	if (nullptr != _StartData)
	{
		StartData.SysMemPitch = 0;
		StartData.SysMemSlicePitch = 0;
		StartData.pSysMem = _StartData;
		StartDataPtr = &StartData;
	}



	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, StartDataPtr, &Buffer))
	{
		MsgBoxAssert("스트럭처드 버퍼 생성에 실패했습니다.");
	}

	// Shader Resource View
	// 쉐이더 리소스를 만드는데 버퍼기반 
	// D3D11_SRV_DIMENSION_BUFFEREX 버퍼기반 쉐이더 리소스 뷰라는것을 알려주기 위한 용도
	D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
	tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	tSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	tSRVDesc.BufferEx.FirstElement = 0;
	tSRVDesc.BufferEx.Flags = 0;
	tSRVDesc.BufferEx.NumElements = DataCount; // 10개로 우리어진 m_pSRV를 넣어달라.

	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(Buffer, &tSRVDesc, &ShaderResourceView))
	{
		MsgBoxAssert("FAIL (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(GetBuffer(), &tSRVDesc, &m_pSRV))");
	}
}


void GameEngineStructuredBuffer::ChangeData(const void* _Data, size_t _Size)
{
	// 512 라이트 데이터를 세팅해줄수 있는 버퍼를 만들었다고 하더라도
// 진짜 512개의 라이트를 세팅하는것은 아닐수가 있으므로
// 기존에 만든 세팅들이 사이드 이펙트가 생기지는 않겠지만
// 위험하니까 고려는 해둬야 할겁니다.

// 여기에서 실제 데이터를 세팅해주게 되는데.
#ifdef _DEBUG
	//if (m_BufferInfo.ByteWidth != _Size)
	//{
	//	GameEngineDebug::AssertMsg("if (m_BufferInfo.ByteWidth != _Size)");
	//}
	SettingResources.pData = nullptr;
#endif

	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

#ifdef _DEBUG
	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("if (nullptr == m_Res.pData)");
	}
#endif 

	const float4x4* Ptr = reinterpret_cast<const float4x4*>(_Data);

	float4x4 Test = *Ptr;

	memcpy_s(SettingResources.pData, BufferDesc.ByteWidth, _Data, _Size);

	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
}


void GameEngineStructuredBuffer::VSReset(int _BindPoint)
{
	ID3D11ShaderResourceView* Nullptr = nullptr;

	GameEngineDevice::GetContext()->VSSetShaderResources(_BindPoint, 1, &Nullptr);
}
void GameEngineStructuredBuffer::PSReset(int _BindPoint)
{
	ID3D11ShaderResourceView* Nullptr = nullptr;

	GameEngineDevice::GetContext()->PSSetShaderResources(_BindPoint, 1, &Nullptr);
}

void GameEngineStructuredBuffer::VSSetting(int _BindPoint)
{
	if (nullptr == ShaderResourceView)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}

	GameEngineDevice::GetContext()->VSSetShaderResources(_BindPoint, 1, &ShaderResourceView);
}

void GameEngineStructuredBuffer::PSSetting(int _BindPoint)
{
	if (nullptr == ShaderResourceView)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}

	GameEngineDevice::GetContext()->PSSetShaderResources(_BindPoint, 1, &ShaderResourceView);
}

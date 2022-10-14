#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineBlend.h"


GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() 
	: InputLayOut(nullptr)
	, VertexBuffer(nullptr)
	, VertexShader(nullptr)
	, IndexBuffer(nullptr)
	, Rasterizer(nullptr)
	, PixelShader(nullptr)
	, DepthStencil(nullptr)
	, Blend(nullptr)
	, Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	VertexBuffer = GameEngineVertexBuffer::Find("rect");
	IndexBuffer = GameEngineIndexBuffer::Find("rect");
	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
	Blend = GameEngineBlend::Find("AlphaBlend");
	DepthStencil = GameEngineDepthStencil::Find("EngineBaseDepth");
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() 
{
}

//
//void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
//{
//	InputLayOut = GameEngineInputLayOut::Find(_Name);
//
//	if (nullptr == InputLayOut)
//	{
//		MsgBoxAssert("존재하지 않는 인풋레이아웃을 세팅하려고 했습니다.");
//		return;
//	}
//}

void GameEngineRenderingPipeLine::AllShaderReset()
{
	GameEngineDevice::GetContext()->VSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->DSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->HSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->PSSetShader(nullptr, nullptr, 0);
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Create()
{
	return CreateResUnName();
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Create(const std::string& _Name)
{
	return CreateResName(_Name);
}

void GameEngineRenderingPipeLine::SetInputAssembler1VertexBuffer(const std::string& _Name) 
{
	VertexBuffer = GameEngineVertexBuffer::Find(_Name);

	if (nullptr == VertexBuffer)
	{
		MsgBoxAssert("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}


	if (nullptr == InputLayOut && nullptr != VertexShader)
	{
		InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader = GameEngineVertexShader::Find(_Name);

	if (nullptr == VertexShader)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}

	// 인풋레이아웃이 만들어지지 않았는데.
	if (nullptr == InputLayOut && nullptr != VertexBuffer)
	{
		InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Shader)
{
	VertexShader = _Shader;

	// 인풋레이아웃이 만들어지지 않았는데.
	// 인스턴싱때 문제될수 있다.
	if (nullptr == InputLayOut && nullptr != VertexBuffer)
	{
		InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}

}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBuffer(const std::string& _Name) 
{
	IndexBuffer = GameEngineIndexBuffer::Find(_Name);

	if (nullptr == IndexBuffer)
	{
		MsgBoxAssert("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer = GameEngineRasterizer::Find(_Name);

	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("존재하지 않는 레스터라이저 세팅를 세팅하려고 했습니다.");
		return;
	}

}


void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader = GameEnginePixelShader::Find(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고 했습니다.");
		return;
	}

}



void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil = GameEngineDepthStencil::Find(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("존재하지 않는 깊이스텐실를 세팅하려고 했습니다.");
		return;
	}

}


void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend = GameEngineBlend::Find(_Name);

	if (nullptr == Blend)
	{
		MsgBoxAssert("존재하지 않는 블랜더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::Rendering()
{
	InputAssembler1VertexBufferSetting();

	VertexShaderSetting();

	InputAssembler2IndexBufferSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();

	Draw();

}

void GameEngineRenderingPipeLine::RenderingInstancing(int _RenderingCount, class GameEngineInstancingBuffer* _Buffer)
{
	InputAssembler1InstancingVertexBufferSetting(_Buffer);

	VertexShaderSetting();

	InputAssembler2IndexBufferSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();

	InstancingDraw(_RenderingCount);

}

void GameEngineRenderingPipeLine::InstancingDataCollect()
{
	// InstancingDraw();
}

// 실직적으로 세팅의 순서는 그다지 중요하지 않다.

void GameEngineRenderingPipeLine::InputAssembler1VertexBufferSetting()
{
	InputLayOut->Setting();

	VertexBuffer->Setting();
}

void GameEngineRenderingPipeLine::InputAssembler1InstancingVertexBufferSetting(GameEngineInstancingBuffer* _Buffer)
{
	// 그래픽리소스에 Setting이라는 함수가 존재한다면
// 그건 이제부터 그 설정으로 랜더링 파이프라인이 돌아가게 된다는 뜻이 됩니다.
	InputLayOut->Setting();
	// 버텍스 버퍼는 세팅할게 없다.
	// VertexBuffer->Setting();

	// 2번째는 인스턴싱 버퍼의 

	// GameEngineVertexBuffer* InstancingBuffer;

	ID3D11Buffer* ArrBuffer[2] = { VertexBuffer->GetBuffer(), _Buffer->GetBuffer() };
	UINT ArrVertexSize[2] = { VertexBuffer->GetVertexSize(), _Buffer->GetDataSize()};
	UINT ArrOffset[2] = { 0, 0 };

	GameEngineDevice::GetContext()->IASetVertexBuffers(
		0, // 버텍스 버퍼를 이중포인터로 세팅해줬을대의 사용시작 인덱스
		2, ArrBuffer, ArrVertexSize, ArrOffset);
}

void GameEngineRenderingPipeLine::VertexShaderSetting() 
{
	VertexShader->Setting();
	// 위치 
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void GameEngineRenderingPipeLine::InputAssembler2IndexBufferSetting() 
{
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology);

	IndexBuffer->Setting();
}

void GameEngineRenderingPipeLine::RasterizerSetting() 
{
	Rasterizer->Setting();
}

void GameEngineRenderingPipeLine::PixelShaderSetting() 
{
	PixelShader->Setting();
}

void GameEngineRenderingPipeLine::OutputMergerBlendSetting() 
{
	Blend->Setting();
}

void GameEngineRenderingPipeLine::OutputMergerDepthStencilSetting() 
{
	DepthStencil->Setting();
}


void GameEngineRenderingPipeLine::Draw()
{
	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
}

void GameEngineRenderingPipeLine::InstancingDraw(int _RenderingCount)
{
	//[in] IndexCountPerInstance 유형 : UINT
	//각 인스턴스에 대해 인덱스 버퍼에서 읽은 인덱스 수입니다.
	//

	//[in] InstanceCount 유형 : UINT
	//그릴 인스턴스 수입니다.

	//[in] StartIndexLocation
	//유형 : UINT GPU가 인덱스 버퍼에서 읽은 첫 번째 인덱스의 위치입니다.

	//[in] BaseVertexLocation 유형 : 지능
	//정점 버퍼에서 정점을 읽기 전에 각 인덱스에 추가된 값입니다.

	//[in] StartInstanceLocation 유형 : UINT
	//정점 버퍼에서 인스턴스별 데이터를 읽기 전에 각 인덱스에 추가된 값입니다.

	// 그냥 4가 들어간다.
	GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer->GetIndexCount(), _RenderingCount, 0, 0, 0);
}

void GameEngineRenderingPipeLine::Copy(GameEngineRenderingPipeLine* _Original)
{
	InputLayOut			= _Original->InputLayOut;
	VertexBuffer			= _Original->VertexBuffer;
	VertexShader			= _Original->VertexShader;
	IndexBuffer			= _Original->IndexBuffer;
	Topology				= _Original->Topology;
	Rasterizer				= _Original->Rasterizer;
	PixelShader			= _Original->PixelShader;
	DepthStencil			= _Original->DepthStencil;
	Blend					= _Original->Blend;
}
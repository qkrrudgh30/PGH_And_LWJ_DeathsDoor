#include "PreCompile.h"
#include "GameEngineMesh.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

GameEngineMesh::GameEngineMesh() 
	: VertexBuffer(nullptr)
	, IndexBuffer(nullptr)
{
	SetInputAssembler1VertexBuffer("rect");
	SetInputAssembler2IndexBuffer("rect");
}

GameEngineMesh::~GameEngineMesh() 
{
}

const GameEngineLayOutDesc& GameEngineMesh::GetLayOutDesc()
{
	if (nullptr == VertexBuffer)
	{
		MsgBoxAssert("버텍스 버퍼가 세팅이 되어있지 않아서 레이아웃 정보를 빼낼수 없습니다.");
	}

	return VertexBuffer->GetLayOutDesc();
}

std::shared_ptr < GameEngineMesh> GameEngineMesh::Create(const std::string& _Name)
{
	return Create(_Name, _Name, _Name);
}

std::shared_ptr < GameEngineMesh> GameEngineMesh::Create(const std::string& _Name, const std::string& _Vtx, const std::string& _Idx)
{
	std::shared_ptr < GameEngineMesh> NewRes = CreateResName(_Name);
	NewRes->SetInputAssembler1VertexBuffer(_Vtx);
	NewRes->SetInputAssembler2IndexBuffer(_Idx);
	return NewRes;
}

std::shared_ptr < GameEngineMesh> GameEngineMesh::Create(std::shared_ptr < GameEngineVertexBuffer> _Vtx, std::shared_ptr < GameEngineIndexBuffer> _Idx)
{
	std::shared_ptr < GameEngineMesh> NewRes = CreateResUnName();
	NewRes->SetInputAssembler1VertexBuffer(_Vtx);
	NewRes->SetInputAssembler2IndexBuffer(_Idx);
	return NewRes;
}

void GameEngineMesh::InputAssembler1VertexBufferSetting()
{
	VertexBuffer->Setting();
}


void GameEngineMesh::InputAssembler2IndexBufferSetting()
{
	IndexBuffer->Setting();
}

void GameEngineMesh::Setting()
{
	InputAssembler1VertexBufferSetting();
	InputAssembler2IndexBufferSetting();
}

void GameEngineMesh::SetInputAssembler1VertexBuffer(const std::string& _Name)
{
	VertexBuffer = GameEngineVertexBuffer::Find(_Name);

	if (nullptr == VertexBuffer)
	{
		MsgBoxAssert("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}


	//if (nullptr == InputLayOut && nullptr != VertexShader)
	//{
	//	InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	//}
}


void GameEngineMesh::SetInputAssembler2IndexBuffer(const std::string& _Name)
{
	IndexBuffer = GameEngineIndexBuffer::Find(_Name);

	if (nullptr == IndexBuffer)
	{
		MsgBoxAssert("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMesh::SetInputAssembler1VertexBuffer(std::shared_ptr < GameEngineVertexBuffer> _Res)
{
	if (nullptr == _Res)
	{
		MsgBoxAssert("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
		return;
	}

	VertexBuffer = _Res;
}
void GameEngineMesh::SetInputAssembler2IndexBuffer(std::shared_ptr < GameEngineIndexBuffer> _Res)
{
	if (nullptr == _Res)
	{
		MsgBoxAssert("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
		return;
	}

	IndexBuffer = _Res;
}


void GameEngineMesh::Render()
{
	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
}

void GameEngineMesh::RenderInstancing(size_t _InstancingCount)
{
	GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer->GetIndexCount(), static_cast<unsigned int>(_InstancingCount), 0, 0, 0);
}

void GameEngineMesh::SettingInstancing(std::shared_ptr<GameEngineInstancingBuffer> _Buffer)
{
	// InputLayOut->Setting();
	// 버텍스 버퍼는 세팅할게 없다.
	// VertexBuffer->Setting();

	// 2번째는 인스턴싱 버퍼의 

	ID3D11Buffer* ArrBuffer[2] = { VertexBuffer->GetBuffer(), _Buffer->GetBuffer() };
	UINT ArrVertexSize[2] = { VertexBuffer->GetVertexSize(), _Buffer->GetDataSize()};
	UINT ArrOffset[2] = { 0, 0 };

	GameEngineDevice::GetContext()->IASetVertexBuffers(
		0, // 버텍스 버퍼를 이중포인터로 세팅해줬을대의 사용시작 인덱스
		2, ArrBuffer, ArrVertexSize, ArrOffset);

	InputAssembler2IndexBufferSetting();

}
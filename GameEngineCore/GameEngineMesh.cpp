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
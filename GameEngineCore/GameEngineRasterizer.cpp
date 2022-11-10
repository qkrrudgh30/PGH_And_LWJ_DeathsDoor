#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() 
	: Desc{}
{
}

GameEngineRasterizer::~GameEngineRasterizer() 
{
	if (nullptr != State)
	{
		State->Release();
	}
}


void GameEngineRasterizer::Setting() 
{

	if (nullptr == State)
	{
		MsgBoxAssert("레스터라이저가 nullptr 입니다. 세팅할수 없습니다.");
		return;
	}

	GameEngineDevice::GetContext()->RSSetState(State);

}

std::shared_ptr < GameEngineRasterizer> GameEngineRasterizer::Create(
	const std::string& _Name, const D3D11_RASTERIZER_DESC& _Desc
)
{
	std::shared_ptr < GameEngineRasterizer> NewRes = CreateResName(_Name);
	NewRes->Create(_Desc);
	return NewRes;
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Desc)
{
	Desc = _Desc;

	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &State))
	{
		MsgBoxAssert("레스터라이저 생성에 실패했습니다.");
	}
}

#include "PreCompile.h"
#include "GameEngineSampler.h"

GameEngineSampler* GameEngineSampler::Create(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info)
{
	GameEngineSampler* NewRes = CreateResName(_Name);
	NewRes->Create(_Info);
	return NewRes;
}

GameEngineSampler::GameEngineSampler() 
	: State(nullptr)
	, Desc{}
{
}

GameEngineSampler::~GameEngineSampler() 
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}



void GameEngineSampler::Create(const D3D11_SAMPLER_DESC& _Info)
{
	Desc = _Info;

	if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(&_Info, &State))
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}
}


void GameEngineSampler::VSSetting(int _BindPoint)
{
	if (nullptr == State)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}

	GameEngineDevice::GetContext()->VSSetSamplers(_BindPoint, 1, &State);
}

void GameEngineSampler::PSSetting(int _BindPoint)
{
	if (nullptr == State)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}

	GameEngineDevice::GetContext()->PSSetSamplers(_BindPoint, 1, &State);
}
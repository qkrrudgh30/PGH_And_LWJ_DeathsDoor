#pragma once
#include "GameEngineRes.h"

// 뎁스스텐실 설정이랑
// 뎁스스텐실 텍스처가



// 설명 : 최종 픽셀쉐이더의 출력결과를 랜더타겟에 출력할때 누가 앞이고 누가 뒤인지에 대한 처리
class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
//public:
//	static GameEngineDepthStencil* Create(const float4 _Scale);

public:
	static GameEngineDepthStencil* Create(
		const std::string& _Name, const D3D11_DEPTH_STENCIL_DESC& _Desc);

public:
	// constrcuter destructer
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

	// delete Function
	GameEngineDepthStencil(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _Other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil& operator=(GameEngineDepthStencil&& _Other) noexcept = delete;

	void Setting();

protected:

private:
	D3D11_DEPTH_STENCIL_DESC Desc;
	ID3D11DepthStencilState* State;

	void Create(const D3D11_DEPTH_STENCIL_DESC& _Desc);
};


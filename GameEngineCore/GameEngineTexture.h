#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

#include "../GameEngineCore/ThirdParty/inc/DirectXTex.h"

#pragma comment(lib, "DirectXTex.lib")


struct PixelColor 
{
	union 
	{
		struct 
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned int Color;
	};

public:
	PixelColor() 
		: Color(0)
	{

	}
};

// 설명 :
class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{


public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static GameEngineTexture* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineTexture* Load(const std::string& _Path, const std::string& _Name);

	// static
	static GameEngineTexture* Create(const std::string& _Name, ID3D11Texture2D* _Texture);
	static GameEngineTexture* Create(ID3D11Texture2D* _Texture);

	static GameEngineTexture* Create(const D3D11_TEXTURE2D_DESC& _Desc);

	// static void Cut("Boss_Left.bmp", 5, 7);
	static void Cut(const std::string& _Name, UINT _X, UINT _Y);

	// Member
	ID3D11RenderTargetView* CreateRenderTargetView();
	ID3D11ShaderResourceView* CreateShaderResourceView();
	ID3D11DepthStencilView* CreateDepthStencilView();

	void VSSetting(int _BindPoint);
	void PSSetting(int _BindPoint);

	void VSReset(int _BindPoint);
	void PSReset(int _BindPoint);

	size_t GetCutCount() 
	{
		return CutData.size();
	}

	float4 GetFrameData(UINT _Index)
	{
		if (true == CutData.empty())
		{
			MsgBoxAssertString(GetNameCopy() + " 자르지 않은 텍스처를 사용하려고 했습니다.");
		}

		if (CutData.size() <= _Index)
		{
			MsgBoxAssertString(GetNameCopy() + " 프레임 범위를 초과했습니다.");
		}

		return CutData[_Index];
	}
	
	void TextureLoad(const std::string& _Path);

	float4 GetScale()
	{								//(Metadata.width),(Metadata.height)이거쓰면 0,0되서 텍스쳐 생성에 실패함 뜸
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height) };
	}

	float4 GetCutPos(int _Index)
	{
		return { CutData[_Index].PosX * static_cast<float>(Desc.Width), CutData[_Index].PosY * static_cast<float>(Desc.Height) };
	}

	float4 GetCutScale(int _Index)
	{					
		return { CutData[_Index].SizeX * static_cast<float>(Desc.Width), CutData[_Index].SizeY * static_cast<float>(Desc.Height)};
	}

	void TextureCreate(const D3D11_TEXTURE2D_DESC& _Desc);

	PixelColor GetPixelToPixelColor(int _x, int _y);

	float4 GetPixelToFloat4(int _x, int _y);

	void Cut(UINT _StartX, UINT _StartY, UINT _SizeX, UINT _SizeY);


protected:

private:
	ID3D11Texture2D* Texture2D;
	ID3D11RenderTargetView* RenderTargetView;  // 랜더타겟으로 사용할경우의 인터페이스
	ID3D11ShaderResourceView* ShaderResourceView; // 쉐이더에 세팅해주기 인터페이스
	ID3D11DepthStencilView* DepthStencilView; // 깊이 버퍼로 사용할 경우의 인터페이스

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage Image;

	D3D11_TEXTURE2D_DESC Desc;
	// 이녀석은 텍스처를 통해서 
	// ID3D11RenderTargetView* Render;

	std::vector<float4> CutData;

	void Cut(UINT _X, UINT _Y);
};


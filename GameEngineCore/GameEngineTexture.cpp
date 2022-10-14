#include "PreCompile.h"
#include "GameEngineTexture.h"

GameEngineTexture::GameEngineTexture()
	: Texture2D(nullptr)
	, RenderTargetView(nullptr)
	, ShaderResourceView(nullptr)
	, Metadata()
{
}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != DepthStencilView)
	{
		DepthStencilView->Release();
	}

	if (nullptr != ShaderResourceView)
	{
		ShaderResourceView->Release();
	}

	if (nullptr != RenderTargetView)
	{
		RenderTargetView->Release();
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}

ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RenderTargetView)
	{
		return RenderTargetView;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RenderTargetView))
	{
		MsgBoxAssert("랜더타겟 생성에 실패했습니다.");
	}

	return RenderTargetView;
}

ID3D11ShaderResourceView* GameEngineTexture::CreateShaderResourceView()
{
	if (nullptr != ShaderResourceView)
	{
		return ShaderResourceView;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(Texture2D, nullptr, &ShaderResourceView))
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패했습니다.");
	}

	return ShaderResourceView;
}

ID3D11DepthStencilView* GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr != DepthStencilView)
	{
		return DepthStencilView;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DepthStencilView))
	{
		MsgBoxAssert("깊이 버퍼 세팅 실패했습니다.");
	}

	return DepthStencilView;
}

GameEngineTexture* GameEngineTexture::Create(ID3D11Texture2D* _Texture)
{
	GameEngineTexture* NewRes = CreateResUnName();
	NewRes->Texture2D = _Texture;
	_Texture->GetDesc(&NewRes->Desc);
	return NewRes;
}

GameEngineTexture* GameEngineTexture::Create(const D3D11_TEXTURE2D_DESC& _Desc)
{
	GameEngineTexture* NewRes = CreateResUnName();
	NewRes->TextureCreate(_Desc);
	return NewRes;
}

GameEngineTexture* GameEngineTexture::Create(const std::string& _Name, ID3D11Texture2D* _Texture)
{
	GameEngineTexture* NewRes = CreateResName(_Name);
	NewRes->Texture2D = _Texture;
	return NewRes;
}

GameEngineTexture* GameEngineTexture::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineTexture* NewRes = CreateResName(_Name);
	NewRes->TextureLoad(_Path);
	return NewRes;
}

void GameEngineTexture::TextureLoad(const std::string& _Path)
{
	std::string Ex = GameEngineString::ToUpperReturn(GameEnginePath::GetExtension(_Path));

	std::wstring LoadPath = GameEngineString::AnsiToUnicodeReturn(_Path);

	if (Ex == "TGA")
		// && S_OK != DirectX::LoadFromTGAFile(LoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, Image))
	{
		MsgBoxAssertString(_Path + "아직 처리하지 않은 이미지 포멧입니다.");
	}
	else if (Ex == "DDS")
		// && S_OK != DirectX::LoadFromDDSFile(LoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, Image))
	{
		MsgBoxAssertString(_Path + "아직 처리하지 않은 이미지 포멧입니다.");
	}
	else if (S_OK != DirectX::LoadFromWICFile(LoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, Image))
	{
		MsgBoxAssertString(_Path + "로드에 실패했습니다.");
	}

	// GameEngineDevice::GetDevice()->쉬운텍스처함수

	// 이건 라이브러리에서 지원해주는 함수이고
	if (S_OK != DirectX::CreateShaderResourceView(
		GameEngineDevice::GetDevice(),
		Image.GetImages(),
		Image.GetImageCount(),
		Image.GetMetadata(),
		&ShaderResourceView
	))
	{
		MsgBoxAssertString(_Path + "쉐이더 리소스 생성에 실패했습니다.");
	}

	Desc.Width = static_cast<UINT>(Metadata.width);
	Desc.Height = static_cast<UINT>(Metadata.height);
}

void GameEngineTexture::VSSetting(int _BindPoint)
{
	if (nullptr == ShaderResourceView)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}

	GameEngineDevice::GetContext()->VSSetShaderResources(_BindPoint, 1, &ShaderResourceView);
}

void GameEngineTexture::PSSetting(int _BindPoint)
{
	if (nullptr == ShaderResourceView)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용할 수 없습니다.");
	}

	GameEngineDevice::GetContext()->PSSetShaderResources(_BindPoint, 1, &ShaderResourceView);
}

void GameEngineTexture::VSReset(int _BindPoint)
{
	ID3D11ShaderResourceView* Nullptr = nullptr;

	GameEngineDevice::GetContext()->VSSetShaderResources(_BindPoint, 1, &Nullptr);
}
void GameEngineTexture::PSReset(int _BindPoint)
{
	ID3D11ShaderResourceView* Nullptr = nullptr;

	GameEngineDevice::GetContext()->PSSetShaderResources(_BindPoint, 1, &Nullptr);
}


void GameEngineTexture::Cut(const std::string& _Name, UINT _X, UINT _Y)
{
	GameEngineTexture* Texture = Find(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 자르려고 했습니다.");
		return;
	}

	Texture->Cut(_X, _Y);
}

void GameEngineTexture::Cut(UINT _StartX, UINT _StartY, UINT _SizeX, UINT _SizeY)
{
	float4 FrameData;

	FrameData.PosX = _StartX / GetScale().x;
	FrameData.PosY = _StartY / GetScale().y;
	FrameData.SizeX = _SizeX / GetScale().x;
	FrameData.SizeY = _SizeY / GetScale().y;

	CutData.push_back(FrameData);

}

void GameEngineTexture::Cut(UINT _X, UINT _Y)
{
	float SizeX = 1.0f / _X;
	float SizeY = 1.0f / _Y;

	float4 Start = float4::ZERO;

	for (size_t y = 0; y < _Y; y++)
	{
		for (size_t x = 0; x < _X; x++)
		{

			float4 FrameData;

			FrameData.PosX = Start.x;
			FrameData.PosY = Start.y;
			FrameData.SizeX = SizeX;
			FrameData.SizeY = SizeY;
			CutData.push_back(FrameData);
			Start.x += SizeX;
		}

		Start.x = 0.0f;
		Start.y += SizeY;
	}
}

void GameEngineTexture::TextureCreate(const D3D11_TEXTURE2D_DESC& _Desc)
{
	Desc = _Desc;

	GameEngineDevice::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("텍스처 생성에 실패했습니다.");
		return;
	}
}

PixelColor GameEngineTexture::GetPixelToPixelColor(int _x, int _y)
{
	if (0 > _x)
	{
		return PixelColor();
	}

	if (0 > _y)
	{
		return PixelColor();
	}

	if (Image.GetMetadata().width <= _x)
	{
		return PixelColor();
	}

	if (Image.GetMetadata().height <= _y)
	{
		return PixelColor();
	}

	// 여러분들이 생각하기에 색깔이 이상하다고 생각하면
	DXGI_FORMAT Fmt = Image.GetMetadata().format;

	uint8_t* Color = Image.GetImages()->pixels;

	PixelColor ReturnColor;


	switch (Fmt)
	{
	case DXGI_FORMAT_UNKNOWN:
		break;
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32B32A32_UINT:
		break;
	case DXGI_FORMAT_R32G32B32A32_SINT:
		break;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32B32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32B32_UINT:
		break;
	case DXGI_FORMAT_R32G32B32_SINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_SNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		break;
	case DXGI_FORMAT_R32G32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32_UINT:
		break;
	case DXGI_FORMAT_R32G32_SINT:
		break;
	case DXGI_FORMAT_R32G8X24_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		break;
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		break;
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		break;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		break;
	case DXGI_FORMAT_R10G10B10A2_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10A2_UINT:
		break;
	case DXGI_FORMAT_R11G11B10_FLOAT:
		break;
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	{
		int Index = _y * static_cast<int>(Image.GetMetadata().width) + _x;
		Color = Color + (Index * 4);

		ReturnColor.r = Color[0];
		ReturnColor.g = Color[1];
		ReturnColor.b = Color[2];
		ReturnColor.a = Color[3];
		break;
	}
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		break;
	case DXGI_FORMAT_R8G8B8A8_SNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		break;
	case DXGI_FORMAT_R16G16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16_UNORM:
		break;
	case DXGI_FORMAT_R16G16_UINT:
		break;
	case DXGI_FORMAT_R16G16_SNORM:
		break;
	case DXGI_FORMAT_R16G16_SINT:
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT:
		break;
	case DXGI_FORMAT_R32_FLOAT:
		break;
	case DXGI_FORMAT_R32_UINT:
		break;
	case DXGI_FORMAT_R32_SINT:
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		break;
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		break;
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8_UNORM:
		break;
	case DXGI_FORMAT_R8G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_SNORM:
		break;
	case DXGI_FORMAT_R8G8_SINT:
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		break;
	case DXGI_FORMAT_R16_FLOAT:
		break;
	case DXGI_FORMAT_D16_UNORM:
		break;
	case DXGI_FORMAT_R16_UNORM:
		break;
	case DXGI_FORMAT_R16_UINT:
		break;
	case DXGI_FORMAT_R16_SNORM:
		break;
	case DXGI_FORMAT_R16_SINT:
		break;
	case DXGI_FORMAT_R8_TYPELESS:
		break;
	case DXGI_FORMAT_R8_UNORM:
		break;
	case DXGI_FORMAT_R8_UINT:
		break;
	case DXGI_FORMAT_R8_SNORM:
		break;
	case DXGI_FORMAT_R8_SINT:
		break;
	case DXGI_FORMAT_A8_UNORM:
		break;
	case DXGI_FORMAT_R1_UNORM:
		break;
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		break;
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
		break;
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		break;
	case DXGI_FORMAT_BC1_TYPELESS:
		break;
	case DXGI_FORMAT_BC1_UNORM:
		break;
	case DXGI_FORMAT_BC1_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC2_TYPELESS:
		break;
	case DXGI_FORMAT_BC2_UNORM:
		break;
	case DXGI_FORMAT_BC2_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC3_TYPELESS:
		break;
	case DXGI_FORMAT_BC3_UNORM:
		break;
	case DXGI_FORMAT_BC3_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC4_TYPELESS:
		break;
	case DXGI_FORMAT_BC4_UNORM:
		break;
	case DXGI_FORMAT_BC4_SNORM:
		break;
	case DXGI_FORMAT_BC5_TYPELESS:
		break;
	case DXGI_FORMAT_BC5_UNORM:
		break;
	case DXGI_FORMAT_BC5_SNORM:
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		break;
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC6H_TYPELESS:
		break;
	case DXGI_FORMAT_BC6H_UF16:
		break;
	case DXGI_FORMAT_BC6H_SF16:
		break;
	case DXGI_FORMAT_BC7_TYPELESS:
		break;
	case DXGI_FORMAT_BC7_UNORM:
		break;
	case DXGI_FORMAT_BC7_UNORM_SRGB:
		break;
	case DXGI_FORMAT_AYUV:
		break;
	case DXGI_FORMAT_Y410:
		break;
	case DXGI_FORMAT_Y416:
		break;
	case DXGI_FORMAT_NV12:
		break;
	case DXGI_FORMAT_P010:
		break;
	case DXGI_FORMAT_P016:
		break;
	case DXGI_FORMAT_420_OPAQUE:
		break;
	case DXGI_FORMAT_YUY2:
		break;
	case DXGI_FORMAT_Y210:
		break;
	case DXGI_FORMAT_Y216:
		break;
	case DXGI_FORMAT_NV11:
		break;
	case DXGI_FORMAT_AI44:
		break;
	case DXGI_FORMAT_IA44:
		break;
	case DXGI_FORMAT_P8:
		break;
	case DXGI_FORMAT_A8P8:
		break;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		break;
	case DXGI_FORMAT_P208:
		break;
	case DXGI_FORMAT_V208:
		break;
	case DXGI_FORMAT_V408:
		break;
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
		break;
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
		break;
	case DXGI_FORMAT_FORCE_UINT:
		break;
	default:
		break;
	}



	return ReturnColor;
}

float4 GameEngineTexture::GetPixelToFloat4(int _x, int _y)
{
	PixelColor Color = GetPixelToPixelColor(_x, _y);

	return float4(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f, Color.a / 255.0f);
}
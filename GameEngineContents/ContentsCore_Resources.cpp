#include "PreCompile.h"
#include "ContentsCore.h"

#include <math.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

// Resources Header
#include <GameEngineCore/GameEngineStructuredBuffer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineVertexs.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineVertexBuffer.h>
#include <GameEngineCore/GameEngineIndexBuffer.h>
#include <GameEngineCore/GameEngineInstancingBuffer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineDepthStencil.h>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineInputLayOut.h>
#include <GameEngineCore/GameEngineFBXMesh.h>
#include <GameEngineCore/GameEngineFBXAnimation.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRasterizer.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineMaterial.h>

void CreateContentsMesh()
{

}

void CreateContentsInputLayout()
{
	GameEngineVertex::LayOut.AddInputLayOut("CLONEDTEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
}

void CompileContentsShader()
{
	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory("GameEngineResources");
	Dir.Move("ContentsResources");
	Dir.Move("Shader");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
	}
}

void CreateContentsMaterial()
{
	std::weak_ptr<GameEngineMaterial> FadeMaterial = GameEngineMaterial::Create("Fade");
	FadeMaterial.lock()->SetVertexShader("Fade.hlsl");
	FadeMaterial.lock()->SetPixelShader("Fade.hlsl");

	std::weak_ptr<GameEngineMaterial> ContentsBlurMaterial = GameEngineMaterial::Create("ContentsBlur");
	ContentsBlurMaterial.lock()->SetVertexShader("ContentsBlur.hlsl");
	ContentsBlurMaterial.lock()->SetPixelShader("ContentsBlur.hlsl");

	std::weak_ptr<GameEngineMaterial> ContentsBloomMaterial = GameEngineMaterial::Create("ContentsBloom");
	ContentsBloomMaterial.lock()->SetVertexShader("ContentsBloom.hlsl");
	ContentsBloomMaterial.lock()->SetPixelShader("ContentsBloom.hlsl");

	std::weak_ptr<GameEngineMaterial> ContentsPaperBurnMaterial = GameEngineMaterial::Create("PaperBurn");
	ContentsPaperBurnMaterial.lock()->SetVertexShader("PaperBurn.hlsl");
	ContentsPaperBurnMaterial.lock()->SetPixelShader("PaperBurn.hlsl");

	std::weak_ptr<GameEngineMaterial> ContentsBillboardMaterial = GameEngineMaterial::Create("Billboard");
	ContentsBillboardMaterial.lock()->SetVertexShader("Billboard.hlsl");
	ContentsBillboardMaterial.lock()->SetPixelShader("Billboard.hlsl");

	std::weak_ptr<GameEngineMaterial> ContentsPreviousColorMaterial = GameEngineMaterial::Create("PreviousColor");
	ContentsPreviousColorMaterial.lock()->SetVertexShader("PreviousColor.hlsl");
	ContentsPreviousColorMaterial.lock()->SetPixelShader("PreviousColor.hlsl");
	
	// std::weak_ptr<GameEngineMaterial> ContentsShaderMaterial = GameEngineMaterial::Create("ContentsShader");
	// ContentsBlurMaterial.lock()->SetVertexShader("ContentsShader.hlsl");
	// ContentsBlurMaterial.lock()->SetPixelShader("ContentsShader.hlsl");
}

void CreateContentsBlendAndDepthStencilDesc()
{
	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
			// 픽셀을 렌더링 대상으로 설정할 때 알파-검사(alpha-to-coverage)를 다중 샘플링 기술로 사용할지 여부를 지정합니다.
		Desc.IndependentBlendEnable = FALSE;
			// 동시 렌더링 대상에서 독립적인 혼합을 사용할지 여부를 지정합니다. 독립적인 혼합을 사용하도록 설정하려면 TRUE 로 설정합니다.
			// FALSE로 설정하면 RenderTarget[0] 멤버만 사용됩니다. RenderTarget[1..7]은 무시됩니다.

		Desc.RenderTarget[0].BlendEnable = true;
			// 혼합을 사용하거나 사용하지 않도록 설정합니다.

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
			// 픽셀 셰이더가 출력하는 RGB 값에 대해 수행할 작업을 지정합니다. BlendOp 멤버는 SrcBlend 및 DestBlend 작업을 결합하는 방법을 정의합니다.
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
			// 렌더링 대상의 현재 RGB 값에 대해 수행할 작업을 지정합니다. BlendOp 멤버는 SrcBlend 및 DestBlend 작업을 결합하는 방법을 정의합니다.
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_MAX;
			// SrcBlend 및 DestBlend 작업을 결합하는 방법을 정의합니다.

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
			// 픽셀 셰이더가 출력하는 알파 값에 대해 수행할 작업을 지정합니다. _COLOR 끝나는 혼합 옵션은 허용되지 않습니다. 
			// BlendOpAlpha 멤버는 SrcBlendAlpha 및 DestBlendAlpha 작업을 결합하는 방법을 정의합니다.
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
			// 렌더링 대상의 현재 알파 값에 대해 수행할 작업을 지정합니다. _COLOR 끝나는 혼합 옵션은 허용되지 않습니다. 
			// BlendOpAlpha 멤버는 SrcBlendAlpha 및 DestBlendAlpha 작업을 결합하는 방법을 정의합니다.
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_MAX;
			// SrcBlendAlpha 및 DestBlendAlpha 작업을 결합하는 방법을 정의합니다.

		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			// 쓰기 마스크입니다. https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_color_write_enable#constants

		GameEngineBlend::Create("Lighten", Desc);
	}
}

void LoadContentsUITexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Asset");
	Dir.Move("GlobalUI");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());
	}
}

void ContentsCore::InitializeContentsResource()
{
	CreateContentsMesh();

	CreateContentsInputLayout();

	CompileContentsShader();

	CreateContentsMaterial();

	CreateContentsBlendAndDepthStencilDesc();

	LoadContentsUITexture();
}

void ContentsCore::DestroyContentsResource()
{

}

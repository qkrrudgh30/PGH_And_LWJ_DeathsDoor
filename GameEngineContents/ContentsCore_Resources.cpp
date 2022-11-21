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
}

void CreateContentsBlendAndDepthStencilDesc()
{
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

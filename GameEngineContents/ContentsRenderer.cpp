#include "PreCompile.h"
#include "ContentsRenderer.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineVertexShader.h>

ContentsRenderer::ContentsRenderer() 
	: mShaderingInfo()
{
}

ContentsRenderer::~ContentsRenderer() 
{
}

void ContentsRenderer::Render(float _fDeltatime)
{
	if (ResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit.lock()->Render(_fDeltatime);
	}
	else if (ResourceType::Static == mShaderingInfo.miResourceType)
	{

	}
	else if (ResourceType::Animator == mShaderingInfo.miResourceType)
	{

	}
}

void ContentsRenderer::SetTexture(const std::string& _strTextureName)
{
	mwptrCurrent2DTexture = GetShaderResources().SetTexture("Tex", _strTextureName);

	mShaderingInfo.miResourceType = ResourceType::UI;
}

void ContentsRenderer::SetMesh(const std::string& _strMeshName)
{
	if (ResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit.lock()->SetMesh(_strMeshName);

		mShaderingInfo.miResourceType = ResourceType::Static;
	}
	else if (ResourceType::Static == mShaderingInfo.miResourceType)
	{

	}
	else if (ResourceType::Animator == mShaderingInfo.miResourceType)
	{

	}
	
}

void ContentsRenderer::SetMaterial(const std::string& _strMaterialName)
{
	if (ResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit.lock()->SetMaterial(_strMaterialName);
		mwptrRenderingUnit.lock()->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	}
	else if (ResourceType::Static == mShaderingInfo.miResourceType)
	{

	}
	else if (ResourceType::Animator == mShaderingInfo.miResourceType)
	{

	}
}

void ContentsRenderer::SetShader(ShaderBitFlag _eShaderType)
{
	mShaderingInfo.miShaderType |= _eShaderType;

	int a = 100;
}

void ContentsRenderer::SetPivot()
{
}

void ContentsRenderer::SetTexture()
{
}

void ContentsRenderer::Set2DUIShaderingInfo()
{
	 mShaderingInfo.miResourceType = ResourceType::UI;
	 mShaderingInfo.miShaderType = ShaderBitFlag::eNone;

	 mShaderingInfo.miIsUnityTexture = False;

	 mShaderingInfo.mf4FrameData.PosX = 0.f;
	 mShaderingInfo.mf4FrameData.PosY = 0.f;
	 mShaderingInfo.mf4FrameData.SizeX = 1.f;
	 mShaderingInfo.mf4FrameData.SizeY = 1.f;

	 mShaderingInfo.mf4PivotPos = float4::ZERO;

	 mShaderingInfo.mfFadeAccValue = 0.f;

	 mShaderingInfo.muBlurDirection = BlurType::eVerticalAndHorizontal;
	 mShaderingInfo.muBlurAppliedCount = 1u;

	 mShaderingInfo.mfBloomLuminanceThreshold = 0.3f;
	 mShaderingInfo.mfBloomIntensity = 1.f;
}

void ContentsRenderer::Set3DStaticShaderingInfo()
{
}

void ContentsRenderer::Set3DAnimatorShaderingInfo()
{
}

void ContentsRenderer::Start(void)
{
	GameEngineRenderer::Start();

	if (ResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit = std::make_shared<GameEngineRenderUnit>();
	}
	else if (ResourceType::Static == mShaderingInfo.miResourceType)
	{

	}
	else if (ResourceType::Animator == mShaderingInfo.miResourceType)
	{

	}
	
}

void ContentsRenderer::Update(float _fDeltatime)
{
}

void ContentsRenderer::InitializeShaderingInfo(void)
{
	if (ResourceType::UI == mShaderingInfo.miResourceType)
	{
		Set2DUIShaderingInfo();
	}
	else if (ResourceType::Static == mShaderingInfo.miResourceType)
	{
		Set3DStaticShaderingInfo();
	}
	else if (ResourceType::Animator == mShaderingInfo.miResourceType)
	{
		Set3DAnimatorShaderingInfo();
	}
}

void ContentsRenderer::SetRenderingPipeline(void)
{
	InitializeShaderingInfo();

	SetMaterial("ContentsShader");

	GetShaderResources().SetConstantBufferLink("ShaderingInfo", mShaderingInfo);
}


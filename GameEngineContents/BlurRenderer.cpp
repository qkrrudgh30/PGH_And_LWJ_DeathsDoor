#include "PreCompile.h"
#include "BlurRenderer.h"

#include <GameEngineCore/GameEngineTextureRenderer.h>

BlurRenderer::BlurRenderer() 
	: mBlurInfo()
{
}

BlurRenderer::~BlurRenderer() 
{
}

void BlurRenderer::SetPivot(PIVOTMODE _ePivotMode)
{
	switch (_ePivotMode)
	{
	case PIVOTMODE::CENTER:
		mBlurInfo.mf4PivotPos = float4::ZERO;
		break;
	case PIVOTMODE::BOT:
		mBlurInfo.mf4PivotPos = float4(0.0f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::TOP:
		mBlurInfo.mf4PivotPos = float4(0.0f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFT:
		mBlurInfo.mf4PivotPos = float4(0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHT:
		mBlurInfo.mf4PivotPos = float4(-0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTTOP:
		mBlurInfo.mf4PivotPos = float4(0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTTOP:
		mBlurInfo.mf4PivotPos = float4(-0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTBOT:
		mBlurInfo.mf4PivotPos = float4(0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTBOT:
		mBlurInfo.mf4PivotPos = float4(-0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::CUSTOM:
		break;
	default:
		break;
	}
}

void BlurRenderer::SetBlurInfo(unsigned int _uBlurType, unsigned int _uAppliedCount, int _iIsUnityTexture)
{
	mBlurInfo.miIsUnityTexture = _iIsUnityTexture;
}

void BlurRenderer::SetTexture(const std::string& _strTextureName)
{
	mwptrCurrentTexture = GetShaderResources().SetTexture("Tex", _strTextureName);
}

void BlurRenderer::Start(void)
{
	SetBlurRenderingPipeline();
}

void BlurRenderer::Update(float _fDetatime)
{

}

void BlurRenderer::InitializeBlurInfo(void)
{
	mBlurInfo.mf4FrameData.PosX = 0.f;
	mBlurInfo.mf4FrameData.PosY = 0.f;
	mBlurInfo.mf4FrameData.SizeX = 1.f;
	mBlurInfo.mf4FrameData.SizeY = 1.f;

	mBlurInfo.mf4PivotPos = float4::ZERO;

	mBlurInfo.miIsUnityTexture = False;
}

void BlurRenderer::SetBlurRenderingPipeline(void)
{
	InitializeBlurInfo();

	SetMaterial("Blur");

	GetShaderResources().SetConstantBufferLink("BlurInfo", mBlurInfo);
}

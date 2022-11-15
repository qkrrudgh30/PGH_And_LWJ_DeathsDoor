#include "PreCompile.h"
#include "FadeRenderer.h"

#include <GameEngineCore/GameEngineTextureRenderer.h>

FadeRenderer::FadeRenderer() 
	: mFadeInfo()
{
}

FadeRenderer::~FadeRenderer() 
{
}

void FadeRenderer::SetPivot(PIVOTMODE _mode)
{
	switch (_mode)
	{
	case PIVOTMODE::CENTER:
		mFadeInfo.mf4PivotPos = float4::ZERO;
		break;
	case PIVOTMODE::BOT:
		mFadeInfo.mf4PivotPos = float4(0.0f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::TOP:
		mFadeInfo.mf4PivotPos = float4(0.0f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFT:
		mFadeInfo.mf4PivotPos = float4(0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHT:
		mFadeInfo.mf4PivotPos = float4(-0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTTOP:
		mFadeInfo.mf4PivotPos = float4(0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTTOP:
		mFadeInfo.mf4PivotPos = float4(-0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTBOT:
		mFadeInfo.mf4PivotPos = float4(0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTBOT:
		mFadeInfo.mf4PivotPos = float4(-0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::CUSTOM:
		break;
	default:
		break;
	}
}

void FadeRenderer::Start()
{
}

void FadeRenderer::InitializeFadeInfo(void)
{
	mFadeInfo.mfFrom = 0.f;
	mFadeInfo.mfTo = 1.f;
	mFadeInfo.miWrapping = False;
	mFadeInfo.miLoop = False;
	mFadeInfo.miIsUnityTexture = False;
	mFadeInfo.mf4PivotPos = float4::ZERO;	
}

void FadeRenderer::SetFadeRendererSetting(void)
{
	InitializeFadeInfo();

	SetPipeLine("Fade");
	
	GetShaderResources().SetConstantBufferLink("FadeInfo", mFadeInfo);

}


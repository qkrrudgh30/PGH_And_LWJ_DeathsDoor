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

void FadeRenderer::SetFadeInfo(float _fFromAlphaValue, float _fToAlphaValue, float _fSpeed, int _iIsWrapping, int _iIsLoop, int _iIsUnityTexture)
{
	mFadeInfo.mfFromAlphaValue = _fFromAlphaValue;
	mFadeInfo.mfToAlphaValue = _fToAlphaValue;
	mFadeInfo.mfSpeed = _fSpeed;
	mFadeInfo.miIsWrapping = _iIsWrapping;
	mFadeInfo.miIsLoop = _iIsLoop;
	mFadeInfo.miIsUnityTexture = _iIsUnityTexture;
}

void FadeRenderer::SetTexture(const std::string& _strTextureName)
{
	mwpCurrTexture = GetShaderResources().SetTexture("Tex", _strTextureName);
}

void FadeRenderer::Start()
{
	SetFadeRendererSetting();
}

void FadeRenderer::Update(float _fDeltatime)
{
	mFadeInfo.mfDeltatime = _fDeltatime;
}

void FadeRenderer::InitializeFadeInfo(void)
{
	mFadeInfo.mf4FrameData.PosX = 0.f;
	mFadeInfo.mf4FrameData.PosY = 0.f;
	mFadeInfo.mf4FrameData.SizeX = 1.f;
	mFadeInfo.mf4FrameData.SizeY = 1.f;

	mFadeInfo.mf4PivotPos = float4::ZERO;

	mFadeInfo.mfFromAlphaValue = 0.f;
	mFadeInfo.mfToAlphaValue = 1.f;
	mFadeInfo.mfDeltatime = 0.f;
	mFadeInfo.mfSpeed = 10.f;
	mFadeInfo.miIsWrapping = False;
	mFadeInfo.miIsLoop = False;
	mFadeInfo.miIsUnityTexture = False;
}

void FadeRenderer::SetFadeRendererSetting(void)
{
	InitializeFadeInfo();

	SetPipeLine("Fade");
	
	GetShaderResources().SetConstantBufferLink("FadeInfo", mFadeInfo);
}


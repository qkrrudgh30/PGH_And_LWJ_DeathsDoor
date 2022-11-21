#include "PreCompile.h"
#include "FadeRenderer.h"

#include <GameEngineCore/GameEngineTextureRenderer.h>

FadeRenderer::FadeRenderer() 
	: mFadeInfo()
	, mfHoldingAccTimeForFade(0.f)
	, mfCurrentAccTimeForFade(0.f)
	, mbIsLooped(false)
	, miInAndOut(1)
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

void FadeRenderer::SetFadeInfo(int _iInAndOut, float _fHoldingTime, bool _bIsLooped, int _iIsUnityTexture)
{
	miInAndOut = _iInAndOut;
	mfHoldingAccTimeForFade = _fHoldingTime;
	mbIsLooped = _bIsLooped;
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
	mfCurrentAccTimeForFade += (_fDeltatime / mfHoldingAccTimeForFade);
	mFadeInfo.mfAccValue = mFadeInfo.mfAccValue + (_fDeltatime / mfHoldingAccTimeForFade) * miInAndOut;

	if (true == mbIsLooped && mfHoldingAccTimeForFade <= mfCurrentAccTimeForFade)
	{
		miInAndOut = miInAndOut * -1;
		mfCurrentAccTimeForFade = 0.f;
	}
}

void FadeRenderer::InitializeFadeInfo(void)
{
	mFadeInfo.mf4FrameData.PosX = 0.f;
	mFadeInfo.mf4FrameData.PosY = 0.f;
	mFadeInfo.mf4FrameData.SizeX = 1.f;
	mFadeInfo.mf4FrameData.SizeY = 1.f;

	mFadeInfo.mf4PivotPos = float4::ZERO;

	mFadeInfo.mfAccValue = 0.f;
	mFadeInfo.miIsUnityTexture = False;
}

void FadeRenderer::SetFadeRendererSetting(void)
{
	InitializeFadeInfo();

	SetPipeLine("Fade");
	
	GetShaderResources().SetConstantBufferLink("FadeInfo", mFadeInfo);
}


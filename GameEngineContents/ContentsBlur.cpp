#include "PreCompile.h"
#include "ContentsBlur.h"

ContentsBlur::ContentsBlur()
{
}

ContentsBlur::~ContentsBlur()
{
}

void ContentsBlur::EffectInit()
{
	msptrRenderTargetForBlur = std::make_shared<GameEngineRenderTarget>();
	msptrRenderTargetForBlur->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	InitializeBlurInfo();

	mAppliedRenderUnit.SetPipeLine("ContentsBlur");
}

void ContentsBlur::Effect(std::shared_ptr<GameEngineRenderTarget> _sptrRenderTarget)
{
	msptrRenderTargetForBlur->Copy(_sptrRenderTarget);
	// msptrRenderTargetForBlur을 모두 지우고, _sptrRenderTarget의 그림을 그려라.

	mAppliedRenderUnit.ShaderResources.SetTexture("Tex", msptrRenderTargetForBlur->GetRenderTargetTexture(0));
	// msptrRenderTargetForBlur에 그려진 그림을 mAppliedRenderUnit의 셰이더 리소스로 세팅함. (셰이더가 적용되게 하기 위함.)

	_sptrRenderTarget->Clear();
	_sptrRenderTarget->Setting();
	_sptrRenderTarget->Effect(mAppliedRenderUnit);
	// _sptrRenderTarget에다가 완성된 mAppliedRenderUnit의 효과가 적용되게끔 함.

}

void ContentsBlur::SetBlurInfo(unsigned int _uBlurType, unsigned int _uAppliedCount, float _fRadius, int _iIsUnityTexture)
{
	mBlurInfo.muAppliedType = _uBlurType;
	mBlurInfo.muAppliedCount = _uAppliedCount;
	mBlurInfo.mfRadius = _fRadius;
	mBlurInfo.miIsUnityTexture = _iIsUnityTexture;
}

void ContentsBlur::InitializeBlurInfo(void)
{
	mBlurInfo.mf4FrameData.PosX = 0.f;
	mBlurInfo.mf4FrameData.PosY = 0.f;
	mBlurInfo.mf4FrameData.SizeX = 1.f;
	mBlurInfo.mf4FrameData.SizeY = 1.f;

	mBlurInfo.mf4PivotPos = float4::ZERO;

	mBlurInfo.muAppliedType = BlurType::eVerticalAndHorizontal;
	mBlurInfo.muAppliedCount = 1u;

	mBlurInfo.mfRadius = 0.f;

	mBlurInfo.miIsUnityTexture = False;
}


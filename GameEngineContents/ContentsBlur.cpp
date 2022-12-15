#include "PreCompile.h"
#include "ContentsBlur.h"

ContentsBlur::ContentsBlur()
	: mBlurInfo{}
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

	msptrAppliedRenderUnit = std::make_shared<GameEngineRenderUnit>();

	msptrAppliedRenderUnit->SetMesh("FullRect");
	msptrAppliedRenderUnit->SetMaterial("ContentsBlur");
	msptrAppliedRenderUnit->ShaderResources.SetConstantBufferLink("BlurInfo", mBlurInfo);
}

void ContentsBlur::Effect(std::shared_ptr<GameEngineRenderTarget> _sptrRenderTarget)
{
	msptrRenderTargetForBlur->Copy(_sptrRenderTarget);
	// msptrRenderTargetForBlur을 모두 지우고, _sptrRenderTarget의 그림을 그려라.

	msptrAppliedRenderUnit->ShaderResources.SetTexture("Tex", msptrRenderTargetForBlur->GetRenderTargetTexture(0u));
	// msptrRenderTargetForBlur에 그려진 그림을 mAppliedRenderUnit의 셰이더 리소스로 세팅함. (셰이더가 적용되게 하기 위함.)

	_sptrRenderTarget->Clear();
	_sptrRenderTarget->Setting();
	_sptrRenderTarget->Effect(msptrAppliedRenderUnit);
	// _sptrRenderTarget에다가 완성된 mAppliedRenderUnit의 효과가 적용되게끔 함.

}

void ContentsBlur::SetBlurInfo(unsigned int _uOnOff, unsigned int _uAppliedArea, float _fIntence)
{
	mBlurInfo.muOnOff = _uOnOff;
	mBlurInfo.muAppliedArea = _uAppliedArea;
	mBlurInfo.mfIntence = _fIntence;
}

void ContentsBlur::InitializeBlurInfo(void)
{
	mBlurInfo.muOnOff = 0u;
	mBlurInfo.muAppliedArea = 3u;
	mBlurInfo.mfIntence = 0.f;

	mBlurInfo.mf4WindowSize.x = GameEngineWindow::GetScale().x;
	mBlurInfo.mf4WindowSize.y = GameEngineWindow::GetScale().y;
}


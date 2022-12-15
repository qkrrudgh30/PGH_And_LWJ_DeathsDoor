#include "PreCompile.h"
#include "ContentsBloom.h"

ContentsBloom::ContentsBloom() 
	: mBloomInfo{}
{
}

ContentsBloom::~ContentsBloom() 
{
}

void ContentsBloom::EffectInit()
{
	msptrRenderTargetForBloom = std::make_shared<GameEngineRenderTarget>();
	msptrRenderTargetForBloom->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	InitializeBloomInfo();

	msptrAppliedRenderUnit = std::make_shared<GameEngineRenderUnit>();

	msptrAppliedRenderUnit->SetMesh("FullRect");
	msptrAppliedRenderUnit->SetMaterial("ContentsBloom");
	msptrAppliedRenderUnit->ShaderResources.SetConstantBufferLink("BloomInfo", mBloomInfo);
}

void ContentsBloom::Effect(std::shared_ptr<GameEngineRenderTarget> _sptrRenderTarget)
{
	msptrRenderTargetForBloom->Copy(_sptrRenderTarget);

	msptrAppliedRenderUnit->ShaderResources.SetTexture("Tex", msptrRenderTargetForBloom->GetRenderTargetTexture(0u));

	_sptrRenderTarget->Clear();
	_sptrRenderTarget->Setting();
	_sptrRenderTarget->Effect(msptrAppliedRenderUnit);
}

void ContentsBloom::SetBloomInfo(unsigned int _uOnOff, unsigned int muAppliedArea, float _fLuminance, float _fIntence)
{
	mBloomInfo.muOnOff = _uOnOff;
	mBloomInfo.muAppliedArea = muAppliedArea;
	mBloomInfo.mfLuminance = _fLuminance;
	mBloomInfo.mfIntence = _fIntence;
}

void ContentsBloom::InitializeBloomInfo(void)
{
	mBloomInfo.muOnOff = 0u;
	mBloomInfo.muAppliedArea = 1u;
	mBloomInfo.mfLuminance = 0.3f;
	mBloomInfo.mfIntence = 0.f;

	mBloomInfo.mf4WindowSize.x = GameEngineWindow::GetScale().x;
	mBloomInfo.mf4WindowSize.y = GameEngineWindow::GetScale().y;
}

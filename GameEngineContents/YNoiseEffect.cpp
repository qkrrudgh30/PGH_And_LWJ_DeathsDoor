#include "PreCompile.h"
#include "YNoiseEffect.h"

YNoiseEffect::YNoiseEffect() 
	: CopyTarget(nullptr)
{
}

YNoiseEffect::~YNoiseEffect() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
	}
}


void YNoiseEffect::EffectInit()
{

	// EffectSet.SetPipeLine("YEffect");


	

	// EffetSet
}

void YNoiseEffect::Effect(GameEngineRenderTarget* _Target)
{
	//if (nullptr == CopyTarget)
	//{
	//	CopyTarget = new GameEngineRenderTarget();
	//	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	//	CopyTarget->Copy(_Target);
	//	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	//	EffectSet.ShaderResources.SetConstantBufferLink("RenderOption", Option);
	//	Option.DeltaTime = 0.0f;
	//	Option.SumDeltaTime = 0.0f;
	//}

	//Option.DeltaTime = GameEngineTime::GetDeltaTime();
	//Option.SumDeltaTime += GameEngineTime::GetDeltaTime();;

	//// _Target->Copy(CopyTarget);
	//_Target->Setting();
	//_Target->Effect(EffectSet);

}
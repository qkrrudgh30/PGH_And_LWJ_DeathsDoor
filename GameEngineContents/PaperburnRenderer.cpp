#include "PreCompile.h"
#include "PaperburnRenderer.h"

PaperburnRenderer::PaperburnRenderer() 
{
}

PaperburnRenderer::~PaperburnRenderer() 
{
}

void PaperburnRenderer::InitializePaperBurn(std::shared_ptr<GameEngineFBXAnimationRenderer>& _sptrFBXAnimationRenderer)
{
	size_t uMeshCount = _sptrFBXAnimationRenderer->GetAllRenderUnit().size();
	std::vector<size_t> vuSubsetCount;
	vuSubsetCount.resize(uMeshCount, 0);
	for (size_t i = 0; i < uMeshCount; ++i)
	{
		vuSubsetCount.at(i) = _sptrFBXAnimationRenderer->GetAllRenderUnit()[i].size();
	}

	for (size_t i = 0; i < uMeshCount; ++i)
	{
		for (size_t j = 0; j < vuSubsetCount.at(i); ++j)
		{
			_sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].GetCloneMaterial()->SetVertexShader("PaperBurn.hlsl");
			_sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].GetCloneMaterial()->SetPixelShader("PaperBurn.hlsl");

			if (true == _sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].ShaderResources.IsConstantBuffer("PaperBurnInfo"))
			{
				_sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].ShaderResources.SetConstantBufferLink("PaperBurnInfo", mPaperBurnInfo);
			}

			if (true == _sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].ShaderResources.IsTexture("CloudTexture"))
			{
				_sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].ShaderResources.SetTexture("CloudTexture", "CloudTexture.png");
			}

		}
	}
}

void PaperburnRenderer::SetPaperBurnInfo(unsigned int _uOnOffPaperBurn, float _fEffectTime)
{
	mPaperBurnInfo.muOnOffPaperBurn = _uOnOffPaperBurn;
	mPaperBurnInfo.mfEffectTime = _fEffectTime;
}

void PaperburnRenderer::Start()
{
}

void PaperburnRenderer::Update(float _fDeltatime)
{
	/*InitializePaperBurn(FBXAnimationRenderer);

	if (m_Info.m_Hp <= 0 && false == bOnce)
	{
		Death(3.f);
		bOnce = true;
		bOnDeath = true;
	}

	if (m_Info.m_Hp <= 0 && true == bOnDeath)
	{
		static float fSinTime = 0.f;
		fSinTime += std::sin(_DeltaTime) / 30.f;
		SetPaperBurnInfo(1u, fSinTime);
	}*/
}

void PaperburnRenderer::End()
{
}


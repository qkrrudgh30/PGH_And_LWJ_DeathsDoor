#include "PreCompile.h"
#include "LoadingUI.h"
#include "ContentsCore.h"
#include "ContentsLevel.h"

bool LoadingUI::mbIsFirstLoadingStage = true;

LoadingUI::LoadingUI() 
	: mpUIRendererForBackground(nullptr)
	, mpUIRendererForProgressBar(nullptr)
	, muTotalCountOfResources(0u)
	, muCurrentCountOfLoadedResources(0u)
	, mfCrrProgressState(-1.f)
	, mfSrcProgressAmount(0.001f)
	, mfDstProgressAmount(0.f)
	, muCurrLoadingStage(eAnimatorMesh)
	, muPrevLoadingStage(eAnimatorMesh)
{
}

LoadingUI::~LoadingUI() 
{
}

void LoadingUI::Start()
{
	mpUIRendererForBackground = CreateComponent<GameEngineUIRenderer>();
	mpUIRendererForBackground->SetTexture("LoadingAnimatorsBack.png");
	mpUIRendererForBackground->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForBackground->GetTransform().SetLocalScale(float4{ 1280.f, 720.f });

	mpUIRendererForProgressBar = CreateComponent<GameEngineUIRenderer>();
	mpUIRendererForProgressBar->SetTexture("ProgressBar.png");
	mpUIRendererForProgressBar->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForProgressBar->GetTransform().SetLocalScale(float4{ 400.f, 20.f });
	mpUIRendererForProgressBar->GetTransform().SetLocalPosition(float4{ -200.f, -18.f, 0.f });
	mpUIRendererForProgressBar->SetPivot(PIVOTMODE::LEFT);
}

void LoadingUI::Update(float _DeltaTime)
{
	if (muPrevLoadingStage != muCurrLoadingStage)
	{
		switch (muCurrLoadingStage)
		{
		case eAnimatorMesh:
			mpUIRendererForBackground->SetTexture("LoadingAnimatorsBack.png");
			break;

		case eStaticMesh:
			mpUIRendererForBackground->SetTexture("LoadingStaticMeshBack.png");
			break;

		case eAnimation:
			mpUIRendererForBackground->SetTexture("LoadingAnimationBack.png");
			break;

		case eEndStage:
			break;

		default:
			break;
		}
	}

	mfSrcProgressAmount = ContentsCore::ReturnFloatLerp(mfSrcProgressAmount, mfDstProgressAmount, 2.f * _DeltaTime);
	mpUIRendererForProgressBar->GetTransform().SetLocalScale(float4{ 400.f * mfSrcProgressAmount, 20.f });

	if (eAnimation == muCurrLoadingStage && (0.998f <= mfSrcProgressAmount + 0.00001f))
	{ 
		GEngine::ChangeLevel(ContentsLevel::mstrNextLevelName);
		Death();
	}
}

void LoadingUI::End()
{
}

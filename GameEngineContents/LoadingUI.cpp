#include "PreCompile.h"
#include "LoadingUI.h"
#include "ContentsCore.h"
#include "ContentsLevel.h"

bool LoadingUI::mbIsFirstLoadingStage = true;

LoadingUI::LoadingUI() 
	: mpUIRendererForBackground(nullptr)
	, mpUIRendererForProgressBar(nullptr)
	, mpUIRendererForFont(nullptr)
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
	mpUIRendererForBackground->SetTexture("LoadingBack.png");
	mpUIRendererForBackground->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForBackground->GetTransform().SetLocalScale(float4{ 1280.f, 720.f });

	mpUIRendererForFont = CreateComponent<GameEngineUIRenderer>();
	mpUIRendererForFont->SetTexture("Loading.png");
	mpUIRendererForFont->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForFont->GetTransform().SetLocalScale(float4{ 600.f, 120.f });
	mpUIRendererForFont->GetTransform().SetLocalPosition(float4{ 0.f, 30.f, 0.f, 0.f });

	mpUIRendererForProgressBar = CreateComponent<GameEngineUIRenderer>();
	mpUIRendererForProgressBar->SetTexture("ProgressBar.png");
	mpUIRendererForProgressBar->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForProgressBar->GetTransform().SetLocalScale(float4{ 400.f, 20.f });
	mpUIRendererForProgressBar->GetTransform().SetLocalPosition(float4{ -200.f, -17.f, 0.f });
	mpUIRendererForProgressBar->SetPivot(PIVOTMODE::LEFT);
}

void LoadingUI::Update(float _DeltaTime)
{
	mfSrcProgressAmount = ContentsCore::ReturnFloatLerp(mfSrcProgressAmount, mfDstProgressAmount, 2.f * _DeltaTime);
	mpUIRendererForProgressBar->GetTransform().SetLocalScale(float4{ 400.f * mfSrcProgressAmount, 20.f });

	if (0.998f <= mfSrcProgressAmount + 0.00001f)
	{
		size_t i = 0;
		bool bLoop = true;

		for (auto loaded : ContentsLevel::mstrvecAllResourceNames)
		{
			if (nullptr == GameEngineFBXMesh::Find(loaded + ".FBX"))
			{
				bLoop = false;
			}
		}

		if (true == bLoop)
		{
			GEngine::ChangeLevel(ContentsLevel::mstrNextLevelName);
			Death();
		}
	}
}

void LoadingUI::End()
{
}

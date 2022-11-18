#include "PreCompile.h"
#include "LoadingUI.h"
#include "ContentsCore.h"
#include "ContentsLevel.h"
#include "FadeRenderer.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

bool LoadingUI::mbIsFirstLoadingStage = true;

LoadingUI::LoadingUI() 
	: mpUIRendererForBackground()
	, mpUIRendererForProgressBar()
	, mpUIRendererForFont()
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
	mpUIRendererForBackground.lock()->SetTexture("LoadingBack.png");
	mpUIRendererForBackground.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForBackground.lock()->GetTransform().SetLocalScale(float4{ 1280.f, 720.f });

	mpUIRendererForFont = CreateComponent<FadeRenderer>();
	mpUIRendererForFont.lock()->SetTexture("Loading.png");
	mpUIRendererForFont.lock()->SetFadeInfo(-1, 1.f, True);
	mpUIRendererForFont.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForFont.lock()->GetTransform().SetLocalScale(float4{ 600.f, 120.f });
	mpUIRendererForFont.lock()->GetTransform().SetLocalPosition(float4{ 0.f, 30.f, 0.f, 0.f });

	mpUIRendererForProgressBar = CreateComponent<GameEngineUIRenderer>();
	mpUIRendererForProgressBar.lock()->SetTexture("ProgressBar.png");
	mpUIRendererForProgressBar.lock()->ChangeCamera(CAMERAORDER::UICAMERA);
	mpUIRendererForProgressBar.lock()->GetTransform().SetLocalScale(float4{ 400.f, 20.f });
	mpUIRendererForProgressBar.lock()->GetTransform().SetLocalPosition(float4{ -200.f, -17.f, 0.f });
	mpUIRendererForProgressBar.lock()->SetPivot(PIVOTMODE::LEFT);
}

void LoadingUI::Update(float _DeltaTime)
{
	mfSrcProgressAmount = ContentsCore::ReturnFloatLerp(mfSrcProgressAmount, mfDstProgressAmount, 2.f * _DeltaTime);
	mpUIRendererForProgressBar.lock()->GetTransform().SetLocalScale(float4{ 400.f * mfSrcProgressAmount, 20.f });

	if (0.998f <= mfSrcProgressAmount + 0.00001f)
	{
		size_t i = 0;
		bool bLoop = true;

		for (auto loaded : ContentsLevel::mstrvecAllResourceNames)
		{
			if ("Collider" == loaded) { continue; }
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

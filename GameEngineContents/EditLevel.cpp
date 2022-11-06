#include "PreCompile.h"
#include "EditLevel.h"
#include "LoadingUI.h"

EditLevel::EditLevel()
{
}

EditLevel::~EditLevel()
{
}

void EditLevel::Start()
{
	
}

void EditLevel::Update(float _DeltaTime)
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();

		GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
		float4 CameraWorldPos = GetMainCameraActorTransform().GetWorldPosition();
		CameraWorldPos.y += 1700.f;
		CameraWorldPos.z -= 1700.f;
		GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);
	}
}

void EditLevel::End()
{
}

void EditLevel::LevelStartEvent()
{
	mpLoadingUI = CreateActor<LoadingUI>(); // Fade-In

	if ("Previous" == ContentsLevel::mstrNextLevelName) 
	{ 
		GEngine::ChangeLevel(ContentsLevel::mstrPrevLevelName);
		Death(); // Fade-Out

		return; 
	}

	PlacePathOn(ContentsLevel::mstrNextLevelName);

	if (false == ContentsLevel::mmapPrimitiveInitialized[ContentsLevel::mstrNextLevelName])
	{
		ContentsLevel::mmapPrimitiveInitialized[ContentsLevel::mstrNextLevelName] = true;

		GameEngineCore::EngineThreadPool.Work(
			[this]
			{
				LoadFBXFiles();
			});
	}
	else
	{
		GEngine::ChangeLevel(ContentsLevel::mstrNextLevelName);
		Death(); // Fade-Out
	}

	
}

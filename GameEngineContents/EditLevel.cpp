#include "PreCompile.h"
#include "EditLevel.h"
#include "LoadingUI.h"
#include "ContentsBlur.h"
#include "ContentsBloom.h"
#include "WorldLight.h"

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
	ContentsLevel::Update(_DeltaTime);

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
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		msptrContentsBlur->InitializeContentsBlur(msptrContentsBlur);
		msptrContentsBloom->InitializeBloom(msptrContentsBloom);



		mbPrimitiveInitialized = true;
	}


#pragma endregion

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
			[=]
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

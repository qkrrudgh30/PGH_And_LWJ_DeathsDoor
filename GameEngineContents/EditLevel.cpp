#include "PreCompile.h"
#include "EditLevel.h"

EditLevelPipe* EditLevelPipe::Inst = nullptr;
EditLevel* EditLevelPipe::m_ptrParentEditLevel = nullptr;

EditLevel::EditLevel()
{
}

EditLevel::~EditLevel()
{
}

void EditLevel::Start()
{
	if (nullptr == EditLevelPipe::GetInst())
	{
		EditLevelPipe temp(this);
	}
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
}

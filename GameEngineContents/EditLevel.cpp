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
	if (true == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void EditLevel::End()
{
}

void EditLevel::LevelStartEvent()
{
}

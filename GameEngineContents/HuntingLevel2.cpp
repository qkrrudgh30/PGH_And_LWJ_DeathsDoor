#include "PreCompile.h"
#include "HuntingLevel2.h"
#include "Player.h"
#include "UIMouse.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

HuntingLevel2::HuntingLevel2() 
{
}

HuntingLevel2::~HuntingLevel2() 
{
}

void HuntingLevel2::Start()
{
#pragma region LoadFBXMeshiesAndAnimation
	DirectPathAt("02_HuntingLevel2");
	LoadFBXFiles();
#pragma endregion


}

void HuntingLevel2::Update(float _DeltaTime)
{
}

void HuntingLevel2::End()
{
}

void HuntingLevel2::LevelStartEvent()
{
}

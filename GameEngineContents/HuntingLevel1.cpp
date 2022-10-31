#include "PreCompile.h"
#include "HuntingLevel1.h"
#include "Player.h"
#include "UIMouse.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

HuntingLevel1::HuntingLevel1() 
{
}

HuntingLevel1::~HuntingLevel1() 
{
}

void HuntingLevel1::Start()
{
#pragma region LoadFBXMeshiesAndAnimation
	DirectPathAt("01_HuntingLevel1");
	LoadFBXFiles();
#pragma endregion


}

void HuntingLevel1::Update(float _DeltaTime)
{
}

void HuntingLevel1::End()
{
}

void HuntingLevel1::LevelStartEvent()
{
}

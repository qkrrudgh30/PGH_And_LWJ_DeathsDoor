#include "PreCompile.h"
#include "HuntingLevel5.h"
#include "Player.h"
#include "UIMouse.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

HuntingLevel5::HuntingLevel5() 
{
}

HuntingLevel5::~HuntingLevel5() 
{
}

void HuntingLevel5::Start()
{
#pragma region LoadFBXMeshiesAndAnimation
	DirectPathAt("05_HuntingLevel5");
	LoadFBXFiles();
#pragma endregion


}

void HuntingLevel5::Update(float _DeltaTime)
{
}

void HuntingLevel5::End()
{
}

void HuntingLevel5::LevelStartEvent()
{
}

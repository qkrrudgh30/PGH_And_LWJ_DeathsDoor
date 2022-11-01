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

}

void HuntingLevel2::Update(float _DeltaTime)
{
}

void HuntingLevel2::End()
{
}

void HuntingLevel2::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		// DirectPathAt("02_HuntingLevel2");
		// LoadFBXFiles();

		// TODO

		mbPrimitiveInitialized = true;
	}
#pragma endregion


}

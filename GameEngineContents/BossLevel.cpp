#include "PreCompile.h"
#include "BossLevel.h"
#include "Player.h"
#include "UIMouse.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

BossLevel::BossLevel() 
{
}

BossLevel::~BossLevel() 
{
}

void BossLevel::Start()
{
#pragma region LoadFBXMeshiesAndAnimation
//	DirectPathAt("06_BossLevel");
//	LoadFBXFiles();
	if (false == mbPrimitiveInitialized)
	{
		// DirectPathAt("06_BossLevel");
		// LoadFBXFiles();

		// TODO

		mbPrimitiveInitialized = true;
	}
#pragma endregion


}

void BossLevel::Update(float _DeltaTime)
{
}

void BossLevel::End()
{
}

void BossLevel::LevelStartEvent()
{
}

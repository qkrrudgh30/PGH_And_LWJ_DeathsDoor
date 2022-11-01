#include "PreCompile.h"
#include "HuntingLevel4.h"
#include "Player.h"
#include "UIMouse.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

HuntingLevel4::HuntingLevel4() 
{
}

HuntingLevel4::~HuntingLevel4() 
{
}

void HuntingLevel4::Start()
{

}

void HuntingLevel4::Update(float _DeltaTime)
{
}

void HuntingLevel4::End()
{
}

void HuntingLevel4::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		// DirectPathAt("04_HuntingLevel4");
		// LoadFBXFiles();

		// TODO

		mbPrimitiveInitialized = true;
	}
#pragma endregion


}

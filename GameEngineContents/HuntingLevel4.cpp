#include "PreCompile.h"
#include "HuntingLevel4.h"
#include "Player.h"
#include "Potal.h"

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

	{

		Potal* Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
		Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-0.f });
		Potal_->m_PotalType = PotalType::Stage4ToStage3;

	}



	{

		Potal* Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
		Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-1300.F });
		Potal_->m_PotalType = PotalType::Stage4ToStage5;

	}
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


	{
		if (nullptr == Player::GetMainPlayer())
		{
			Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->SetLevelOverOn();


		}
		else
		{
			Player* NewPlayer = Player::GetMainPlayer();
			NewPlayer->GetTransform().SetWorldPosition({ 1.F,0.F,1.F });
			NewPlayer->UIOn();
			//NewPlayer->m_bLogoLevelCheck = false;

			GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
			GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
			float4 CameraWorldPos = GetMainCameraActorTransform().GetWorldPosition();
			CameraWorldPos.y += 1700.f;
			CameraWorldPos.z -= 1700.f;
			GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);



		}
	}



}

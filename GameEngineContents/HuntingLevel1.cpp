#include "PreCompile.h"
#include "HuntingLevel1.h"
#include "Player.h"

#include "TestActor.h"
#include "Potal.h"

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


	{

		Potal* Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
		Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-0.f });
		Potal_->m_PotalType = PotalType::Stage1ToStage2;

	}



	{

		Potal* Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
		Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-1300.F });
		Potal_->m_PotalType = PotalType::Stage1ToSLogin;

	}


}

void HuntingLevel1::Update(float _DeltaTime)
{
}

void HuntingLevel1::End()
{
}

void HuntingLevel1::LevelStartEvent()
{
	#pragma region LoadFBXMeshiesAndAnimation
		if (false == mbPrimitiveInitialized)
		{
			// DirectPathAt("01_HuntingLevel1");
			// LoadFBXFiles();

			// TODO

			// CreateActor<TestActor>(); // Test Code.

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

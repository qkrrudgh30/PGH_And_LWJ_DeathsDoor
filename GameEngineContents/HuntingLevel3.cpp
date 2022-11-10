#include "PreCompile.h"
#include "HuntingLevel3.h"
#include "Player.h"
#include "Potal.h"
#include "ROOM_MainHall.h"
#include "LoadingUI.h"
#include "HeadRoller.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

HuntingLevel3::HuntingLevel3() 
{
}

HuntingLevel3::~HuntingLevel3() 
{
}

void HuntingLevel3::Start()
{
}

void HuntingLevel3::Update(float _DeltaTime)
{
}

void HuntingLevel3::End()
{
}

void HuntingLevel3::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		LoadCreaturesFromFile("03_HuntingLevel3");

		{
			std::shared_ptr < ROOM_MainHall> pMap = CreateActor<ROOM_MainHall>(OBJECTORDER::StaticMesh);
		}

		{

			std::shared_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_->GetTransform().SetWorldPosition({ -1800.F,0.F,1400.F });
			Potal_->m_PotalType = PotalType::Stage3ToStage4;

		}



		{

			std::shared_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_->GetTransform().SetWorldPosition({ 692.F,0.F,439.f });
			Potal_->m_PotalType = PotalType::Stage3ToStage2;

		}


		{
			std::shared_ptr < HeadRoller> cMonster = CreateActor<HeadRoller>(OBJECTORDER::Monster);
			cMonster->GetTransform().SetWorldPosition({ 305.f,0.F,-554.f });


		}

		{
			std::shared_ptr < HeadRoller> cMonster = CreateActor<HeadRoller>(OBJECTORDER::Monster);
			cMonster->GetTransform().SetWorldPosition({ -1020.f,0.F,169.f });


		}



		{
			std::shared_ptr < HeadRoller> cMonster = CreateActor<HeadRoller>(OBJECTORDER::Monster);
			cMonster->GetTransform().SetWorldPosition({ -800.f,0.F,1071.f });


		}



		mbPrimitiveInitialized = true;
	}
#pragma endregion
	

	{
		if (nullptr == Player::GetMainPlayer())
		{
			std::shared_ptr < Player> NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->SetLevelOverOn();


		}
		else
		{
			std::shared_ptr < Player> NewPlayer = Player::GetMainPlayer();
			NewPlayer->GetTransform().SetWorldPosition({ 540.F,0.F,244.F });
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

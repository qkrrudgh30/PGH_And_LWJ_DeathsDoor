#include "PreCompile.h"
#include "HuntingLevel1.h"
#include "Player.h"
#include "Slime.h"
#include "TestActor.h"
#include "Potal.h"
#include "ROOM_Enter.h"
#include "LoadingUI.h"

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
		LoadCreaturesFromFile("01_HuntingLevel1");


		{
			std::shared_ptr < ROOM_Enter> pMap = CreateActor<ROOM_Enter>(OBJECTORDER::StaticMesh);
		}

		{

			std::shared_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_->GetTransform().SetWorldPosition({ -1231.F,0.F,-1875.F });
			Potal_->m_PotalType = PotalType::Stage1ToStage2;

		}



		{

			std::shared_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_->GetTransform().SetWorldPosition({ 503.F,0.F,-172.f });
			Potal_->m_PotalType = PotalType::Stage1ToSLogin;

		}

		mbPrimitiveInitialized = true;


		{
			std::shared_ptr < Slime> cMonster = CreateActor<Slime>(OBJECTORDER::Monster);
			cMonster->GetTransform().SetWorldPosition({ -438.f,0.F,-583.f });


		}

		{
			std::shared_ptr < Slime> cMonster = CreateActor<Slime>(OBJECTORDER::Monster);
			cMonster->GetTransform().SetWorldPosition({ -887.f,0.F,-1122.f });


		}


		{
			std::shared_ptr < Slime> cMonster = CreateActor<Slime>(OBJECTORDER::Monster);
			cMonster->GetTransform().SetWorldPosition({ 7.f,0.F,-1266.f });


		}



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
			NewPlayer->GetTransform().SetWorldPosition({ 357.F,0.F,-353.F });
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

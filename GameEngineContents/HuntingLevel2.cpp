#include "PreCompile.h"
#include "HuntingLevel2.h"
#include "Player.h"
#include "Potal.h"
#include "ROOM_Left.h"
#include "LoadingUI.h"

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
		LoadCreaturesFromFile("02_HuntingLevel2");
		mbPrimitiveInitialized = true;
	}
#pragma endregion
	{
		ROOM_Left* pMap = CreateActor<ROOM_Left>(OBJECTORDER::StaticMesh);
	}

	{

		Potal* Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
		Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-1300.F });
		Potal_->m_PotalType = PotalType::Stage2ToStage3;

	}



	{

		Potal* Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
		Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-0.f });
		Potal_->m_PotalType = PotalType::Stage2ToStage1;

	}

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

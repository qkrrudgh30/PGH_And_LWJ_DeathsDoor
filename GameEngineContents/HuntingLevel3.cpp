#include "PreCompile.h"
#include "HuntingLevel3.h"
#include "Player.h"
#include "Potal.h"
#include "ROOM_MainHall.h"
#include "LoadingUI.h"
#include "ContentsBloom.h"
#include "ContentsBlur.h"
#include "EditGUIWindow.h"

#include "Headroller.h"
#include "WorldLight.h"

#include "Firemgr.h"


#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

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
	ContentsLevel::Update(_DeltaTime);



#pragma region EngineCode
	msptrBlurCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());
	msptrBloomCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());
#pragma endregion
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
		msptrContentsBlur->InitializeContentsBlur(msptrContentsBlur);
		msptrContentsBloom->InitializeBloom(msptrContentsBloom);

		{
			std::weak_ptr < ROOM_MainHall> pMap = CreateActor<ROOM_MainHall>(OBJECTORDER::StaticMesh);
		}

		{

			std::weak_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_.lock()->GetTransform().SetWorldPosition({ -1586.F,0.F,1091.F });
			Potal_.lock()->FBXStaticRenderer->GetTransform().SetLocalRotation({ 0.f, -45.f, 0.f });

			Potal_.lock()->m_PotalType = PotalType::Stage3ToStage4;

		}



		{

			std::weak_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_.lock()->GetTransform().SetWorldPosition({ 616.F,0.F,238.f });
			Potal_.lock()->m_PotalType = PotalType::Stage3ToStage2;

		}


		//Fire
		{

			std::weak_ptr < Firemgr> Fire = CreateActor<Firemgr>(OBJECTORDER::Eff);
			Fire.lock()->GetTransform().SetWorldPosition({ 1418.f,280.f,-706.f });


		}


		{

			std::weak_ptr < Firemgr> Fire = CreateActor<Firemgr>(OBJECTORDER::Eff);
			Fire.lock()->GetTransform().SetWorldPosition({ -342.f,280.f,971.f });


		}




		{
			std::weak_ptr < Headroller> cMonster = CreateActor<Headroller>(OBJECTORDER::Monster);
			cMonster.lock()->GetTransform().SetWorldPosition({ 78.f,0.F,-1672.f });


		}


		mbPrimitiveInitialized = true;
	}
	EditGUIWindow::OffStartingLevel();
#pragma endregion
	

	{
		if (nullptr == Player::GetMainPlayer())
		{
			//std::shared_ptr < Player> NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			//NewPlayer->SetLevelOverOn();


		}
		else
		{
			Player* NewPlayer = Player::GetMainPlayer();
			NewPlayer->On();
			NewPlayer->GetTransform().SetWorldPosition({ 499.F,0.F,110.F });
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

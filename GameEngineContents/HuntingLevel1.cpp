#include "PreCompile.h"
#include "HuntingLevel1.h"
#include "Player.h"
#include "Slime.h"
#include "TestActor.h"
#include "Potal.h"
#include "ROOM_Enter.h"
#include "LoadingUI.h"
#include "ContentsBloom.h"
#include "ContentsBlur.h"
#include "EditGUIWindow.h"
#include "WorldLight.h"


#include "Firemgr.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

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
	ContentsLevel::Update(_DeltaTime);

#pragma region EngineCode

	msptrBlurCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());
	msptrBloomCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());

#pragma endregion
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
		msptrContentsBlur->InitializeContentsBlur(msptrContentsBlur);
		msptrContentsBloom->InitializeBloom(msptrContentsBloom);

		{
			std::weak_ptr < ROOM_Enter> pMap = CreateActor<ROOM_Enter>(OBJECTORDER::StaticMesh);
		}

		{

			std::weak_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_.lock()->GetTransform().SetWorldPosition({ -1025.F,0.F,-1815.F });
			Potal_.lock()->FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.7f, 0.7f, 0.7f });
			Potal_.lock()->FBXStaticRenderer->GetTransform().SetLocalRotation({ 0.f, 225.f, 0.f });
			Potal_.lock()->m_PotalType = PotalType::Stage1ToStage2;

		}


		{

			std::weak_ptr < Firemgr> Fire = CreateActor<Firemgr>(OBJECTORDER::Eff);
			Fire.lock()->GetTransform().SetWorldPosition({ -436.f,280.f,43.f });
		

		}

		{

			std::weak_ptr < Firemgr> Fire = CreateActor<Firemgr>(OBJECTORDER::Eff);
			Fire.lock()->GetTransform().SetWorldPosition({ -1109.f,280.f,-636.f });


		}



		{

			std::weak_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_.lock()->GetTransform().SetWorldPosition({ 448.F,0.F,-290.f });
			Potal_.lock()->FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
			Potal_.lock()->m_PotalType = PotalType::Stage1ToSLogin;

		}

		mbPrimitiveInitialized = true;


		{
			std::weak_ptr < Slime> cMonster = CreateActor<Slime>(OBJECTORDER::Monster);
			cMonster.lock()->GetTransform().SetWorldPosition({ -438.f,0.F,-583.f });


		}

		{
			std::weak_ptr < Slime> cMonster = CreateActor<Slime>(OBJECTORDER::Monster);
			cMonster.lock()->GetTransform().SetWorldPosition({ -887.f,0.F,-1122.f });


		}


		{
			std::weak_ptr < Slime> cMonster = CreateActor<Slime>(OBJECTORDER::Monster);
			cMonster.lock()->GetTransform().SetWorldPosition({ 7.f,0.F,-1266.f });


		}



	}
	EditGUIWindow::OffStartingLevel();




#pragma endregion
	


	{
		if (nullptr == Player::GetMainPlayer())
		{

		}
		else
		{
			Player*  NewPlayer = Player::GetMainPlayer();
			NewPlayer->On();
			NewPlayer->GetTransform().SetWorldPosition({ 340.F,0.F,-400.F });
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

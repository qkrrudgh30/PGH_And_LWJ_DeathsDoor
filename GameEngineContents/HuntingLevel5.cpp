#include "PreCompile.h"
#include "HuntingLevel5.h"
#include "Player.h"
#include "Potal.h"
#include "ROOM_Far.h"
#include "LoadingUI.h"
#include "Tower.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

HuntingLevel5::HuntingLevel5() 
{
}

HuntingLevel5::~HuntingLevel5() 
{
}

void HuntingLevel5::Start()
{
}

void HuntingLevel5::Update(float _DeltaTime)
{
}

void HuntingLevel5::End()
{
}

void HuntingLevel5::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		LoadCreaturesFromFile("05_HuntingLevel5");

		{
			std::weak_ptr < ROOM_Far> pMap = CreateActor<ROOM_Far>(OBJECTORDER::StaticMesh);
		}

		{

			std::weak_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_.lock()->GetTransform().SetWorldPosition({ -1997.F,0.F,-2317.F });
			Potal_.lock()->m_PotalType = PotalType::Stage5ToStageBoss;

		}



		{

			std::weak_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_.lock()->GetTransform().SetWorldPosition({ 650.F,0.F,415.f });
			Potal_.lock()->m_PotalType = PotalType::Stage5ToStage4;

		}

		{
			cMonster = CreateActor<Tower>(OBJECTORDER::Monster);
			
			//cMonster.lock()->m_bstart = true;

		}

		mbPrimitiveInitialized = true;
	}
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
			NewPlayer->GetTransform().SetWorldPosition({ 475.F,0.F,228.F });
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

#include "PreCompile.h"
#include "TestLevel.h"
#include "GlobalContentsValue.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineCore/GameEngineBlur.h>
#include "Player.h"
#include "Monster.h"
#include "FlowerMonster.h"


#include "TsetBackGround.h"
#include "StageMainCamera.h"


#include "ShopNPC.h"

#include "Monster.h"



TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start() 
{





	// 내가 직접 설정해줘야 합니다.
	




	{
		//TsetBackGround* TestBack = CreateActor<TsetBackGround>(OBJECTORDER::BackGround);
	}

	{
		Monster* cMonster = CreateActor<Monster>(OBJECTORDER::Monster);
		cMonster->GetTransform().SetWorldPosition({500.f,0.f,-500.f});
		

	}


	//{
	//	Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
	//	// actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 100.0f });
	//	actor->GetTransform().SetWorldScale(float4(1.0f, 1.f, 1.0f));
	//}
}

void TestLevel::LevelStartEvent()
{



#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		DirectPathAt("08_TestLevel");
		LoadFBXFiles();

	
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
			NewPlayer->GetTransform().SetWorldPosition({1.F,0.F,1.F});
			NewPlayer->UIOn();
			//NewPlayer->m_bLogoLevelCheck = false;

			GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
			GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
			float4 CameraWorldPos = GetMainCameraActorTransform().GetWorldPosition();
			CameraWorldPos.y += 1700.f;
			CameraWorldPos.z -= 1700.f;
			GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);

			{
				FlowerMonster* cMonster = CreateActor<FlowerMonster>(OBJECTORDER::Monster);
				cMonster->GetTransform().SetWorldPosition({ -500.f,0.f,-500.f });


			}


		}
	}
}


void TestLevel::Update(float _DeltaTime) 
{
	//GameEngineStatusWindow::AddDebugRenderTarget("BackBuffer", GameEngineDevice::GetBackBuffer());
	//GameEngineStatusWindow::AddDebugRenderTarget("MainCamera", GetMainCamera()->GetCameraRenderTarget());
	//GameEngineStatusWindow::AddDebugRenderTarget("UICamera", GetUICamera()->GetCameraRenderTarget());

	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		// ;
		GetMainCameraActor()->FreeCameraModeOnOff();
	}


}
void TestLevel::End() {}

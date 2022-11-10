#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include "Player.h"
#include "TestActor.h"
#include "StaticMesh.h"
#include "Hall.h"
#include "LoadingUI.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include "UIMouse.h"

#include "ShopNPC.h"
#include "Potal.h"

LoginLevel::LoginLevel()	:
	UI(nullptr)
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
	// PlacePathOn("00_LoginLevel");core
	// LoadFBXFiles();


	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
	GetMainCameraActorTransform().SetWorldRotation({ 12.f,11.f,0.f });
	float4 CameraWorldPos = GetMainCameraActorTransform().GetWorldPosition();
	CameraWorldPos.x -= 880.f;
	CameraWorldPos.y += 750.f;
	CameraWorldPos.z -= 1900.f;;
	GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);



	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}





	{
		std::shared_ptr < UIMouse> m_UIMouse = CreateActor<UIMouse>(OBJECTORDER::MouseUI);
		m_UIMouse->SetLevelOverOn();
	}
}

void LoginLevel::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		LoadCreaturesFromFile("00_LoginLevel");
		mbPrimitiveInitialized = true;
	}
#pragma endregion
	

	if (nullptr == UI)
	{


		CreateActor<Hall>(); // Test Code.


		{
			UI = CreateActor<LoginUI>(GameObjectGroup::UI);
			UI->CreateComponent<GameEngineCollision>();

			std::shared_ptr < ShopNPC> cShopNPC = CreateActor<ShopNPC>(OBJECTORDER::NPC);
			cShopNPC->GetTransform().SetWorldPosition({ -300.F,0.F,500.F });
			//	cShopNPC->GetTransform().SetWorl

		}

		{

			std::shared_ptr < Potal> Potal_ = CreateActor<Potal>(OBJECTORDER::NPC);
			Potal_->GetTransform().SetWorldPosition({ 250.F,100.F,-1300.F });
			Potal_->m_PotalType = PotalType::LoginToStage1;

		}



	}





	{
		if (nullptr == Player::GetMainPlayer())
		{
			std::shared_ptr < Player> NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->GetTransform().SetWorldPosition({-600.F,100.F,-150.F});
			NewPlayer->SetLevelOverOn();
			NewPlayer->UIOff();
			NewPlayer->m_bLogoLevelCheck = true;
		}
		else
		{
			Player::GetMainPlayer()->GetTransform().SetWorldPosition({ -600.F,100.F,-150.F });
		}
	}

}

void LoginLevel::Update(float _DeltaTime)
{
	//float4 MyPos = GetMainCameraActorTransform().GetWorldPosition();

	//std::string A2 = std::to_string(MyPos.x);
	//std::string B2 = std::to_string(MyPos.y);
	//std::string C2 = std::to_string(MyPos.z);

	//A2 += " : PX";
	//B2 += " : PY";
	//C2 += " : PZ";

	//GameEngineDebug::OutPutString(A2);
	//GameEngineDebug::OutPutString(B2);
	//GameEngineDebug::OutPutString(C2);


	//MyPos = GetMainCameraActorTransform().GetLocalRotation();

	//std::string A1 = std::to_string(MyPos.x);
	//std::string B1 = std::to_string(MyPos.y);
	//std::string C1 = std::to_string(MyPos.z);

	//A1 += " : LX";
	//B1 += " : LY";
	//C1 += " : LZ";

	//GameEngineDebug::OutPutString(A1);
	//GameEngineDebug::OutPutString(B1);
	//GameEngineDebug::OutPutString(C1);

}

void LoginLevel::End()
{
}
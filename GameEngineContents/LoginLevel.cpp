#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include "Player.h"
#include "TestActor.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include "UIMouse.h"

#include "ShopNPC.h"

LoginLevel::LoginLevel()	:
	UI(nullptr)
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
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
		UIMouse* m_UIMouse = CreateActor<UIMouse>(OBJECTORDER::MouseUI);
		m_UIMouse->SetLevelOverOn();
	}



	
}

void LoginLevel::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		DirectPathAt("00_LoginLevel");
		LoadFBXFiles();

		// 애니메이션 액터의 매시 로드
		// 스태틱 매시 로드
		// 애니메이션 액터의 애니메이션 로드


		/* 초기 멀티스레드 로딩 코드
		GameEngineCore::EngineThreadPool.Work(
			[this]
			{
				this->LoadTextureInStatic();
			});

		GameEngineCore::EngineThreadPool.Work(
			[this]
			{
				this->LoadTextureInAnimator();
			});
		*/
		CreateActor<TestActor>(); // Test Code.
		mbPrimitiveInitialized = true;
	}
#pragma endregion

	if (nullptr == UI)
	{
			{
				UI = CreateActor<LoginUI>(GameObjectGroup::UI);
				UI->CreateComponent<GameEngineCollision>();

				ShopNPC* cShopNPC = CreateActor<ShopNPC>(OBJECTORDER::NPC);
				cShopNPC->GetTransform().SetWorldPosition({ -300.F,0.F,500.F });
				//	cShopNPC->GetTransform().SetWorl

			}

	}





	{
		if (nullptr == Player::GetMainPlayer())
		{
			Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->GetTransform().SetWorldPosition({-600.F,100.F,-150.F});
			NewPlayer->SetLevelOverOn();
			NewPlayer->UIOff();
			NewPlayer->m_bLogoLevelCheck = true;


		}
	}

}

void LoginLevel::Update(float _DeltaTime)
{
	GameEngineDebug::OutPutString(std::to_string(muFBXFolderCount));


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
#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include "Player.h"
#include "TestActor.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include "UIMouse.h"

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
	GetMainCameraActorTransform().SetWorldRotation({ 25.f,0.f,0.f });
	float4 CameraWorldPos = GetMainCameraActorTransform().GetWorldPosition();
	CameraWorldPos.y += 700.f;
	CameraWorldPos.z -= 1200.f;;
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
	DirectPathAt("01_HuntingLevel1");
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
#pragma endregion

	CreateActor<TestActor>(); // Test Code.

	if (nullptr == UI)
	{
	


		UI = CreateActor<LoginUI>(GameObjectGroup::UI);
		UI->CreateComponent<GameEngineCollision>();


	}


	/*if (nullptr == GameEngineTexture::Find("cutCursor.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("MainUI");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}*/





	{
		if (nullptr == Player::GetMainPlayer())
		{
			Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->GetTransform().SetWorldPosition({1.F,0.F,1.F});
			NewPlayer->SetLevelOverOn();
			NewPlayer->UIOff();
			NewPlayer->m_bLogoLevelCheck = true;


		}
	}

}

void LoginLevel::Update(float _DeltaTime)
{
	GameEngineDebug::OutPutString(std::to_string(muFBXFolderCount));
}

void LoginLevel::End()
{
}
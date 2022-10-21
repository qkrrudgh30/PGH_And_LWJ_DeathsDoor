#include "PreCompile.h"
#include "PlayLevel.h"
#include "GlobalContentsValue.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineCore/GameEngineBlur.h>
#include "Player.h"
#include "Monster.h"
#include "TsetBackGround.h"
#include "StageMainCamera.h"


#include "ShopNPC.h"



#include "UIMouse.h"


PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start() 
{


	int a = 0;
	GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
	float4 CameraWorldPos = GetMainCameraActorTransform().GetWorldPosition();
	//CameraWorldPos.x -= 1700.f;
	CameraWorldPos.y += 1700.f;
	CameraWorldPos.z -= 1700.f;
	GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);


	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}




	// 내가 직접 설정해줘야 합니다.
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);




	{
		UIMouse* m_UIMouse = CreateActor<UIMouse>(OBJECTORDER::MouseUI);
	}



	{
		//TsetBackGround* TestBack = CreateActor<TsetBackGround>(OBJECTORDER::BackGround);
	}

	{
		ShopNPC* cShopNPC = CreateActor<ShopNPC>(OBJECTORDER::NPC);
	//	cShopNPC->GetTransform().SetWorl

	}

	
	

	//{
	//	Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
	//	// actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 100.0f });
	//	actor->GetTransform().SetWorldScale(float4(1.0f, 1.f, 1.0f));
	//}
}

void PlayLevel::LevelStartEvent()
{






	{
		if (nullptr == Player::GetMainPlayer())
		{
			Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->SetLevelOverOn();

	
		}
		else
		{
			Player* NewPlayer = Player::GetMainPlayer();
			NewPlayer->UIOn();

		}
	}
}


void PlayLevel::Update(float _DeltaTime) 
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
void PlayLevel::End() {}

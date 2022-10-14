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

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start() 
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Texture");
	Dir.Move("Test");


	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}


	GameEngineFolderTexture::Load(Dir.GetFullPath());

	// 내가 직접 설정해줘야 합니다.
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);



	{
		StageMainCamera* CameraMain = CreateActor<StageMainCamera>(OBJECTORDER::MainCamera);
		
	}



	{
		TsetBackGround* TestBack = CreateActor<TsetBackGround>(OBJECTORDER::BackGround);
	}


	

	{
		TsetBackGround* TestBack = CreateActor<TsetBackGround>(OBJECTORDER::BackGround);
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

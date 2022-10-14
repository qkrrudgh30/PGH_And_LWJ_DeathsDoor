#include "PreCompile.h"
#include "PlayLevel.h"
#include "GlobalContentsValue.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineInstancing.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineCore/GameEngineBlur.h>
#include "Player.h"
#include "Monster.h"

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

	GameEngineFolderTexture::Load(Dir.GetFullPath());

	// 내가 직접 설정해줘야 합니다.
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	{
		GameEngineInstancing* Inst = GetMainCamera()->GetInstancing("TextureAtlas");

		// <우리구조에서> 인스턴싱은 만들기만해도 내부에서 상수버퍼를 사용하고 있다면
		// 그냥 채워버리는데 문제는? 0으로 채워.
		PixelData* Data = Inst->ShaderResources.GetConstantBufferNewData<PixelData>("PixelData");

		Data->MulColor = float4::ONE;
		// Data->PlusColor = float4::ZERO;
		Data->PlusColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
		Data->Slice.x = 0.0f;
		Data->Slice.y = 0.0f;
		Inst->ShaderResources.SetTexture("Tex", "Test", 0);
		int a = 0;
	}

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
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

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Login");
	}

}
void PlayLevel::End() {}

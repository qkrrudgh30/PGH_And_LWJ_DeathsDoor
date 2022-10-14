#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "YNoiseEffect.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	if (false == GameEngineInput::GetInst()->IsKey("YEffect"))
	{
		GameEngineInput::GetInst()->CreateKey("YEffect", 'T');
	}


	// 줌인 줌아웃도 이녀석으로 할수 있습니다.
	// GetMainCamera()->SetProjectionSize(float4{1920, 1080});

	// 카메라를 먼저 만들어서 세계를 볼 준비를 하고
	//GetMainCameraActor()->GetTransform().SetLocalPosition({0.0f, 0.0f, -100.0f});
	//GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0] 앞을 보고 있다.
	// [0][0][-100][0] 뒤로 물러나서

	// 세상에 보일 오브젝트들을 만들어서
	// [800][0][0][0]
	// [0][400][0][0]
	// [0][0][1][0] 앞을 보고 있다.
	// [0][200][0][0] 뒤로 물러나서

	// Ptr->Death(0.0f);

}

void LoginLevel::LevelStartEvent()
{

	if (nullptr == GameEngineTexture::Find("LoginBackground.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("Login");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}


	//{

	//	if (nullptr == Player::GetMainPlayer())
	//	{
	//		Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	//		NewPlayer->SetLevelOverOn();
	//	}

	//}

	UI = CreateActor<LoginUI>(GameObjectGroup::UI);
	UI->CreateComponent<GameEngineCollision>();

	YEffect = GetMainCamera()->GetCameraRenderTarget()->AddEffect<YNoiseEffect>();
	YEffect->Off();
}

void LoginLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		// ;
		GetMainCameraActor()->FreeCameraModeOnOff();
	}


	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Play");
	}

	if (true == GameEngineInput::GetInst()->IsDown("YEffect"))
	{
		YEffect->On();
	}

	if (nullptr != YEffect->CopyTarget)
	{
		if (nullptr != UI)
		{
			UI->Death();
			UI = nullptr;
		}
	}
}

void LoginLevel::End()
{
}
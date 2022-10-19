#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>


LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{


}

void LoginLevel::LevelStartEvent()
{


	if (nullptr == GameEngineTexture::Find("ClickButton.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Texture");
		Dir.Move("LogoUI");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}


		UI = CreateActor<LoginUI>(GameObjectGroup::UI);
		UI->CreateComponent<GameEngineCollision>();


	}



}

void LoginLevel::Update(float _DeltaTime)
{



}

void LoginLevel::End()
{
}
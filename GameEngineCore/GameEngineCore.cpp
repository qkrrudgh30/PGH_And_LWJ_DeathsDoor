#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineLevel.h"
#include "GameEngineDevice.h"
#include "GameEngineGUI.h"
#include "GameEngineCamera.h"
#include "GameEngineCameraActor.h"
#include "GameEngineCoreDebug.h"

#pragma comment(lib, "GameEngineBase.lib")

GameEngineLevel* GameEngineCore::CurrentLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineThreadPool GameEngineCore::EngineThreadPool;


std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevels;


GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

class GameEngineLevel* GameEngineCore::FindLevel(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevels.find(UpperName);
	if (FindIter == AllLevels.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

bool GameEngineCore::ChangeLevel(const std::string& _Name)
{
	NextLevel = FindLevel(_Name);

	if (nullptr == NextLevel)
	{
		MsgBoxAssert("존재하지 않는 레벨로 바꾸려고 했습니다.");
		return false;
	}

	return true;
}

void GameEngineCore::CoreStart(GameEngineCore* _UserCore)
{
	GameEngineGUI::Initialize();

	// 엔진 리소스는 완성되어야 합니다.
	EngineResourcesInitialize();

	EngineThreadPool.Initialize("GameEngineThread");

	// 
	GameEngineDevice::CreateSwapChain();

	GameEngineDebug::Debug3DInitialize();

// 엔진이 뭔가를 할겁니다.
	// 준비를 먼저하고.
	_UserCore->Start();
}

void GameEngineCore::CoreUpdate(GameEngineCore* _UserCore)
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurrentLevel)
		{
			CurrentLevel->ActorLevelEndEvent();
			CurrentLevel->LevelEndEvent();
			// 넘어가려는 액터가 이때 존재해야 겠죠?

			CurrentLevel->OverChildMove(NextLevel);
		}

		CurrentLevel = NextLevel;
		NextLevel = nullptr;
		CurrentLevel->LevelStartEvent();
		CurrentLevel->ActorLevelStartEvent();

		// ex) 타이틀에서 5초후 => 플레이 레벨로 이동
		//     플레이 레벨에서 => 다시 타이틀레벨로
		CurrentLevel->ReSetAccTime();

		GameEngineTime::GetInst()->Reset();
	}


	if (nullptr == CurrentLevel)
	{
		MsgBoxAssert("레벨을 지정해주지 않으면 엔진을 시작할수가 업습니다.");
	}

	GameEngineSound::Update();
	GameEngineTime::GetInst()->Update();
	float DeltaTime = GameEngineTime::GetDeltaTime();
	GameEngineInput::GetInst()->Update(DeltaTime);

	if (true == GameEngineTime::IsFrameCheck())
	{
		// 엔진수준에서 유저가 하고 싶은일.
		_UserCore->Update(DeltaTime);
		CurrentLevel->LevelUpdate(DeltaTime);
	}

}

void GameEngineCore::CoreEnd(GameEngineCore* _UserCore) 
{
	_UserCore->End();

	for (auto& Level : AllLevels)
	{
		if (nullptr == Level.second)
		{
			continue;
		}
		delete Level.second;
		Level.second = nullptr;
	}

	// 이유는 리소스를 사용할거 같아서
	// gui에서 텍스처라던가 이런거 쓰다가
	GameEngineGUI::GUIDestroy();

	GameEngineDebug::Debug3DDestroy();

	EngineResourcesDestroy();

	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineDebug::Destroy();
	GameEngineTime::Destroy();
}


void GameEngineCore::WindowCreate(const std::string& _Name, GameEngineCore* _UserCore)
{
	GameEngineWindow::GetInst()->CreateGameWindow(nullptr, _Name.c_str());
	GameEngineWindow::GetInst()->SetWindowScaleAndPosition(_UserCore->StartWindowPosition(), _UserCore->StartWindowSize());
	GameEngineWindow::GetInst()->ShowGameWindow();
	GameEngineDevice::Initialize();




	// 엔진의 실행인데.
	GameEngineWindow::GetInst()->MessageLoop(
		std::bind(&GameEngineCore::CoreStart, _UserCore),
		std::bind(&GameEngineCore::CoreUpdate, _UserCore),
		std::bind(&GameEngineCore::CoreEnd, _UserCore)
	);


}

void GameEngineCore::InitializeLevel(GameEngineLevel* _Level, const std::string _Name)
{
	{
		GameEngineCameraActor* actor = _Level->CreateActor<GameEngineCameraActor>();
		actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	}

	{
		GameEngineCameraActor* actor = _Level->CreateActor<GameEngineCameraActor>();
		actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	}

	_Level->Start();
	_Level->SetName(_Name);
	
	// AllLevels.insert(std::map<std::string, GameEngineLevel*>::value_type(_Name, NewLevel));
	AllLevels.insert(std::make_pair(_Name, _Level));
}
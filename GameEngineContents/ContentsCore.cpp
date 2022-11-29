#include "PreCompile.h"
#include "ContentsCore.h"
#include <GameEngineBase/magic_enum.hpp>
#include "GameEngineContents/LoginLevel.h"
#include "GameEngineContents/HuntingLevel1.h"
#include "GameEngineContents/HuntingLevel2.h"
#include "GameEngineContents/HuntingLevel3.h"
#include "GameEngineContents/HuntingLevel4.h"
#include "GameEngineContents/HuntingLevel5.h"
#include "GameEngineContents/BossLevel.h"
#include "GameEngineContents/TestLevel.h"
#include "GameEngineContents/EditLevel.h"
#include "GameEngineContents/EditGUIWindow.h"
#include "GameEngineStatusWindow.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineTime::SetLimitFrame(-1);

	InitializeContentsResource();

#pragma region CreateContentsLevel
	CreateLevel<LoginLevel>("00_LoginLevel");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("00_LOGINLEVEL", false));
	CreateLevel<HuntingLevel1>("01_HuntingLevel1");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("01_HUNTINGLEVEL1", false));
	CreateLevel<HuntingLevel2>("02_HuntingLevel2");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("02_HUNTINGLEVELl2", false));
	CreateLevel<HuntingLevel3>("03_HuntingLevel3");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("03_HUNTINGLEVEL3", false));
	CreateLevel<HuntingLevel4>("04_HuntingLevel4");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("04_HUNTINGLEVEL4", false));
	CreateLevel<HuntingLevel5>("05_HuntingLevel5");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("05_HUNTINGLEVEL5", false));
	CreateLevel<BossLevel>("06_BossLevel");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("06_BOSSLEVEL", false));
	CreateLevel<EditLevel>("07_EditLevel");
	CreateLevel<TestLevel>("08_TestLevel");

	ChangeLevel("07_EditLevel");
	ContentsLevel::mstrNextLevelName = "00_LOGINLEVEL";
#pragma endregion

#pragma region CreateContentsGUI

// #ifdef _DEBUG
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
	GameEngineGUI::CreateGUIWindow<EditGUIWindow>("EditGUIWindow", nullptr);
// #endif

#pragma endregion

}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
	DestroyContentsResource();
}
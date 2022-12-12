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
#include "ContentsLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

int ContentsCore::m_nCurrentLevel = -1;
int ContentsCore::m_nNextLevel = -1;

enum
{
	LOGIN_LEVEL = 0,
	HUNTING_LEVEL1 = 1,
	HUNTING_LEVEL2 = 2,
	HUNTING_LEVEL3 = 3,
	HUNTING_LEVEL4 = 4,
	HUNTING_LEVEL5 = 5,
	BOSS_LEVEL = 6,
	EDIT_LEVEL = 7,
	TEST_LEVEL = 8,
	NONE = -1
};

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
	if (nullptr != GEngine::GetCurrentLevel())
	{
		ChangeLevelNumber();

		/*
		00_LoginLevelBGM.mp3
		01_HuntingLevelBGM.mp3
		19_MiddleBossLevelBGM.mp3
		26_LastBossLevelBGM.mp3
		*/

		if (m_nCurrentLevel != m_nNextLevel)
		{
			if (LOGIN_LEVEL == m_nNextLevel)
			{
				mstructSoundPlayer.Stop();
				mstructSoundPlayer = GameEngineSound::SoundPlayControl("00_LoginLevelBGM.mp3", 10);
				mstructSoundPlayer.Volume(0.3f);
			}

			if (HUNTING_LEVEL1 == m_nNextLevel || HUNTING_LEVEL2 == m_nNextLevel || 
				HUNTING_LEVEL3 == m_nNextLevel || HUNTING_LEVEL2 == m_nNextLevel )
			{
				mstructSoundPlayer.Stop();
				mstructSoundPlayer = GameEngineSound::SoundPlayControl("01_HuntingLevelBGM.mp3", 10);
				mstructSoundPlayer.Volume(2.f);
			}

			if (HUNTING_LEVEL5 == m_nNextLevel)
			{
				mstructSoundPlayer.Stop();
				mstructSoundPlayer = GameEngineSound::SoundPlayControl("19_MiddleBossLevelBGM.mp3", 10);
				mstructSoundPlayer.Volume(0.3f);
			}

			if (BOSS_LEVEL == m_nNextLevel)
			{
				mstructSoundPlayer.Stop();
				mstructSoundPlayer = GameEngineSound::SoundPlayControl("26_LastBossLevelBGM.mp3", 10);
				mstructSoundPlayer.Volume(0.6f);
			}

			m_nCurrentLevel = m_nNextLevel;
		}

	}
}

void ContentsCore::ChangeLevelNumber()
{
	if (GameEngineString::ToUpperReturn("00_LoginLevel")		 == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = LOGIN_LEVEL; }
	else if (GameEngineString::ToUpperReturn("01_HuntingLevel1") == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = HUNTING_LEVEL1; }
	else if (GameEngineString::ToUpperReturn("02_HuntingLevel2") == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = HUNTING_LEVEL2; }
	else if (GameEngineString::ToUpperReturn("03_HuntingLevel3") == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = HUNTING_LEVEL3; }
	else if (GameEngineString::ToUpperReturn("04_HuntingLevel4") == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = HUNTING_LEVEL4; }
	else if (GameEngineString::ToUpperReturn("05_HuntingLevel5") == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = HUNTING_LEVEL5; }
	else if (GameEngineString::ToUpperReturn("06_BossLevel")     == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = BOSS_LEVEL; }
	else if (GameEngineString::ToUpperReturn("07_EditLevel")     == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = EDIT_LEVEL; }
	else if (GameEngineString::ToUpperReturn("08_TestLevel")     == GEngine::GetCurrentLevel()->GetNameCopy()) { m_nNextLevel = TEST_LEVEL; }
}

void ContentsCore::End()
{
	DestroyContentsResource();
}
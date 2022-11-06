#include "PreCompile.h"
#include "ContentsCore.h"
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



#include <GameEngineBase/magic_enum.hpp>


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
	std::string_view Value = magic_enum::enum_name(OBJECTORDER::Player);
	std::string Name = Value.data();

	{   // 파란색, 디버그 충돌체 3dbox, getworld
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Asset");

		// std::vector<GameEngineDirectory> DirList = Dir.GetRecursiveAllDirectory();

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Asset");
		Dir.Move("GlobalUI");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}


	}


	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("ContentsResources");
		Dir.Move("Shader");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
		}
	}

	//{
	//	GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("YEffect");
	//	NewPipe->SetInputAssembler1VertexBuffer("FullRect");
	//	NewPipe->SetInputAssembler2IndexBuffer("FullRect");
	//	NewPipe->SetVertexShader("YEffect.hlsl");
	//	NewPipe->SetPixelShader("YEffect.hlsl");
	//}

	if (false == GameEngineInput::GetInst()->IsKey("LevelChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChangeKey", 'P');
	}

	// RTTI 런 타임 타입 인포메이션
	CreateLevel<LoginLevel>("00_LoginLevel");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("00_LoginLevel", false));
	CreateLevel<HuntingLevel1>("01_HuntingLevel1");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("01_HuntingLevel1", false));
	CreateLevel<HuntingLevel2>("02_HuntingLevel2");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("02_HuntingLevel2", false));
	CreateLevel<HuntingLevel3>("03_HuntingLevel3");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("03_HuntingLevel3", false));
	CreateLevel<HuntingLevel4>("04_HuntingLevel4");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("04_HuntingLevel4", false));
	CreateLevel<HuntingLevel5>("05_HuntingLevel5");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("05_HuntingLevel5", false));
	CreateLevel<BossLevel>("06_BossLevel");
	ContentsLevel::mmapPrimitiveInitialized.insert(std::make_pair("06_BossLevel", false));
	CreateLevel<EditLevel>("07_EditLevel");
	CreateLevel<TestLevel>("08_TestLevel");



	ChangeLevel("07_EditLevel");
	ContentsLevel::mstrNextLevelName = "00_LoginLevel";

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
	GameEngineGUI::CreateGUIWindow<EditGUIWindow>("EditGUIWindow", nullptr);

}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}
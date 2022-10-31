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
		Dir.Move("Texture");

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
		Dir.Move("Texture");
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
	CreateLevel<LoginLevel>("Login");
	CreateLevel<HuntingLevel1>("Hunting1");
	CreateLevel<HuntingLevel2>("Hunting2");
	CreateLevel<HuntingLevel3>("Hunting3");
	CreateLevel<HuntingLevel4>("Hunting4");
	CreateLevel<HuntingLevel5>("Hunting5");
	CreateLevel<BossLevel>("Boss");
	CreateLevel<TestLevel>("Test");
	CreateLevel<EditLevel>("Edit");
	ChangeLevel("Login");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
	GameEngineGUI::CreateGUIWindow<EditGUIWindow>("EditGUIWindow", nullptr);

}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}
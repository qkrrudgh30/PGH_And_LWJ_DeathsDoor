#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/LoginLevel.h"
#include "GameEngineContents/PlayLevel.h"
#include "GameEngineContents/MapEditorLevel.h"
#include "MetaLevel.h"

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

	GameEngineTime::SetLimitFrame(60);
	std::string_view Value = magic_enum::enum_name(OBJECTORDER::Player);
	std::string Name = Value.data();

	{
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
	CreateLevel<PlayLevel>("Play");
	CreateLevel<MapEditorLevel>("MapEditor");
	CreateLevel<MetaLevel>("MetaEditor");
	ChangeLevel("Login");
	
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}
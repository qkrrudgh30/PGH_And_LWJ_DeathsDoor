#include "PreCompile.h"
#include "GameEngineFolderTexture.h"
#include <GameEngineBase/GameEnginePath.h>

GameEngineFolderTexture::GameEngineFolderTexture() 
{
}

GameEngineFolderTexture::~GameEngineFolderTexture() 
{
	Textures.clear();
	//for (size_t i = 0; i < Textures.size(); i++)
	//{
	//	delete Textures[i];
	//}
}


std::shared_ptr < GameEngineFolderTexture> GameEngineFolderTexture::Load(const std::string& _Path)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path));
}

std::shared_ptr < GameEngineFolderTexture> GameEngineFolderTexture::Load(const std::string& _Path, const std::string& _Name)
{
	std::shared_ptr < GameEngineFolderTexture> NewTex = CreateResName(_Name);
	NewTex->LoadFolder(_Path);
	return NewTex;
}

void GameEngineFolderTexture::LoadFolder(const std::string& _Path)
{
	GameEngineDirectory Dir = GameEngineDirectory(_Path);

	//GameEngineDirectory Dir = _Path;

	//GameEngineDirectory Dir = { _Path };

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = std::make_shared<GameEngineTexture>();
		NewTexture->TextureLoad(AllFile[i].GetFullPath());
		Textures.push_back(NewTexture);
	}



	int a = 0;
}
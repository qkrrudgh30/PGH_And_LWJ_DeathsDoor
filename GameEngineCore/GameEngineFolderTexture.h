#pragma once
#include "GameEngineTexture.h"

// 설명 :
class GameEngineFolderTexture : public GameEngineRes<GameEngineFolderTexture>
{
public:
	// constrcuter destructer
	GameEngineFolderTexture();
	~GameEngineFolderTexture();

	// delete Function
	GameEngineFolderTexture(const GameEngineFolderTexture& _Other) = delete;
	GameEngineFolderTexture(GameEngineFolderTexture&& _Other) noexcept = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture& _Other) = delete;
	GameEngineFolderTexture& operator=(GameEngineFolderTexture&& _Other) noexcept = delete;

	static std::shared_ptr < GameEngineFolderTexture> Load(const std::string& _Path);

	static std::shared_ptr < GameEngineFolderTexture> Load(const std::string& _Path, const std::string& _Name);

	size_t GetTextureCount() 
	{
		return Textures.size();
	}

	std::shared_ptr<GameEngineTexture> GetTexture(size_t _Index)
	{
		if (Textures.size() <= _Index)
		{
			MsgBoxAssert("폴더 텍스처 참조범위를 넘겼습니다.");
		}

		return Textures[_Index];
	}

protected:
	void LoadFolder(const std::string& _Path);

private:
	std::vector<std::shared_ptr < GameEngineTexture>> Textures;
};


#include "PreCompile.h"
#include "GameEnginePath.h"
#include <GameEngineBase/GameEngineString.h>

GameEnginePath::GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path) 
	: Path_(_Path)
{

}

GameEnginePath::~GameEnginePath() 
{
}

void GameEnginePath::SetCurrentPath() 
{
	// 현재 폴더.
	Path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExits() 
{
	return std::filesystem::exists(Path_);
}

bool GameEnginePath::ChangeExtension(const std::string_view& _Extension)
{
	std::string Path = Path_.string();

	// GameEngineString::ToUpper(Path);

	Path = GameEngineString::Replace(Path, GetExtension(), _Extension);

	if (Path == Path_.string())
	{
		return false;
	}

	Path_ = Path;

	return true;
}

std::string GameEnginePath::GetExtension() const
{
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()  const
{
	return Path_.filename().string();
}

std::string GameEnginePath::GetExtension(const std::string& _Path)
{
	std::filesystem::path Path_ = _Path;
	return Path_.extension().string();
}

/*static*/ std::string GameEnginePath::GetFileName(const std::string& _Path)
{
	std::filesystem::path Path_ = _Path;
	return Path_.filename().string();
}

std::string GameEnginePath::GetFolderPath(const std::string& _Path)
{
	std::string FileName = GetFileName(_Path);
	std::string FullPath = _Path;

	FullPath = FullPath.replace(FullPath.size() - FileName.size(), FileName.size(), "");
	return FullPath;
}

std::string GameEnginePath::GetFullPath() const
{
	return Path_.string();
}

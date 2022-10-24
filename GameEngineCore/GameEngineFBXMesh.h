#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>

// Ό³Έν :
class GameEngineFBXMesh : public GameEngineFBX, public GameEngineRes<GameEngineFBXMesh>
{
public:
	// constrcuter destructer
	GameEngineFBXMesh();
	~GameEngineFBXMesh();

	// delete Function
	GameEngineFBXMesh(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _Other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh& operator=(GameEngineFBXMesh&& _Other) noexcept = delete;

	static GameEngineFBXMesh* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineFBXMesh* Load(const std::string& _Path, const std::string& _Name);


protected:

private:

};


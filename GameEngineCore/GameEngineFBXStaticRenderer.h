#pragma once
#include "GameEngineFBXRenderer.h"

// Ό³Έν :
class GameEngineFBXStaticRenderer : public GameEngineFBXRenderer
{
public:
	// constrcuter destructer
	GameEngineFBXStaticRenderer();
	~GameEngineFBXStaticRenderer();

	// delete Function
	GameEngineFBXStaticRenderer(const GameEngineFBXStaticRenderer& _Other) = delete;
	GameEngineFBXStaticRenderer(GameEngineFBXStaticRenderer&& _Other) noexcept = delete;
	GameEngineFBXStaticRenderer& operator=(const GameEngineFBXStaticRenderer& _Other) = delete;
	GameEngineFBXStaticRenderer& operator=(GameEngineFBXStaticRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _Name, std::string _Material) override;
	void SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex, size_t _SubSetIndex = 0) override;


protected:

private:
	void Render(float _DeltaTime) override;

};


#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineFBXMesh.h"

// Ό³Έν :
class GameEngineFBXRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	virtual ~GameEngineFBXRenderer() = 0;

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	virtual void SetFBXMesh(const std::string& _Name, std::string _Material);
	virtual GameEngineRenderUnit* SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex, size_t _SubSetIndex = 0);

	void Render(float _DeltaTime) override;

	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

	inline GameEngineFBXMesh* GetFBXMesh() 
	{
		return FBXMesh;
	}

protected:

private:
	GameEngineFBXMesh* FBXMesh;
	std::vector<std::vector<GameEngineRenderUnit>> Unit;

};


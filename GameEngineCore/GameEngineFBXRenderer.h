#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineFBXMesh.h"

// 설명 :
class GameEngineFBXRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	~GameEngineFBXRenderer();

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _Name, std::string _PipeLine);
	void SetFBXMesh(const std::string& _Name, std::string _PipeLine, size_t MeshIndex, size_t _SubSetIndex = 0);

	void Render(float _DeltaTime) override;

	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

protected:
	


private:
	GameEngineFBXMesh* FBXMesh;

	// 대검 
	// 사람          
	std::vector<std::vector<GameEngineRenderUnit>> Unit;

};


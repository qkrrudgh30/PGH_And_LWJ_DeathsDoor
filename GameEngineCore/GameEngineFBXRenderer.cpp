#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"

GameEngineFBXRenderer::GameEngineFBXRenderer() 
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer() 
{
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _PipeLine)
{
	// 너 몇개 가지고 있어.
	for (size_t i = 0; i < 2; i++)
	{
		SetFBXMesh(_Name, _PipeLine, i);
	}
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _PipeLine, int Index, int _SubSetIndex /*= 0*/)
{
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
		// 지금까지 만든거 다 날립니다.
	}

	GameEngineRenderUnit& RenderUnit = Unit.emplace_back();

	GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(Index);

	// RenderUnit.SetMesh();

}

void GameEngineFBXRenderer::Render(float _DeltaTime) 
{
	int a = 0;
}
#include "PreCompile.h"
#include "GameEngineFBXStaticRenderer.h"
#include "GameEngineVertexShader.h"

GameEngineFBXStaticRenderer::GameEngineFBXStaticRenderer() 
{
}

GameEngineFBXStaticRenderer::~GameEngineFBXStaticRenderer() 
{
}

void GameEngineFBXStaticRenderer::SetFBXMesh(const std::string& _Name, std::string _Material) 
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (true == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("스태틱 매쉬 랜더러는 애니메이션을 할수 없습니다. 머티리얼 내부에 ArrAniMationMatrix를 사용하고 있습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_Name, _Material);
}

GameEngineRenderUnit* GameEngineFBXStaticRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex /*= 0*/)
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return nullptr;
	}

	if (true == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("스태틱 매쉬 랜더러는 애니메이션을 할수 없습니다. 머티리얼 내부에 ArrAniMationMatrix를 사용하고 있습니다.");
		return nullptr;
	}

	return GameEngineFBXRenderer::SetFBXMesh(_Name, _Material, _MeshIndex, _SubSetIndex);
}

void GameEngineFBXStaticRenderer::Render(float _DeltaTime) 
{
	GameEngineFBXRenderer::Render(_DeltaTime);
}
#include "PreCompile.h"
#include "GameEngineRenderSet.h"

GameEngineRenderSet::GameEngineRenderSet() 
{
}

GameEngineRenderSet::~GameEngineRenderSet() 
{
}


void GameEngineRenderSet::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("존재하지 않는 파이프라인을 세팅하려고 했습니다.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);

	//if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	//{
	//	ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	//}

	//if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	//{
	//	ShaderResources.SetConstantBufferLink("RENDEROPTION", &Option, sizeof(Option));
	//}

}

void GameEngineRenderSet::Render()
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할수 없습니다.");
	}

	// 준비된 모든 리소스들을 다 세팅해준다.
	ShaderResources.AllResourcesSetting();
	PipeLine->Rendering();
	ShaderResources.AllResourcesReset();
}

GameEngineRenderingPipeLine* GameEngineRenderSet::GetPipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	GameEngineRenderingPipeLine* Clone = GameEngineRenderingPipeLine::Create();
	Clone->Copy(PipeLine);
	PipeLine = Clone;
	return PipeLine;
}
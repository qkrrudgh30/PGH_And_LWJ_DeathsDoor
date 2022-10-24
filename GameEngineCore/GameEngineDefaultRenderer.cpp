#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();

	// 뭔가 또 할일이 있다면 여기서 해라.
}

void GameEngineDefaultRenderer::SetMesh(const std::string& _Name)
{
	Unit.SetMesh(_Name);
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _Name)
{
	Unit.SetPipeLine(_Name);
	Unit.SetRenderer(this);
	PushRendererToMainCamera();
}

void GameEngineDefaultRenderer::Render(float _DeltaTime) 
{
	Unit.Render(_DeltaTime);

	//if (nullptr == PipeLine)
	//{
	//	MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할수 없습니다.");
	//}

	//if (false == IsInstancing(GetPipeLine()))
	//{
	//	// 준비된 모든 리소스들을 다 세팅해준다.
	//	ShaderResources.AllResourcesSetting();
	//	PipeLine->Rendering();
	//	ShaderResources.AllResourcesReset();
	//}
	//else 
	//{
	//	InstancingDataSetting(GetPipeLine());
	//	// 여러분들이 새로운 랜더러를 만들고 인스턴싱을 하면
	//	// 이 부분이 달라져야 합니다.
	//	// 유저가 몇바이트짜리 인스턴
	//	// Camera->PushInstancingIndex(PipeLine);
	//}
}

void GameEngineDefaultRenderer::InstancingOn()
{
	GameEngineRenderer::InstancingOn();

	// Camera->PushInstancing(PipeLine, 1);
}
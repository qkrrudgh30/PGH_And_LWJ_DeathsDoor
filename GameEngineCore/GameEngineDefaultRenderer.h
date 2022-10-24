#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

// 설명 :
class GameEngineMaterial;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
	// 하나의 랜더링 파이프라인은
	// 하나의 매쉬
	// 하나의 메테리얼

	// 하나의 랜더타겟


public:

	// GameEngineShaderResourcesHelper ShaderResources;

	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

	// delete Function
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);


	void SetMesh(const std::string& _Name);
	void SetPipeLine(const std::string& _Name);

	virtual void InstancingOn();

	inline GameEngineShaderResourcesHelper& GetShaderResources()
	{
		return Unit.ShaderResources;
	}

	inline GameEngineRenderUnit& GetRenderUnit()
	{
		return Unit;
	}

protected:

	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	GameEngineRenderUnit Unit;

	// 공통적인 메모리 공유하는 메로리들을 들고 있고
	// GameEngineMaterial* PipeLine;


};


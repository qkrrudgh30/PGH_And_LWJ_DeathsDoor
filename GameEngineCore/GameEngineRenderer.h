#pragma once
#include "GameEngineCamera.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineMesh.h"

struct RenderOption 
{
    float DeltaTime = 0.0f;
    float SumDeltaTime = 0.0f;
	int Temp0;
	int Temp1;
};

// 랜더타겟이 세팅되어 있다면 이녀석으로 그릴수가 있다.

class GameEngineRenderUnit 
{
public:
	GameEngineRenderUnit();

	void SetMesh(const std::string& _Name);

	void SetPipeLine(const std::string& _Name);

	// 우리 엔진에서는 이런 이름을 가진x는 무조건 이렇게 세팅하기로 했어.
	void EngineShaderResourcesSetting(GameEngineRenderer* _Renderer);

	void Render(float _DeltaTime);

	void SetRenderer(GameEngineRenderer* _Renderer);

	GameEngineRenderingPipeLine* GetPipeLine();

	GameEngineRenderingPipeLine* GetClonePipeLine();

	GameEngineRenderingPipeLine* ClonePipeLine(GameEngineRenderingPipeLine* _Rendering);

	GameEngineShaderResourcesHelper ShaderResources;

private:
	GameEngineRenderer* ParentRenderer;
	GameEngineMesh* Mesh; // 이 메쉬를
	GameEngineRenderingPipeLine* PipeLine; // 이 설정으로
	GameEngineInputLayOut* InputLayOut; // 인풋어셈블러1 세팅
	// 	GameEngineShaderResourcesHelper ShaderResources; // 이 데이터를 가지고
	D3D11_PRIMITIVE_TOPOLOGY Topology;// 이렇게 그린다.
};


// 추상클래스
// 강제 내 자식들을 하나의 인터페이스로 묶는 역할입니다.
// 설명 :
class GameEngineRenderingPipeLine;
class GameEngineShaderResourcesHelper;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;


public:
	RenderOption renderOption;

	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// float4x4 ViewPort;
	void ChangeCamera(CAMERAORDER _Order);

    GameEngineRenderingPipeLine* ClonePipeLine(GameEngineRenderingPipeLine* _Rendering);

    inline int GetRenderingOrder() 
    {
        return RenderingOrder;
    }

    void SetRenderingOrder(int _Order);

	virtual void InstancingOn() 
	{
		IsInstancing_ = true;
	};

	bool IsInstancing(GameEngineRenderingPipeLine* _Rendering);

	void InstancingDataSetting(GameEngineRenderingPipeLine* _Line);

	void EngineShaderResourcesSetting(GameEngineShaderResourcesHelper* _ShaderResources);

	void PushRendererToMainCamera();

	void PushRendererToUICamera();
	
protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

    class GameEngineCamera* Camera;



private:
	CAMERAORDER CameraOrder;
    int RenderingOrder;
	bool IsInstancing_;

	virtual void Render(float _DeltaTime) = 0;

};


#pragma once
#include "GameEngineCamera.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineMesh.h"
#include "ShaderStruct.h"


// 추상클래스
// 강제 내 자식들을 하나의 인터페이스로 묶는 역할입니다.
// 설명 :
class GameEngineMaterial;
class GameEngineShaderResourcesHelper;
class GameEngineRenderer 
	: public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;


public:
	RenderOption RenderOptionInst;

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

    inline int GetRenderingOrder() 
    {
        return RenderingOrder;
    }

    void SetRenderingOrder(int _Order);

	virtual void InstancingOn() 
	{
		IsInstancing_ = true;
	};

	GameEngineCamera* GetCamera()
	{
		return Camera;
	}

	void PushRendererToMainCamera();

	void PushRendererToUICamera();

	std::shared_ptr<GameEngineRenderUnit> CreateRenderUnit();

	std::list<std::shared_ptr<GameEngineRenderUnit>>& GetUnits()
	{
		return Units;
	}

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

    class GameEngineCamera* Camera;



private:
	std::list<std::shared_ptr<GameEngineRenderUnit>> Units;

	CAMERAORDER CameraOrder;
    int RenderingOrder;
	bool IsInstancing_;

	virtual void Render(float _DeltaTime) = 0;

};




// 랜더타겟이 세팅되어 있다면 이녀석으로 그릴수가 있다.

class GameEngineRenderUnit
	: public std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	GameEngineRenderUnit();

	GameEngineRenderUnit(const GameEngineRenderUnit& _Render);

	inline bool GetIsOn()
	{
		if (nullptr == ParentRenderer)
		{
			MsgBoxAssert("랜더러가 세팅되지 않았습니다.");
		}

		return IsOn && ParentRenderer->IsUpdate();
	}

	inline bool IsDeath()
	{
		if (nullptr == ParentRenderer)
		{
			MsgBoxAssert("랜더러가 세팅되지 않았습니다.");
		}

		return ParentRenderer->IsDeath();
	}

	inline int Order()
	{
		if (nullptr == ParentRenderer)
		{
			MsgBoxAssert("랜더러가 세팅되지 않았습니다.");
		}

		return ParentRenderer->GetOrder();
	}

	inline void On()
	{
		IsOn = true;
	}

	inline void Off()
	{
		IsOn = false;
	}

	inline GameEngineRenderer* GetRenderer()
	{
		return ParentRenderer;
	}

	void SetMesh(const std::string& _Name);

	void SetMesh(std::shared_ptr<GameEngineMesh> _Mesh);

	void PushCamera();

	void SetMaterial(const std::string& _Name);

	// 우리 엔진에서는 이런 이름을 가진x는 무조건 이렇게 세팅하기로 했어.
	void EngineShaderResourcesSetting(GameEngineRenderer* _Renderer);

	void Render(float _DeltaTime);

	void SetRenderer(GameEngineRenderer* _Renderer);

	void RenderInstancing(float _DeltaTime, size_t _RanderingCount, std::shared_ptr<GameEngineInstancingBuffer> _Buffer);

	std::shared_ptr < GameEngineMesh> GetMesh();

	std::shared_ptr < GameEngineMaterial> GetMaterial();

	std::shared_ptr < GameEngineMaterial> GetCloneMaterial();

	std::shared_ptr < GameEngineMaterial> CloneMaterial(std::shared_ptr<GameEngineMaterial> _Rendering);

	GameEngineShaderResourcesHelper ShaderResources;

	std::function<bool(float)> RenderFunction;

	RENDERINGPATHORDER GetPath()
	{
		return Path;
	}

	void SetPath(RENDERINGPATHORDER _Path)
	{
		Path = _Path;
	}

private:
	bool IsOn;
	RENDERINGPATHORDER Path;

	GameEngineRenderer* ParentRenderer;
	std::shared_ptr < GameEngineMesh> Mesh; // 이 메쉬를
	std::shared_ptr < GameEngineMaterial> Material; // 이 설정으로
	std::shared_ptr < GameEngineInputLayOut> InputLayOut; // 인풋어셈블러1 세팅
	D3D11_PRIMITIVE_TOPOLOGY Topology;// 이렇게 그린다.

};

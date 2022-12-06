#pragma once
#include "GameEngineTransformComponent.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineInstancingBuffer.h"
#include <set>

enum class CAMERAPROJECTIONMODE
{
	PersPective,
	Orthographic,
};


// 설명 :
class GameEngineLight;
class GameEngineLevel;
class GameEngineCamera;
class GameEngineInstancing;
class GameEngineRenderTarget;
class GameEngineMaterial;
class GameEngineCamera : public GameEngineTransformComponent
{
	friend GameEngineLevel;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	inline CAMERAPROJECTIONMODE GetProjectionMode()
	{
		return Mode;
	}

	inline std::shared_ptr < GameEngineRenderTarget> GetCameraRenderTarget()
	{
		return CameraRenderTarget;
	}

	void SetCameraOrder(CAMERAORDER _Order);

	inline void SetProjectionMode(CAMERAPROJECTIONMODE _Mode)
	{
		Mode = _Mode;
	}

	// 왼쪽 위가 0,0
	float4 GetMouseScreenPosition();

	float4 GetMouseWorldPosition();

	float4 GetMouseWorldPositionToActor();

	inline float4x4 GetView() 
	{
		return View;
	}
	inline float4x4 GetProjectionMatrix()
	{
		return Projection;
	}

	inline float4 GetMouseWorldDir()
	{
		return MouseDir;
	}

	inline void SetProjectionSize(const float4& _Value) 
	{
		Size = _Value;
		// return float4();
	}

	inline float4 GetProjectionSize()
	{
		return Size;
	}

	//                  개수
	GameEngineInstancing& GetInstancing(const std::string& _Name);
	//void PushInstancing(std::shared_ptr < GameEngineMaterial> _Pipe, int Count);
	//int PushInstancingData(std::shared_ptr < GameEngineMaterial> _Pipe, void* _DataPtr, int _Size);
	//int PushInstancingIndex(std::shared_ptr < GameEngineMaterial> _Pipe);

	float4 GetWorldPositionToScreenPosition(const float4& _Pos);

	void PushLight(std::shared_ptr<class GameEngineLight> _Light);

protected:
	void Start();

	void ChangeRenderingOrder(std::shared_ptr < GameEngineRenderer> _Renderer, int _ChangeOrder);


private:
	void Render(float _DeltaTime);

	void PushRenderer(std::shared_ptr < GameEngineRenderer> _Renderer);

	void Release(float _DelataTime);

	void Update(float _DeltaTime) override;

	void OverRenderer(std::shared_ptr<GameEngineCamera> _NextOver);

	std::shared_ptr<class GameEngineRenderTarget> CameraRenderTarget;

	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> AllRenderer_;

	std::unordered_map<std::string, GameEngineInstancing> InstancingMap;

	std::set<std::shared_ptr<class GameEngineLight>> AllLight;

	// std::list<GameEngineLight>

	float4x4 View; // 바라보는것
	float4x4 Projection;
	float4x4 ViewPort;
	CAMERAPROJECTIONMODE Mode;

	float4 PrevMouse;
	float4 MouseDir;

	D3D11_VIEWPORT ViewPortDesc;

	// Projection Data
	float4 Size;
	float Near;
	float Far;

	// Perspective
	float Fov;
};


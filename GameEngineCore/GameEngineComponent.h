#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"

// Ό³Έν :
class GameEngineComponent :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	void SetParent(GameEngineUpdateObject*) override;

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}
};


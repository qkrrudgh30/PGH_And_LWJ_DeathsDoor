
#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :

class UIMouse : public GameEngineActor
{
public:
	// constrcuter destructer
	UIMouse();
	~UIMouse();

	// delete Function
	UIMouse(const UIMouse& _Other) = delete;
	UIMouse(UIMouse&& _Other) noexcept = delete;
	UIMouse& operator=(const UIMouse& _Other) = delete;
	UIMouse& operator=(UIMouse&& _Other) noexcept = delete;
public:

	bool UnitCol;

	float4 UnitPos;
	std::shared_ptr < GameEngineUIRenderer> Renderer;
	std::shared_ptr < GameEngineCollision>  Collision;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:

};



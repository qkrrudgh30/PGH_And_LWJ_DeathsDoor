#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MouseSlot : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseSlot();
	~MouseSlot();

	// delete Function
	MouseSlot(const MouseSlot& _Other) = delete;
	MouseSlot(MouseSlot&& _Other) noexcept = delete;
	MouseSlot& operator=(const MouseSlot& _Other) = delete;
	MouseSlot& operator=(MouseSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<GameEngineUIRenderer> mpRenderer;

};


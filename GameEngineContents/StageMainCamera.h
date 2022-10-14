#pragma once

// Ό³Έν :
class StageMainCamera : public GameEngineActor
{
public:
	// constrcuter destructer
	StageMainCamera();
	~StageMainCamera();

	// delete Function
	StageMainCamera(const StageMainCamera& _Other) = delete;
	StageMainCamera(StageMainCamera&& _Other) noexcept = delete;
	StageMainCamera& operator=(const StageMainCamera& _Other) = delete;
	StageMainCamera& operator=(StageMainCamera&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

public:
	Player* m_Player;
};


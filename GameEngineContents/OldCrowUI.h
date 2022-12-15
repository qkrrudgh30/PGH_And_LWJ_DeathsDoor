

#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class OldCrowUI : public GameEngineActor
{
public:
	// constrcuter destructer
	OldCrowUI();
	~OldCrowUI();

	// delete Function
	OldCrowUI(const OldCrowUI& _Other) = delete;
	OldCrowUI(OldCrowUI&& _Other) noexcept = delete;
	OldCrowUI& operator=(const OldCrowUI& _Other) = delete;
	OldCrowUI& operator=(OldCrowUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr <GameEngineUIRenderer> RendererButton1;
	std::shared_ptr <GameEngineUIRenderer> RendererButton2;


public:

	bool m_bStartCheck = false;

	bool m_bButtoncheck = false;;



	float TimeAngle = 0.f;
};


#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class LoginUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LoginUI();
	~LoginUI();

	// delete Function
	LoginUI(const LoginUI& _Other) = delete;
	LoginUI(LoginUI&& _Other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _Other) = delete;
	LoginUI& operator=(LoginUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

	float TimeAngle;
};


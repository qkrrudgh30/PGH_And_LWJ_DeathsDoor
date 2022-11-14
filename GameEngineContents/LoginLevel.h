#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class LoginUI;
class LoginLevel : public ContentsLevel
{
public:
	// constrcuter destructer
	LoginLevel();
	~LoginLevel();

	// delete Function
	LoginLevel(const LoginLevel& _Other) = delete;
	LoginLevel(LoginLevel&& _Other) noexcept = delete;
	LoginLevel& operator=(const LoginLevel& _Other) = delete;
	LoginLevel& operator=(LoginLevel&& _Other) noexcept = delete;


	std::shared_ptr < LoginUI> UI;


	std::shared_ptr < PlayerUpgradeUI> UpgradeUI;
	std::shared_ptr < PlayerMainUI>		MainUI;



protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class HuntingLevel1 : public ContentsLevel
{
public:
	// constrcuter destructer
	HuntingLevel1();
	~HuntingLevel1();

	// delete Function
	HuntingLevel1(const HuntingLevel1& _Other) = delete;
	HuntingLevel1(HuntingLevel1&& _Other) noexcept = delete;
	HuntingLevel1& operator=(const HuntingLevel1& _Other) = delete;
	HuntingLevel1& operator=(HuntingLevel1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


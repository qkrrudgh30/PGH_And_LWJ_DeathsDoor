#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class HuntingLevel2 : public ContentsLevel
{
public:
	// constrcuter destructer
	HuntingLevel2();
	~HuntingLevel2();

	// delete Function
	HuntingLevel2(const HuntingLevel2& _Other) = delete;
	HuntingLevel2(HuntingLevel2&& _Other) noexcept = delete;
	HuntingLevel2& operator=(const HuntingLevel2& _Other) = delete;
	HuntingLevel2& operator=(HuntingLevel2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


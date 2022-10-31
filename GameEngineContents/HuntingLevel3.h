#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class HuntingLevel3 : public ContentsLevel
{
public:
	// constrcuter destructer
	HuntingLevel3();
	~HuntingLevel3();

	// delete Function
	HuntingLevel3(const HuntingLevel3& _Other) = delete;
	HuntingLevel3(HuntingLevel3&& _Other) noexcept = delete;
	HuntingLevel3& operator=(const HuntingLevel3& _Other) = delete;
	HuntingLevel3& operator=(HuntingLevel3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


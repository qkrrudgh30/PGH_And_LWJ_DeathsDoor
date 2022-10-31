#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class HuntingLevel4 : public ContentsLevel
{
public:
	// constrcuter destructer
	HuntingLevel4();
	~HuntingLevel4();

	// delete Function
	HuntingLevel4(const HuntingLevel4& _Other) = delete;
	HuntingLevel4(HuntingLevel4&& _Other) noexcept = delete;
	HuntingLevel4& operator=(const HuntingLevel4& _Other) = delete;
	HuntingLevel4& operator=(HuntingLevel4&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


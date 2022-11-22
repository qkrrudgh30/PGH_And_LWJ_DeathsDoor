#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class Tower;
class HuntingLevel5 : public ContentsLevel
{
public:
	// constrcuter destructer
	HuntingLevel5();
	~HuntingLevel5();

	// delete Function
	HuntingLevel5(const HuntingLevel5& _Other) = delete;
	HuntingLevel5(HuntingLevel5&& _Other) noexcept = delete;
	HuntingLevel5& operator=(const HuntingLevel5& _Other) = delete;
	HuntingLevel5& operator=(HuntingLevel5&& _Other) noexcept = delete;



private :
	std::weak_ptr < Tower> cMonster;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


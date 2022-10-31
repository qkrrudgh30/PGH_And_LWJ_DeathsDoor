#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class BossLevel : public ContentsLevel
{
public:
	// constrcuter destructer
	BossLevel();
	~BossLevel();

	// delete Function
	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator=(const BossLevel& _Other) = delete;
	BossLevel& operator=(BossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};


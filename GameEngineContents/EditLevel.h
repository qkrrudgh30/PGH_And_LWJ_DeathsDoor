#pragma once

#include "ContentsLevel.h"

// Ό³Έν :
class EditLevel 
	: public ContentsLevel
{
	friend class EditLevelPipe;

public:
	// constrcuter destructer
	EditLevel();
	~EditLevel();

	// delete Function
	EditLevel(const EditLevel& _Other) = delete;
	EditLevel(EditLevel&& _Other) noexcept = delete;
	EditLevel& operator=(const EditLevel& _Other) = delete;
	EditLevel& operator=(EditLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;

private:

};

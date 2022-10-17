#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class EditLevel;
class EditLevelPipe
{
public:
	EditLevelPipe(EditLevel* _ptrParentEditLevel)
	{
		m_ptrParentEditLevel = _ptrParentEditLevel;
	}

	static EditLevelPipe* GetInst()
	{
		return Inst;
	}

	static EditLevel* GetEditLevel()
	{
		return m_ptrParentEditLevel;
	}

private:
	static EditLevelPipe* Inst;
	static EditLevel* m_ptrParentEditLevel;

};

// Ό³Έν :
class EditLevel : public GameEngineLevel
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

#pragma once
#include <GameEngineBase/GameEngineNameObject.h>

class StateInfo
{
public:
	float StateTime; // 지금 이 스테이트가 얼마나 지속됐냐?
	std::string PrevState; // 이전 스테이트는 뭐였냐
};

class GameEngineStateManager;
class GameEngineState : public GameEngineNameObject
{
	friend GameEngineStateManager;

public:
	void StateUpdate(float _DeltaTime) 
	{
		if (nullptr == Update)
		{
			return;
		}

		Info.StateTime += _DeltaTime;
		Update(_DeltaTime, Info);
	}

private:
	StateInfo Info;
	std::function<void(const StateInfo&)> Start;
	std::function<void(const StateInfo&)> End;
	std::function<void(float, const StateInfo&)> Update;


public:
	GameEngineState()
		: Start(nullptr)
		, End(nullptr)
		, Update(nullptr)
	{

	}
};

// 설명 :
class GameEngineStateManager final // 더는 상속 못내려
{
public:
	// constrcuter destructer
	GameEngineStateManager();
	~GameEngineStateManager();

	// delete Function
	GameEngineStateManager(const GameEngineStateManager& _Other) = delete;
	GameEngineStateManager(GameEngineStateManager&& _Other) noexcept = delete;
	GameEngineStateManager& operator=(const GameEngineStateManager& _Other) = delete;
	GameEngineStateManager& operator=(GameEngineStateManager&& _Other) noexcept = delete;

	// 맴버함수만 됩니다.
	void CreateStateMember(const std::string& _StateName
		, std::function<void(float, const StateInfo&)> _Update
		, std::function<void(const StateInfo&)> _Start = nullptr
		, std::function<void(const StateInfo&)> _End = nullptr
	) 
	{
		if (AllState.end() != AllState.find(_StateName))
		{
			MsgBoxAssert("존재하는 이름의 스테이트를 또 만들려고 했습니다.");
		}

		// 무조건 만들고 find와 참조까지 찾아낸다
		GameEngineState& NewState = AllState[_StateName];
		NewState.SetName(_StateName);
		if (nullptr != _Update)
		{
			NewState.Update = _Update;
		}
		if (nullptr != _Start)
		{
			NewState.Start = _Start;
		}
		if (nullptr != _End)
		{
			NewState.End = _End;
		}
	}

	void Update(float _DeltaTime);

	std::string GetCurStateStateName()
	{
		if (nullptr == CurState)
		{
			return "";
		}

		return CurState->GetNameCopy();
	}

	void ChangeState(const std::string& _StateName)
	{
		if (AllState.end() == AllState.find(_StateName))
		{
			MsgBoxAssert("존재하지 않는 스테이트로 전이 하려고 했습니다.");
		}

		std::string PrevState = "";

		if (nullptr != CurState)
		{
			PrevState = CurState->GetNameCopy();
			if (nullptr != CurState->End)
			{
				CurState->End(CurState->Info);
			}
		}

		CurState = &AllState[_StateName];
		CurState->Info.StateTime = 0.0f;
		CurState->Info.PrevState = PrevState;

		if (nullptr != CurState->Start)
		{
			CurState->Start(CurState->Info);
		}
	}

	float GetCurStateTime() 
	{
		if (nullptr == CurState)
		{
			return 0.0f;
		}

		return CurState->Info.StateTime;
	}

protected:

private:
	std::map<std::string, GameEngineState> AllState;
	GameEngineState* CurState;
};


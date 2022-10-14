#pragma once
#include <map>
#include <chrono>

// 설명 :
class GameEngineTime
{

private:
	static GameEngineTime* Inst_;

public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	// 마지막에 지우더라도 내가 의도한 순서에서 지우고 싶기 때문에
	// pointer로 삭제하는 겁니다.
	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void Reset();
	void Update();

	static inline int GetFPS()
	{
		return Inst_->FPS;
	}


	static inline float GetDeltaTime()
	{
		if (0.05f <= Inst_->DeltaTimef)
		{
			Inst_->DeltaTimef = 0.05f;
		}

		if (Inst_->FrameLimit == -1)
		{
			return Inst_->DeltaTimef * Inst_->GlobalScale;
		}


		return Inst_->SumDeltaTimef * Inst_->GlobalScale;
	}

	static inline void SetLimitFrame(unsigned int _Frame ) 
	{
		Inst_->FrameLimit = _Frame;
		Inst_->FrameTime = 1.0f / Inst_->FrameLimit;
		Inst_->CurFrameTime = 0.0f;
	}

	template<typename EnumType>
	static inline float GetDeltaTime(EnumType _Key)
	{
		return GetDeltaTime(static_cast<int>(_Key));
	}

	static inline float GetDeltaTime(int _Key)
	{
		return Inst_->SumDeltaTimef * Inst_->GetTimeScale(_Key);
	}

	template<typename EnumType>
	static inline float SetTimeScale(EnumType _Key, float _TimeScale)
	{
		SetTimeScale(static_cast<int>(_Key), _TimeScale);
	}


	void SetTimeScale(int _Key, float _TimeScale) 
	{
		TimeScale_[_Key] = _TimeScale;
	}

	float GetTimeScale(int _Key)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			TimeScale_[_Key] = 1.0f;
		}

		return TimeScale_[_Key];
	}

	void SetGlobalScale(float _GlobalScale) 
	{
		GlobalScale = _GlobalScale;
	}

	static bool IsFrameCheck() 
	{
		return Inst_->FrameUpdate;
	}

protected:

private:
	std::chrono::steady_clock::time_point Prev;

	double DeltaTimed;
	float DeltaTimef;
	float SumDeltaTimef;
	std::map<int, float> TimeScale_;
	float GlobalScale;

	float FrameCheckTime;
	int SumFPS;
	int SumFPSCount;
	int FPS;

	int FrameLimit;
	float FrameTime;
	float CurFrameTime;
	bool FrameUpdate;

	GameEngineTime();
	~GameEngineTime();
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

};


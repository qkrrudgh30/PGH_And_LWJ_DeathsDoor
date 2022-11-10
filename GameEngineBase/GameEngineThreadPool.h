#pragma once
#include <functional>
#include "GameEngineThread.h"
#include <atomic>
// Window의 힘을 빌려서 

// obejct pool memory pool
// obejct pool은 특히나 어렵지 않은데.
// 우리 엔진에서 개념적으로 설명하면
// 몬스터 100마리 만들고 off 시켜놓은다음 필요할때마다 on하면 이걸 pool 방식이라고 한다.

// 그렇게 미리 객체를 많이 만들어 놓고 지우거나 더이상 만들지 않고
// 필요할때 마다 사용하는 방식 => pool 방식

enum ThreadWorkType
{
	UserWork = -1,
	Destroy = -2,
};


// 설명 :
class GameEngineThreadPool
{
private:
	class GameEngineThreadJob
	{
	public:
		virtual void Process() = 0;
	};

	class GameEngineThreadCallBackJob : public GameEngineThreadJob
	{
	public:
		std::function<void()> Work;

		void Process()
		{
			if (nullptr == Work)
			{
				return;
			}
			Work();
		}
	};


public:
	// constrcuter destructer
	GameEngineThreadPool(const std::string& _ThreadName, int _ThreadCount = 0);

	GameEngineThreadPool();

	~GameEngineThreadPool();

	// delete Function
	GameEngineThreadPool(const GameEngineThreadPool& _Other) = delete;
	GameEngineThreadPool(GameEngineThreadPool&& _Other) noexcept = delete;
	GameEngineThreadPool& operator=(const GameEngineThreadPool& _Other) = delete;
	GameEngineThreadPool& operator=(GameEngineThreadPool&& _Other) noexcept = delete;

	// 함수를 넘기면 쓰레드가 알아서 처리한다.
	void Work(std::function<void()> _CallBack);

	void Initialize(const std::string& _ThreadName, int _ThreadCount = 0);

protected:

private:
	HANDLE IocpHandle;
	int ThreadCount;
	std::atomic<bool> IsRun;
	std::atomic<int> DestroyThreadCount;

	static void ThreadPoolFunction(GameEngineThreadPool* _ThreadPool, GameEngineThread* _Thread, HANDLE _IocpHandle);

	std::vector<GameEngineThread*> Threads;

};

// extern GameEngineThreadPool EngineThreadPool;
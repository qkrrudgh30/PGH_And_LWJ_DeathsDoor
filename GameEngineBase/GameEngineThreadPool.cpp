#include "PreCompile.h"
#include "GameEngineThreadPool.h"
#include "GameEngineDebug.h"


GameEngineThreadPool::GameEngineThreadPool(const std::string& _ThreadName, int _ThreadCount /*= 0*/)
{
	Initialize(_ThreadName, _ThreadCount);
}

GameEngineThreadPool::GameEngineThreadPool()
{

}

void GameEngineThreadPool::Initialize(const std::string& _ThreadName, int _ThreadCount /*= 0*/)
{
	// 왜 코어개수 *2가 쓰레드의 적절 양이어있는지 까먹음
// ...

	ThreadCount = _ThreadCount;

	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount = Info.dwNumberOfProcessors;
	}

	// 최초에 만드는 iocp핸들은 
	// CreateIoCompletionPort는 여러가지 역할이 있는데
	IocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);

	if (nullptr == IocpHandle)
	{
		MsgBoxAssert("IOCP 핸들 생성에 실패했습니다.");
		return;
	}

	IsRun = true;
	DestroyThreadCount = 0;

	for (size_t i = 0; i < ThreadCount; i++)
	{
		GameEngineThread* NewThread = new GameEngineThread();

		Threads.push_back(NewThread);

		NewThread->SetName(_ThreadName + std::to_string(i));
		NewThread->Start(_ThreadName + std::to_string(i)
			, std::bind(ThreadPoolFunction, this, NewThread, IocpHandle));
	}

}

void GameEngineThreadPool::ThreadPoolFunction(GameEngineThreadPool* _ThreadPool, GameEngineThread* _Thread, HANDLE _IocpHandle)
{
	//_In_ HANDLE CompletionPort,
	// // io작업을 할때 얼마나 전달받았는지를 적어준다.
	// // 내가 io작업을 하지 않는다면 내가 직접 넣어줄수도 있다.
	//_Out_ LPDWORD lpNumberOfBytesTransferred, 
	// 
	// 8바이트를 이 일에 관련된 사용자 데이터인 8바이트 정수를 넣어줄수 있다.
	// 내가 임의로 넣어줄수 있는 키.
	//_Out_ PULONG_PTR lpCompletionKey,
	// 
	// 비동기 io작업시 윈도우에서 요청하는 구조체 직접 동적할당해서 넣어줘야 한다.
	//_Out_ LPOVERLAPPED* lpOverlapped,
	//_In_ DWORD dwMilliseconds


	DWORD Byte;
	ULONG_PTR CompletionKey;
	LPOVERLAPPED lpOverlapped;

	while (_ThreadPool->IsRun)
	{
		GetQueuedCompletionStatus(_IocpHandle, &Byte, &CompletionKey, &lpOverlapped, INFINITE);

		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);
		switch (WorkType)
		{
		case UserWork:
		{
			GameEngineThreadCallBackJob* Job = reinterpret_cast<GameEngineThreadCallBackJob*>(CompletionKey);
			Job->Process();
			delete Job;
			break;
		}
		case Destroy:
			++_ThreadPool->DestroyThreadCount;
			return;
		default:
			break;
		}
		// Sleep(1);
		// 일하는 곳.
	}
}

GameEngineThreadPool::~GameEngineThreadPool() 
{
	IsRun = false;

	while (true)
	{
		if (FALSE == PostQueuedCompletionStatus(
			IocpHandle,
			static_cast<DWORD>(ThreadWorkType::Destroy),
			0,
			nullptr)
			)
		{
			MsgBoxAssert("쓰레드에게 콜백잡을 요청하는데 실패했습니다.");
		}

		Sleep(1);

		if (DestroyThreadCount == ThreadCount)
		{
			break;
		}
	}

	for (size_t i = 0; i < Threads.size(); i++)
	{
		Threads[i]->Join();
		delete Threads[i];
	}
}


void GameEngineThreadPool::Work(std::function<void()> _CallBack) 
{
	if (nullptr == _CallBack)
	{
		MsgBoxAssert("유효하지 않은 함수 포인터 입니다. 이 함수포인터는 쓰레드에게 맡길수 없습니다.");
	}

	GameEngineThreadCallBackJob* NewJob = new GameEngineThreadCallBackJob();

	NewJob->Work = _CallBack;

	// iocp에게 하나의 컴플리션 키를 전달하면서 1개의 쓰레드를 깨운다..
	if (FALSE == PostQueuedCompletionStatus(
		IocpHandle, 
		static_cast<DWORD>(ThreadWorkType::UserWork), 
		reinterpret_cast<ULONG_PTR>(NewJob), 
		nullptr)
		)
	{
		MsgBoxAssert("쓰레드에게 콜백잡을 요청하는데 실패했습니다.");
	}
}


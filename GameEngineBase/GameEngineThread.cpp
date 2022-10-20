#include "PreCompile.h"
#include "GameEngineThread.h"
#include "GameEngineString.h"

GameEngineThread::GameEngineThread() 
{
}

GameEngineThread::GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	Start(_ThreadName, _CallBack);
}

GameEngineThread::~GameEngineThread() 
{
	Join();
}


void GameEngineThread::GameEngineThreadFunction(GameEngineThread* _Thread, std::string _Name) 
{
	// 쓰레드의 영역입니다.
	std::wstring WName = GameEngineString::AnsiToUnicodeReturn(_Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	_Thread->WorkFunction(_Thread);
}
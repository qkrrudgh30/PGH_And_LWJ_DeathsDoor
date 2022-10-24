#pragma once
#include <thread>
#include <functional>
#include <Windows.h>
#include "GameEngineNameObject.h"

// Ό³Έν :
class GameEngineThread : public GameEngineNameObject
{
public:
	GameEngineThread();

	// constrcuter destructer
	GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack);
	~GameEngineThread();

	// delete Function
	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(GameEngineThread&& _Other) noexcept = delete;

	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
	{
		WorkFunction = _CallBack;
		Thread = std::thread(GameEngineThreadFunction, this, _ThreadName);
	}

	void Join()
	{
		if (nullptr != WorkFunction)
		{
			Sleep(1);
			Thread.join();
			WorkFunction = nullptr;
		}
	}


private:
	std::thread Thread;
	std::function<void(GameEngineThread*)> WorkFunction;

	static void GameEngineThreadFunction(GameEngineThread* _Thread, std::string _Name);

};


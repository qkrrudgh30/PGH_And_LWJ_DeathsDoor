#include "PreCompile.h"
#include "GameEngineRandom.h"
#include <chrono>

GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom(long long _Seed /*= -1*/)
	// : mt_(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
	if (_Seed != -1)
	{
		mt_ = std::mt19937_64(_Seed);
	}
	else 
	{
		mt_ = std::mt19937_64(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	}
}

GameEngineRandom::~GameEngineRandom() 
{
}


#include "PreCompile.h"
#include "GameEngineInstancing.h"

// 최소 2개이상이 모여야 인스턴싱을 시작하겠다.
unsigned int GameEngineInstancing::MinInstancingCount = 1;

// 일단 시작했다면 100개는 할수 있다는 가정하에 이걸 하겠다.
unsigned int GameEngineInstancing::StartInstancingCount = 100;

GameEngineInstancing::GameEngineInstancing() 
	: Buffer(nullptr)
	, Count(0)
	, DataInsert(0)

{
}

GameEngineInstancing::~GameEngineInstancing() 
{
}



void GameEngineInstancing::InstancingBufferChangeData()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("인스턴싱에 버퍼를 만들지 않았습니다. 않았습니다.")
	}

	Buffer->ChangeData(&DataBuffer[0], DataBuffer.size());
}
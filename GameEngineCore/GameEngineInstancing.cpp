#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineRenderer.h"
#include "GameEngineVertexShader.h"

const int Inst_Max = 100;

GameEngineInstancing::GameEngineInstancing() 
	: Buffer(nullptr)
	, Count(0)
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

void GameEngineInstancing::PushUnit(std::shared_ptr<GameEngineRenderUnit> _Unit)
{
	if (nullptr == InitUnit)
	{
		InitUnit = _Unit;
	}

	_Unit->Off();

	if (false == _Unit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("인스턴싱용 메테리얼을 가지지 않은 유니트 입니다");
	}

	for (size_t i = 0; i < Units.size(); i++)
	{

	}

	// Units.push_back(_Unit);

	if (Units.size())
	{

	}
}
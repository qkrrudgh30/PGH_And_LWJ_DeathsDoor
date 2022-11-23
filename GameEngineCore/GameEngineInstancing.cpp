#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineRenderer.h"
#include "GameEngineVertexShader.h"

void GameEngineInstancing::InstancingData::Link(const std::string_view& _Name, const void* _Data)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name.data());

	if (Data.end() == Data.find(UpperName))
	{
		MsgBoxAssertString("인스턴싱용 데이터가 존재하지 않습니다 => " + UpperName);
	}

	std::multimap<std::string, const void*>::iterator Start = Data.lower_bound(UpperName);
	std::multimap<std::string, const void*>::iterator End = Data.upper_bound(UpperName);
	for (; Start != End; ++Start)
	{
		Start->second = _Data;
	}
}

void GameEngineInstancing::InstancingData::Init(std::multiset<std::string>& _Set)
{
	//std::multimap<std::string, GameEngineStructuredBufferSetter>& StructuredBuffers
	//	= _Helper.GetStructuredBufferSettingMap();

	//std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator Start = StructuredBuffers.begin();
	//std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator End = StructuredBuffers.end();

	for (const std::string& _Name : _Set)
	{
		Data.insert(std::make_pair(_Name, nullptr));
	}

	//for (; Start != End; ++Start)
	//{
	//	if (std::string::npos != Start->first.find("INST_"))
	//	{
	//		Data.insert(std::make_pair(Start->first, nullptr));
	//	}
	//}

}

size_t GameEngineInstancing::MaxInstancingCount = 100;

GameEngineInstancing::GameEngineInstancing() 
	: Buffer(nullptr)
	, Count(0)

{
	// CreateInstancingUnit();
}

std::list<GameEngineInstancing::InstancingData>& GameEngineInstancing::CreateInstancingUnit()
{
	// 새로운 100개 짜리 그룹이 만들어진다.
	std::list<InstancingData>& NewGroup = Units.emplace_back();
	// 거기에 들어갈 인스턴싱용 버퍼도 만들어져
	std::vector<char>& Data = DataBuffer.emplace_back();
	// 헬퍼
	GameEngineShaderResourcesHelper& Helper = ShaderResources.emplace_back();

	Helper.ShaderCheck(InitUnit->GetMaterial()->GetVertexShader()->GetInstancingShader());


	unsigned int size = static_cast<unsigned int>(InitUnit->GetMesh()->GetLayOutDesc().InstancingSize);
	Buffer = GameEngineInstancingBuffer::Create(MaxInstancingCount, size);
	Data.resize(MaxInstancingCount * size);

	// 스트럭처드 버퍼 조사
	std::multimap<std::string, GameEngineStructuredBufferSetter>& StructuredBuffers
		= Helper.GetStructuredBufferSettingMap();

	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator Start = StructuredBuffers.begin();
	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator End = StructuredBuffers.end();

	for (; Start != End; ++Start)
	{
		if (std::string::npos != Start->first.find("INST_"))
		{
			Start->second.Resize(MaxInstancingCount);
		}
	}

	if (StructuredBufferSet.empty())
	{
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator Start = StructuredBuffers.begin();
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator End = StructuredBuffers.end();

		for (; Start != End; ++Start)
		{
			if (std::string::npos != Start->first.find("INST_"))
			{
				StructuredBufferSet.insert(Start->first);
			}
		}
	}

	return NewGroup;
}

GameEngineInstancing::~GameEngineInstancing() 
{
}

void GameEngineInstancing::RenderInstancing() 
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

void GameEngineInstancing::PushUnit(std::shared_ptr<GameEngineRenderUnit> _Unit, std::function<void(InstancingData&)> _Function)
{
	if (nullptr == InitUnit)
	{
		InitUnit = _Unit;

		if (false == InitUnit->GetMaterial()->GetVertexShader()->IsInstancing())
		{
			MsgBoxAssert("인스턴싱용 메테리얼이 아닙니다.");
		}

		CreateInstancingUnit();
	}

	_Unit->Off();

	if (false == _Unit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("인스턴싱용 메테리얼을 가지지 않은 유니트 입니다");
	}

	// 100개
	// 1 개

	bool Push = false;

	for (size_t i = 0; i < Units.size(); i++)
	{
		if (MaxInstancingCount <= Units[i].size())
		{
			continue;
		}

		Push = true;
		InstancingData NewData = { _Unit };

		NewData.Init(StructuredBufferSet);

		_Function(NewData);

		Units[i].push_back(NewData);
	}

	if (false == Push)
	{
		std::list<InstancingData>& Insert = CreateInstancingUnit();

		InstancingData NewData = { _Unit };

		NewData.Init(StructuredBufferSet);

		_Function(NewData);

		Insert.push_back(NewData);
	}
	

}


#pragma once
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineInstancingBuffer.h"

// Ό³Έν :
class GameEngineRenderUnit;
class GameEngineInstancing
{
	static size_t MaxInstancingCount;

public:
	class InstancingData
	{
		friend GameEngineInstancing;

	public:
		InstancingData(std::shared_ptr<GameEngineRenderUnit> _Unit) 
			: Unit(_Unit)
		{

		}

		void Init(std::multiset<std::string>& _Helper);

		template<typename ValueType>
		void Link(const std::string_view& _Name, ValueType& _Data)
		{
			Link(_Name, reinterpret_cast<const void*>(&_Data));
		}

		void Link(const std::string_view& _Name, const void* _Data);

	private:
		std::shared_ptr<GameEngineRenderUnit> Unit;
		std::multimap<std::string, const void*> Data;

	};

public:
	// constrcuter destructer
	GameEngineInstancing();
	~GameEngineInstancing();

	// delete Function
	GameEngineInstancing(const GameEngineInstancing& _Other) = delete;
	GameEngineInstancing(GameEngineInstancing&& _Other) noexcept = delete;
	GameEngineInstancing& operator=(const GameEngineInstancing& _Other) = delete;
	GameEngineInstancing& operator=(GameEngineInstancing&& _Other) noexcept = delete;

	void PushUnit(std::shared_ptr<GameEngineRenderUnit> _Unit, std::function<void(InstancingData&)> _Function);

	void RenderInstancing();


private:
	int Size;

	unsigned int Count;

	int MaxDataCount;

	std::shared_ptr<GameEngineInstancingBuffer> Buffer;

	std::shared_ptr<GameEngineRenderUnit> InitUnit;

	std::vector<std::list<InstancingData>> Units;
	// std::vector<std::multimap<std::string, std::list<void*>>> Datas;
	std::vector<GameEngineShaderResourcesHelper> ShaderResources;
	std::vector<std::vector<char>> DataBuffer;

	std::multiset<std::string> StructuredBufferSet;


	void InstancingBufferChangeData();

	std::list<InstancingData>& CreateInstancingUnit();

};
#pragma once
#include <string>
#include <list>
#include <map>
#include <GameEngineBase/GameEngineString.h>
#include "GameEngineRes.h"

// Ό³Έν :
class GameEngineConstantBuffer :  public GameEngineRes<GameEngineConstantBuffer>
{
private:

public:
	static std::shared_ptr < GameEngineConstantBuffer> Find(const std::string& _Name, int _ByteSize)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, std::map<int, std::shared_ptr<GameEngineConstantBuffer>>>::iterator NameIter = ConstantBufferRes.find(UpperName);

		if (ConstantBufferRes.end() == NameIter)
		{
			return nullptr;
		}

		std::map<int, std::shared_ptr < GameEngineConstantBuffer>>& SizeMap = NameIter->second;

		std::map<int, std::shared_ptr < GameEngineConstantBuffer>>::iterator SizeIter = SizeMap.find(_ByteSize);

		if (SizeIter == SizeMap.end())
		{
			return nullptr;
		}

		return SizeIter->second;
	}

	static std::shared_ptr < GameEngineConstantBuffer> Create(
		const std::string& _Name, 
		D3D11_SHADER_BUFFER_DESC _Desc
	)
	{
		std::shared_ptr < GameEngineConstantBuffer> NewBuffer = CreateResName(_Name, _Desc.Size);

		NewBuffer->Create(_Desc);

		return NewBuffer;
	}


	static std::shared_ptr < GameEngineConstantBuffer> CreateAndFind(
		const std::string& _Name,
		D3D11_SHADER_BUFFER_DESC _Desc
	)
	{
		std::shared_ptr < GameEngineConstantBuffer> FindBuffer = Find(_Name, _Desc.Size);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		std::shared_ptr < GameEngineConstantBuffer> NewBuffer = CreateResName(_Name, _Desc.Size);

		NewBuffer->Create(_Desc);

		return NewBuffer;
	}


	static void ResourcesDestroy()
	{
		//for (auto& Res : UnNamedRes)
		//{
		//	delete Res;
		//}

		ConstantBufferRes.clear();

		//for (auto& NameRes : ConstantBufferRes)
		//{
		//	for (auto& SizeRes : NameRes.second)
		//	{
		//		delete SizeRes.second;
		//	}
		//}
	}

protected:
	static std::shared_ptr < GameEngineConstantBuffer> CreateResName(const std::string& _Name, int _ByteSize)
	{
		std::string Name = GameEngineString::ToUpperReturn(_Name);

		std::shared_ptr < GameEngineConstantBuffer> FindBuffer = Find(_Name, _ByteSize);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		std::shared_ptr<GameEngineConstantBuffer> Res = CreateRes(Name);
		ConstantBufferRes[Name][_ByteSize] = Res;

		return Res;
	}


private:
	static std::map<std::string, std::map<int, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes;


public:
	// constrcuter destructer
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	// delete Function
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	void ChangeData(const void* _Data, size_t _Size) const;

	void VSSetting(int _BindPoint);

	void PSSetting(int _BindPoint);

	D3D11_BUFFER_DESC& GetBufferDesc() 
	{
		return BufferDesc;
	}

protected:

private:
	ID3D11Buffer* Buffer;
	D3D11_BUFFER_DESC BufferDesc;
	D3D11_SHADER_BUFFER_DESC ShaderDesc;
	// D3D11_MAPPED_SUBRESOURCE SettingResources;

	void Create(const D3D11_SHADER_BUFFER_DESC& _Desc);
};


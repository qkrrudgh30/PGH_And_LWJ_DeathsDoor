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
	static GameEngineConstantBuffer* Find(const std::string& _Name, int _ByteSize)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, std::map<int, GameEngineConstantBuffer*>>::iterator NameIter = ConstantBufferRes.find(UpperName);

		if (ConstantBufferRes.end() == NameIter)
		{
			return nullptr;
		}

		std::map<int, GameEngineConstantBuffer*>& SizeMap = NameIter->second;

		std::map<int, GameEngineConstantBuffer*>::iterator SizeIter = SizeMap.find(_ByteSize);

		if (SizeIter == SizeMap.end())
		{
			return nullptr;
		}

		return SizeIter->second;
	}

	static GameEngineConstantBuffer* Create(
		const std::string& _Name, 
		D3D11_SHADER_BUFFER_DESC _Desc
	)
	{
		GameEngineConstantBuffer* NewBuffer = CreateResName(_Name, _Desc.Size);

		NewBuffer->Create(_Desc);

		return NewBuffer;
	}


	static GameEngineConstantBuffer* CreateAndFind(
		const std::string& _Name,
		D3D11_SHADER_BUFFER_DESC _Desc
	)
	{
		GameEngineConstantBuffer* FindBuffer = Find(_Name, _Desc.Size);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		GameEngineConstantBuffer* NewBuffer = CreateResName(_Name, _Desc.Size);

		NewBuffer->Create(_Desc);

		return NewBuffer;
	}


	static void ResourcesDestroy()
	{
		//for (auto& Res : UnNamedRes)
		//{
		//	delete Res;
		//}

		for (auto& NameRes : ConstantBufferRes)
		{
			for (auto& SizeRes : NameRes.second)
			{
				delete SizeRes.second;
			}
		}
	}

protected:
	static GameEngineConstantBuffer* CreateResName(const std::string& _Name, int _ByteSize)
	{
		std::string Name = GameEngineString::ToUpperReturn(_Name);

		GameEngineConstantBuffer* FindBuffer = Find(_Name, _ByteSize);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		GameEngineConstantBuffer* Res = CreateRes(Name);
		ConstantBufferRes[Name][_ByteSize] = Res;

		return Res;
	}


private:
	static std::map<std::string, std::map<int, GameEngineConstantBuffer*>> ConstantBufferRes;


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


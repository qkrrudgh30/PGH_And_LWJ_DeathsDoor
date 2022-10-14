#include "PreCompile.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineStructuredBuffer.h"

GameEngineShaderResourcesHelper::GameEngineShaderResourcesHelper() 
{
}

GameEngineShaderResourcesHelper::~GameEngineShaderResourcesHelper() 
{
}

void GameEngineShaderResourcesHelper::AllResourcesSetting()
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : ConstantBufferSettingMap)
	{
		Setter.second.Setting();
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& Setter : TextureSettingMap)
	{
		Setter.second.Setting();
	}

	for (const std::pair<std::string, GameEngineSamplerSetter>& Setter : SamplerSettingMap)
	{
		Setter.second.Setting();
	}

	for (const std::pair<std::string, GameEngineStructuredBufferSetter>& Setter : StructuredBufferSettingMap)
	{
		Setter.second.Setting();
	}

}


void GameEngineShaderResourcesHelper::AllResourcesReset()
{
	for (const std::pair<std::string, GameEngineTextureSetter>& Setter : TextureSettingMap)
	{
		Setter.second.Reset();
	}
}

void GameEngineShaderResourcesHelper::ResourcesCheck(GameEngineRenderingPipeLine* _Line)
{
	if (nullptr == _Line)
	{
		MsgBoxAssert("파이프라인이 nullptr 입니다 정상적인 파이프라인을 넣어주세요");
	}

	ShaderCheck(_Line->GetVertexShader());
	ShaderCheck(_Line->GetPixelShader());

}

void GameEngineShaderResourcesHelper::ShaderCheck(GameEngineShader* _Shader)
{
	// 픽셀쉐이더와 버텍스 쉐이더에서 transform데이터 같은 중요 상수버퍼의 이름을 똑같이 해서 사용하고 싶다면??????
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Data : _Shader->ConstantBufferMap)
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator InsertIter = 
			ConstantBufferSettingMap.insert(std::make_pair(Data.first, Data.second));

		BindConstantBuffer(InsertIter->second, Data.second.Res);
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& Data : _Shader->TextureMap)
	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator InsertIter =
		TextureSettingMap.insert(std::make_pair(Data.first, Data.second));

		BindTexture(InsertIter->second, Data.second.Res);

	}


	for (const std::pair<std::string, GameEngineSamplerSetter>& Data : _Shader->SamplerMap)
	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator InsertIter =
			SamplerSettingMap.insert(std::make_pair(Data.first, Data.second));

		BindSampler(InsertIter->second, Data.second.Res);
	}


	for (const std::pair<std::string, GameEngineStructuredBufferSetter>& Data : _Shader->StructuredBufferMap)
	{
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator InsertIter =
			StructuredBufferSettingMap.insert(std::make_pair(Data.first, Data.second));

		BindStructuredBuffer(InsertIter->second, Data.second.Res);
	}

}

bool GameEngineShaderResourcesHelper::IsConstantBuffer(const std::string& _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	if (ConstantBufferSettingMap.end() != ConstantBufferSettingMap.find(Key))
	{
		return true;
	}

	return false;
}

bool GameEngineShaderResourcesHelper::IsStructuredBuffer(const std::string& _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	if (StructuredBufferSettingMap.end() != StructuredBufferSettingMap.find(Key))
	{
		return true;
	}

	return false;
}

GameEngineStructuredBufferSetter* GameEngineShaderResourcesHelper::GetStructuredBuffer(const std::string& _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator Find = StructuredBufferSettingMap.find(Key);

	if (StructuredBufferSettingMap.end() != Find)
	{
		return &Find->second;
	}

	return &Find->second;
}

void GameEngineShaderResourcesHelper::SetConstantBufferNew(const std::string& _Name, const void* _Data, UINT _Size)
{
	if (false == IsConstantBuffer(_Name))
	{
		MsgBoxAssertString(_Name + "쉐이더에서 이러한 이름의 상수버퍼를 사용한 적이 없습니다.");
		return;
	}

	if (16 > _Size)
	{

		MsgBox("최소한 16바이트 이상의 세팅을 해줘야 합니다.");
		return;
	}

	std::string Name = GameEngineString::ToUpperReturn(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter
		= ConstantBufferSettingMap.lower_bound(Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter
		= ConstantBufferSettingMap.upper_bound(Name);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		// 트랜스폼이 바뀌면

		if (0 == NameStartIter->second.OriginalData.size()
			|| NameStartIter->second.OriginalData.size() != _Size)
		{
			NameStartIter->second.OriginalData.resize(_Size);
		}

		NameStartIter->second.SetData = &NameStartIter->second.OriginalData[0];
		memcpy_s(&NameStartIter->second.OriginalData[0], _Size, _Data, _Size);

		NameStartIter->second.Size = _Size;
	}
}

void GameEngineShaderResourcesHelper::SetConstantBufferLink(
	const std::string& _Name, 
	const void* _Data, 
	UINT _Size)
{
	if (false == IsConstantBuffer(_Name))
	{
		MsgBoxAssertString(_Name + "쉐이더에서 이러한 이름의 상수버퍼를 사용한 적이 없습니다.");
		return;
	}

	if (16 > _Size)
	{

		MsgBox("최소한 16바이트 이상의 세팅을 해줘야 합니다.");
		return;
	}

	std::string Name = GameEngineString::ToUpperReturn(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter
		= ConstantBufferSettingMap.lower_bound(Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter
		= ConstantBufferSettingMap.upper_bound(Name);

	for (; NameStartIter != NameEndIter ; ++NameStartIter)
	{
		// 트랜스폼이 바뀌면
		NameStartIter->second.SetData = _Data;
		NameStartIter->second.Size = _Size;
	}

}

bool GameEngineShaderResourcesHelper::IsTexture(const std::string& _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	if (TextureSettingMap.end() != TextureSettingMap.find(Key))
	{
		return true;
	}

	return false;
}


GameEngineTexture* GameEngineShaderResourcesHelper::SetTexture(const std::string& _Name, const std::string& _TextureName)
{
	if (false == IsTexture(_Name))
	{
		MsgBox("쉐이더에서 이러한 이름의 텍스처세팅를 사용한 적이 없습니다.");
		return nullptr;
	}

	std::string Name = GameEngineString::ToUpperReturn(_Name);

	return SetTexture(_Name, GameEngineTexture::Find(_TextureName));
}

GameEngineTexture* GameEngineShaderResourcesHelper::SetTexture(const std::string& _Name, const std::string& _FolderTextureName, int _Index)
{
	if (false == IsTexture(_Name))
	{
		MsgBox("쉐이더에서 이러한 이름의 텍스처세팅를 사용한 적이 없습니다.");
		return nullptr;
	}

	std::string Name = GameEngineString::ToUpperReturn(_Name);

	std::string TextureName = GameEngineString::ToUpperReturn(_FolderTextureName);

	GameEngineFolderTexture* Tex = GameEngineFolderTexture::Find(TextureName);

	if (nullptr == Tex)
	{
		MsgBoxAssert("존재하지 않는 폴더 텍스처를 세팅하려고 했습니다.");
	}

	return SetTexture(_Name, Tex->GetTexture(_Index));
}

GameEngineTexture* GameEngineShaderResourcesHelper::SetTexture(const std::string& _Name, GameEngineTexture* _Texture)
{
	std::string Name = GameEngineString::ToUpperReturn(_Name);

	if (false == IsTexture(_Name))
	{
		MsgBox("쉐이더에서 이러한 이름의 텍스처세팅를 사용한 적이 없습니다.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter
		= TextureSettingMap.lower_bound(Name);

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter
		= TextureSettingMap.upper_bound(Name);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		BindTexture(NameStartIter->second, _Texture);
	}

	return _Texture;
}


bool GameEngineShaderResourcesHelper::IsSampler(const std::string& _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	if (SamplerSettingMap.end() != SamplerSettingMap.find(Key))
	{
		return true;
	}

	return false;
}


GameEngineSampler* GameEngineShaderResourcesHelper::SetSampler(const std::string& _Name, const std::string& _TextureName)
{
	if (false == IsSampler(_Name))
	{
		MsgBox("쉐이더에서 이러한 이름의 텍스처세팅를 사용한 적이 없습니다.");
		return nullptr;
	}

	std::string Name = GameEngineString::ToUpperReturn(_Name);

	return SetSampler(_Name, GameEngineSampler::Find(_TextureName));

}

GameEngineSampler* GameEngineShaderResourcesHelper::SetSampler(const std::string& _Name, GameEngineSampler* _Res)
{
	std::string Name = GameEngineString::ToUpperReturn(_Name);

	if (false == IsSampler(_Name))
	{
		MsgBox("쉐이더에서 이러한 이름의 텍스처세팅를 사용한 적이 없습니다.");
		return nullptr;
	}

	std::multimap<std::string, GameEngineSamplerSetter>::iterator NameStartIter
		= SamplerSettingMap.lower_bound(Name);

	std::multimap<std::string, GameEngineSamplerSetter>::iterator NameEndIter
		= SamplerSettingMap.upper_bound(Name);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		BindSampler(NameStartIter->second, _Res);
	}

	return _Res;
}

void GameEngineShaderResourcesHelper::BindTexture(GameEngineTextureSetter& _Setter, GameEngineTexture* _Res)
{
	_Setter.Res = _Res;

	if (nullptr == _Res)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	}

	switch (_Setter.ShaderType)
	{
	case ShaderType::Vertex:
		_Setter.SettingFunction = std::bind(&GameEngineTexture::VSSetting, _Setter.Res, _Setter.BindPoint);
		_Setter.ResetFunction = std::bind(&GameEngineTexture::VSReset, _Setter.Res, _Setter.BindPoint);
		break;
	case ShaderType::Pixel:
		_Setter.SettingFunction = std::bind(&GameEngineTexture::PSSetting, _Setter.Res, _Setter.BindPoint);
		_Setter.ResetFunction = std::bind(&GameEngineTexture::PSReset, _Setter.Res, _Setter.BindPoint);
		break;
	default:
		break;
	}
}

void GameEngineShaderResourcesHelper::BindConstantBuffer(GameEngineConstantBufferSetter& _Setter, GameEngineConstantBuffer* _Res)
{
	_Setter.Res = _Res;

	if (nullptr == _Res)
	{
		MsgBoxAssert("존재하지 않는 상수버퍼를 사용하려고 했습니다.");
	}

	switch (_Setter.ShaderType)
	{
	case ShaderType::Vertex:
		_Setter.SettingFunction = std::bind(&GameEngineConstantBuffer::VSSetting, _Setter.Res, _Setter.BindPoint);
		break;
	case ShaderType::Pixel:
		_Setter.SettingFunction = std::bind(&GameEngineConstantBuffer::PSSetting, _Setter.Res, _Setter.BindPoint);
		break;
	default:
		break;
	}
}

void GameEngineShaderResourcesHelper::BindSampler(GameEngineSamplerSetter& _Setter, GameEngineSampler* _Res)
{
	_Setter.Res = _Res;

	if (nullptr == _Res)
	{
		MsgBoxAssert("존재하지 않는 샘플러를 사용하려고 했습니다.");
	}

	switch (_Setter.ShaderType)
	{
	case ShaderType::Vertex:
		_Setter.SettingFunction = std::bind(&GameEngineSampler::VSSetting, _Setter.Res, _Setter.BindPoint);
		break;
	case ShaderType::Pixel:
		_Setter.SettingFunction = std::bind(&GameEngineSampler::PSSetting, _Setter.Res, _Setter.BindPoint);
		break;
	default:
		break;
	}
}

void GameEngineShaderResourcesHelper::BindStructuredBuffer(GameEngineStructuredBufferSetter& _Setter, GameEngineStructuredBuffer* _Res)
{
	_Setter.Res = _Res;

	if (nullptr == _Res)
	{
		MsgBoxAssert("존재하지 않는 샘플러를 사용하려고 했습니다.");
	}

	switch (_Setter.ShaderType)
	{
	case ShaderType::Vertex:
		_Setter.SettingFunction = std::bind(&GameEngineStructuredBuffer::VSSetting, _Setter.Res, _Setter.BindPoint);
		break;
	case ShaderType::Pixel:
		_Setter.SettingFunction = std::bind(&GameEngineStructuredBuffer::PSSetting, _Setter.Res, _Setter.BindPoint);
		break;
	default:
		break;
	}
}



void GameEngineShaderResourcesHelper::AllConstantBufferNew()
{
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator Start = ConstantBufferSettingMap.begin();
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator End = ConstantBufferSettingMap.end();

	for (; Start != End; ++Start)
	{
		int Buffersize = Start->second.Res->GetBufferDesc().ByteWidth;
		Start->second.OriginalData.resize(Buffersize);
		Start->second.SetData = &Start->second.OriginalData[0];
		Start->second.Size = Buffersize;
	}
}
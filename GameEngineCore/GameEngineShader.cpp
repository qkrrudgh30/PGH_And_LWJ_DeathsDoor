#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineStructuredBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

void GameEngineConstantBufferSetter::Setting() const
{
	// SetData는 Cpu에 있는 데이터의 포인터일 뿐이다.
	Res->ChangeData(SetData, Size);
	SettingFunction();
}

void GameEngineTextureSetter::Setting() const
{
	SettingFunction();
}

void GameEngineTextureSetter::Reset() const
{
	ResetFunction();
}

void GameEngineSamplerSetter::Setting() const
{
	SettingFunction();
}

void GameEngineStructuredBufferSetter::Setting() const
{
	Res->ChangeData(&CpuDataBuffer[0], CpuDataBuffer.size());
	SettingFunction();
}

int GameEngineStructuredBufferSetter::GetDataSize()
{
	return Res->GetDataSize();
}

void GameEngineStructuredBufferSetter::Resize(int _Count)
{
	Res->CreateResize(_Count, nullptr);
	CpuDataBuffer.resize(Res->GetDataSize() * _Count);
}

void GameEngineStructuredBufferSetter::PushData(const void* Data, int _Count)
{
	int Count = Res->GetDataSize() * _Count;
	memcpy_s(&CpuDataBuffer[Count], CpuDataBuffer.size(), Data, Res->GetDataSize());
}




void GameEngineShader::AutoCompile(const std::string& _Path)
{
	GameEngineFile File = GameEngineFile(_Path);
	File.Open(OpenMode::Read, FileMode::Text);

	std::string AllHlslCode = File.GetString();

	size_t VSEntryIndex = AllHlslCode.find("_VS(");
	// 0123456789
	//"a Color_VS("
	// VSEntryIndex == 7
	if (std::string::npos != VSEntryIndex)
	{
		// size_t VSEntryIndex = AllHlslCode.find("_VS(");
		// 7부터 찾아라 앞쪽으로
		// 1

		GameEngineVertexShader* Vertex = nullptr;

		{
			size_t FirstIndex = AllHlslCode.find_last_of(" ", VSEntryIndex);
			// "01234567"
			// substr(2, 3); "234"

			// ' 'Color_VS 
			std::string EntryName = AllHlslCode.substr(FirstIndex + 1, VSEntryIndex - FirstIndex - 1);
			EntryName += "_VS";
			Vertex = GameEngineVertexShader::Load(_Path, EntryName);
		}

		if (nullptr != Vertex)
		{
			size_t VSInstEntryIndex = AllHlslCode.find("_VSINST(");
			if (std::string::npos != VSInstEntryIndex)
			{
				size_t FirstIndex = AllHlslCode.find_last_of(" ", VSInstEntryIndex);
				std::string EntryName = AllHlslCode.substr(FirstIndex + 1, VSInstEntryIndex - FirstIndex - 1);
				EntryName += "_VSINST";
				Vertex->InstancingShaderCompile(_Path, EntryName);
			}
		}
	}

	size_t PSEntryIndex = AllHlslCode.find("_PS(");
	if (std::string::npos != PSEntryIndex)
	{
		size_t FirstIndex = AllHlslCode.find_last_of(" ", PSEntryIndex);
		std::string EntryName = AllHlslCode.substr(FirstIndex + 1, PSEntryIndex - FirstIndex - 1);
		EntryName += "_PS";
		GameEnginePixelShader::Load(_Path, EntryName);
	}

	// File.GetFileSize();

}

GameEngineShader::GameEngineShader() 
	: Version("")
	, BinaryPtr(nullptr)
{
}

GameEngineShader::~GameEngineShader() 
{
	if (nullptr != BinaryPtr)
	{
		BinaryPtr->Release();
		BinaryPtr = nullptr;
	}
}



void GameEngineShader::CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow)
{
	Version = "";
	Version += _ShaderType + "_"; // vs_
	Version += std::to_string(_VersionHigh); // vs_5
	Version += "_"; // vs_5_
	Version += std::to_string(_VersionLow); // vs_5_0
}

// 쉐이더에서 상수버퍼를 사용했는지 텍스처를 썼는지
void GameEngineShader::ShaderResCheck()
{
	// BinaryPtr 완전히 빌드된 쉐이더 파일의 2진 메모리
	if (nullptr == BinaryPtr)
	{
		MsgBoxAssert("쉐이더 리소스가 만들어지지 않았는데 리소스(상수버퍼 and 텍스처) 체크를 하려고 했습니다.");
		return;
	}

	// Reflection 
	// 클래스의 세부 정보를 언어차원에서 우리에게 제공해줄때 그 클래스나 함수들이 이런 이름을 가지고 있다.
	// 이런 이름의 인터페이스 
	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(
		BinaryPtr->GetBufferPointer(), 
		BinaryPtr->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>( & CompileInfo)
	))
	{
		MsgBoxAssert("쉐이더 쉐이더 리플렉션이 잘못 돼었습니다.");
		return;
	}


	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResInfo;
	// D3D11_SIGNATURE_PARAMETER_DESC InputDesc;

	//for (size_t i = 0; i < Info.InputParameters; i++)
	//{
	//	CompileInfo->GetInputParameterDesc(i, &InputDesc);

	//	int a = 0;
	//}

	// Info.BoundResources 이게 이 쉐이더에서 사용된 총 리소스 양
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResInfo);
		// 리소스가 존재한다.
		std::string Name = GameEngineString::ToUpperReturn(ResInfo.Name);

		// ResInfo

		D3D_SHADER_INPUT_TYPE Type = ResInfo.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 리소스가 상수버퍼라면
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResInfo.Name);

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			// 5번에 세팅되는 
			// ResInfo.BindPoint;

			GameEngineConstantBufferSetter NewSetter;

			// 중복으로 만드는일이 생기면 안되니까.
			// 만든걸 또 만들라고 하는게 
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			NewSetter.Res = GameEngineConstantBuffer::CreateAndFind(Name, BufferDesc);
			NewSetter.BindPoint = ResInfo.BindPoint;
			ConstantBufferMap.insert(std::make_pair(Name, NewSetter));

			break;
		}
		case D3D_SIT_TEXTURE:
		{
			GameEngineTextureSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			NewSetter.Res = GameEngineTexture::Find("NSet.png");
			NewSetter.BindPoint = ResInfo.BindPoint;
			TextureMap.insert(std::make_pair(Name, NewSetter));
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			GameEngineSamplerSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			NewSetter.Res = GameEngineSampler::Find("EngineSamplerLinear");
			NewSetter.BindPoint = ResInfo.BindPoint;
			SamplerMap.insert(std::make_pair(Name, NewSetter));
			break;
		}
		case D3D_SIT_STRUCTURED:
		{
			// 구조적인 특성상 대용량 메모리를 사용하는것이 기본이기 때문에.
			// 미리 만들수도 없어.
			// 스트럭처드 버퍼를 만든다.
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResInfo.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			GameEngineStructuredBufferSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			// 아직은 데이터의 사이즈는 알수있어도 이걸로 몇개짜리 버퍼를 만들지는 알수가 없다.
			NewSetter.Res = GameEngineStructuredBuffer::CreateAndFind(Name, BufferDesc, 0);
			NewSetter.BindPoint = ResInfo.BindPoint;

			StructuredBufferMap.insert(std::make_pair(Name, NewSetter));
			// StructuredBufferMap = 

			break;
		}
		default:
			MsgBoxAssert("아직 처리하지 않은 쉐이더 리소스");
			break;
		}


		// 이 순간 상수버퍼가 만들어져야 합니다.

		int a = 0;

	}

	ConstantBufferMap;
	TextureMap;

	// 상수버는 몇개 쓰는지 크기는 얼마인지 이런것들을 알아내줍니다.
	// CompileInfo

	// CompileInfo->Release();
}

GameEngineConstantBufferSetter& GameEngineShader::GetConstantBufferSetter(std::string _Name)
{
	std::string Name = GameEngineString::ToUpperReturn(_Name);

	if (ConstantBufferMap.end() == ConstantBufferMap.find(Name))
	{
		MsgBoxAssert("존재하지 않는 상수버퍼를 찾으려고 했습니다.");
	}

	return ConstantBufferMap[Name];
}
#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexShader::GameEngineVertexShader() 
	: ShaderPtr(nullptr)
	// , InstancingShaderPtr(nullptr)
{
	ShaderSettingType = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader() 
{
	//if (nullptr != InstancingShaderPtr)
	//{
	//	InstancingShaderPtr->Release();
	//	InstancingShaderPtr = nullptr;
	//}
	//if (nullptr != InstancingShaderPtr)
	//{
	//	InstancingBinaryPtr->Release();
	//	InstancingBinaryPtr = nullptr;
	//}

	if (nullptr != InstancingVertexShader)
	{
		delete InstancingVertexShader;
	}

	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}

}

// Color.hlsl
// 같은 쉐이더파일내에
// 버텍스쉐이더를 2개 작성못합니다.

// Color_VS

void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgBoxAssert("쉐이더 세팅 오류");
	}

	// 두번째 인자는 #include나 #define등 hlsl에서 사용할 헤더나 디파인의 객체를 넣어줄수 있다.
	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}

GameEngineVertexShader* GameEngineVertexShader::Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh /*= 5*/, UINT _VersionLow /*= 0*/)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path), _EntryPoint, _VersionHigh, _VersionLow);
}


GameEngineVertexShader* GameEngineVertexShader::Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
{
	GameEngineVertexShader* NewRes = CreateResName(_Name);
	NewRes->ShaderCompile(_Path, _EntryPoint, _VersionHigh, _VersionLow);

	return NewRes;
}


void GameEngineVertexShader::ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 쉐이더에서는 기본적으로 행렬이 아래와 같이 전치가 되어서 들어가게 되어있는데
	// 1000
	// 0100
	// 2010
	// 0301

	// 1020
	// 0103
	// 0010
	// 0001


	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UnicodePath = GameEngineString::AnsiToUnicodeReturn(_Path);

	// 쉐이더 
	if (D3DCompileFromFile(
		UnicodePath.c_str(), // 파일 경로
		nullptr,  // 매크로 ()
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  // 헤더 ()
		_EntryPoint.c_str(), // 진입점 COLOR_VS(
		Version.c_str(),  // vs_5_0
		Flag,
		0,
		&BinaryPtr,
		&Error)
		)
	{
		std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssertString(ErrorText);
		return;
	}

	// 이미 다 컴파일된 쉐이더 코드의 바이너리를 넣어줘서 생성하는 방식이 됙ㅂ니다.
	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(
		BinaryPtr->GetBufferPointer(),
		BinaryPtr->GetBufferSize(),
		nullptr,
		&ShaderPtr))
	{
		MsgBoxAssert("버텍스 쉐이더 핸들 생성에 실패했습니다.");
	}

	ShaderResCheck();
}

void GameEngineVertexShader::InstancingShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 쉐이더에서는 기본적으로 행렬이 아래와 같이 전치가 되어서 들어가게 되어있는데
	// 1000
	// 0100
	// 2010
	// 0301

	// 1020
	// 0103
	// 0010
	// 0001

	InstancingVertexShader = new GameEngineVertexShader();
	InstancingVertexShader->SetName(_EntryPoint);

	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UnicodePath = GameEngineString::AnsiToUnicodeReturn(_Path);

	// 쉐이더 
	if (D3DCompileFromFile(
		UnicodePath.c_str(), // 파일 경로
		nullptr,  // 매크로 ()
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  // 헤더 ()
		_EntryPoint.c_str(), // 진입점 COLOR_VS(
		Version.c_str(),  // vs_5_0
		Flag,
		0,
		&InstancingVertexShader->BinaryPtr,
		&Error)
		)
	{
		std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssertString(ErrorText);
		return;
	}

	// 이미 다 컴파일된 쉐이더 코드의 바이너리를 넣어줘서 생성하는 방식이 됙ㅂ니다.
	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(
		InstancingVertexShader->BinaryPtr->GetBufferPointer(),
		InstancingVertexShader->BinaryPtr->GetBufferSize(),
		nullptr,
		&InstancingVertexShader->ShaderPtr))
	{
		MsgBoxAssert("버텍스 쉐이더 핸들 생성에 실패했습니다.");
	}

	InstancingVertexShader->ShaderResCheck();

}
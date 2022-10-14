#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <functional>


enum class ShaderType
{
	Vertex,
	Pixel,
	MAX,
};

class GameEngineShader;
class ShaderResSetter : public GameEngineNameObject
{
public:
	GameEngineShader* ParentShader;
	ShaderType ShaderType;
	int BindPoint;
	std::function<void()> SettingFunction;
	std::function<void()> ResetFunction;

public:
	ShaderResSetter() 
		: ShaderType(ShaderType::MAX)
		, BindPoint(-1)
		, ParentShader(nullptr)
	{

	}
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
	friend GameEngineShader;

public:
	GameEngineConstantBuffer* Res;
	// 각자가 가진 정보에 대한 주소
	const void* SetData;
	UINT Size;


	// 자기메모리로 할당할 것이다.
	std::vector<char> OriginalData;

	void Setting() const;

public:
	GameEngineConstantBufferSetter() 
		: Res(nullptr)
		, SetData(nullptr)
		, Size(-1)
	{

	}
};

class GameEngineTexture;
class GameEngineTextureSetter : public ShaderResSetter
{
	friend GameEngineShader;

public:
	void Setting() const;
	void Reset() const;

public:
	GameEngineTexture* Res;
};

class GameEngineSampler;
class GameEngineSamplerSetter : public ShaderResSetter
{
public:
	void Setting() const;

public:
	GameEngineSampler* Res;
};

class GameEngineStructuredBuffer;
class GameEngineStructuredBufferSetter : public ShaderResSetter
{
public:
	void Setting() const;

	void Resize(int _Count);

	template<typename DataType>
	void Push(DataType& _Data, int _Count)
	{
		int LeftSize = sizeof(DataType);
		int RightSize = GetDataSize();

		if (LeftSize != RightSize)
		{
			MsgBoxAssert("구조화버퍼에 넣으려는 데이터 사이즈가 다릅니다.");
		}

		PushData(&_Data, _Count);
	}

	int GetDataSize();

private:
	void PushData(const void* Data, int _Count);

public:
	GameEngineStructuredBuffer* Res;
	std::vector<char> CpuDataBuffer;
};



// 설명 :
class GameEngineShaderResourcesHelper;
class GameEngineShader 
{
	friend GameEngineShaderResourcesHelper;

public:
	static void AutoCompile(const std::string& _Path);

public:
	// constrcuter destructer
	GameEngineShader();
	virtual ~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	GameEngineConstantBufferSetter& GetConstantBufferSetter(std::string _Name);

protected:
	void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);
	void SetEntryPoint(const std::string& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	ID3DBlob* BinaryPtr;

	std::string Version;

	void ShaderResCheck();

	ShaderType ShaderSettingType;

private:
	std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferMap;
	std::map<std::string, GameEngineTextureSetter> TextureMap;
	std::map<std::string, GameEngineSamplerSetter> SamplerMap;
	std::map<std::string, GameEngineStructuredBufferSetter> StructuredBufferMap;

	std::string EntryPoint;

	// std::map<unsigned int, ConstantBuffer> 

	// void SetConstantBuffer() override;

};


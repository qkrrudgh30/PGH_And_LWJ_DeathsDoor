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
	size_t Size;


	// 자기메모리로 할당할 것이다.
	std::vector<char> OriginalData;

	void Setting() const;
	void Bind();


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

	void Bind();

public:
	GameEngineTexture* Res;
};

class GameEngineSampler;
class GameEngineSamplerSetter : public ShaderResSetter
{
public:
	void Setting() const;
	void Bind();
public:
	GameEngineSampler* Res;
};

class GameEngineStructuredBuffer;
class GameEngineStructuredBufferSetter : public ShaderResSetter
{
public:
	void Setting() const;

	void Resize(int _Count);
	void Bind();

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
	// 상수버퍼와 완전히 동일하게 동일하게 생각하면 됩니다.
	GameEngineStructuredBuffer* Res;
	const void* SetData;
	size_t Size;
	std::vector<char> OriginalData;
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

	bool IsTexture(const std::string& _Name);

	bool IsSampler(const std::string& _Name);

	bool IsConstantBuffer(const std::string& _Name);

	bool IsStructuredBuffer(const std::string& _Name);

protected:
	void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);
	void SetEntryPoint(const std::string& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	ID3DBlob* BinaryPtr;

	std::string Version;

	void ShaderResCheck(const std::string_view& _Name);

	ShaderType ShaderSettingType;


private:
	std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferSettingMap;
	std::map<std::string, GameEngineTextureSetter> TextureSettingMap;
	std::map<std::string, GameEngineSamplerSetter> SamplerSettingMap;
	std::map<std::string, GameEngineStructuredBufferSetter> StructuredBufferSettingMap;


	std::string EntryPoint;

	// std::map<unsigned int, ConstantBuffer> 

	// void SetConstantBuffer() override;

};


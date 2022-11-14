#pragma once
#include "GameEnginePath.h"
#include "GameEngineMath.h"

class GameEngineFile;
class Serializer
{
public:
	virtual void Write(GameEngineFile& _File) = 0;
	virtual void Read(GameEngineFile& _File) = 0;
};

enum class OpenMode
{
	Read,
	Write,
};

enum class FileMode
{
	Binary,
	Text,
};

// 설명 :
class GameEngineFile : public GameEnginePath
{
public:
	static uintmax_t GetFileSize(const std::filesystem::path& _Path);

	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const char* _Path);
	GameEngineFile(const std::filesystem::path& _Path);
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	// delete Function
	void Open(OpenMode _Mode, FileMode _Open);

	void Close();

	void Create()
	{
		Open(OpenMode::Write, FileMode::Binary);
		Close();
	}

	void Write(const void* _WriteData, size_t _WriteSize);

	void Write(const std::string& _Text);

	void Write(const float4x4& _Data);

	void Write(const float4& _Data);

	void Write(const double& _Data);

	void Write(const float& _Data);

	template<typename Struct>
	void Write(const Struct& _Data)
	{
		Write(reinterpret_cast<const void*>(&_Data), sizeof(Struct));
	}

	template<typename Value>
	void Write(std::vector<Value>& _Data)
	{
		/*int Size = static_cast<int>(_Data.size());
		Write(&Size, sizeof(int));

		if (Size <= 0)
		{
			return;
		}

		Value* Check = &_Data[0];

		Serializer* Ser = dynamic_cast<Serializer*>(Check);


		for (size_t i = 0; i < _Data.size(); i++)
		{
			if (nullptr == Ser)
			{
				Write(&_Data[i], sizeof(Value));
			}
			else 
			{
				_Data[i].Write(*this);
			}

		}*/

		// Write(reinterpret_cast<const void*>(&_Data), sizeof(Struct));
	}

	// 받는용 버퍼
	void Read(void* _ReadData, size_t _BufferSize, size_t _ReadSize);

	void Read(std::string& _Data);

	void Read(float4x4& _Data);

	void Read(float4& _Data);

	void Read(double& _Data);

	void Read(float& _Data);

	template<typename Struct>
	void Read(Struct& _Data)
	{
		Read(reinterpret_cast<void*>(&_Data), sizeof(Struct), sizeof(Struct));
	}



	std::string GetString();

	uintmax_t GetFileSize() const;


protected:

	


private:
	FILE* FilePtr;
};

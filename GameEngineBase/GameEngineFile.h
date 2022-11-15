#pragma once
#include "GameEnginePath.h"
#include "GameEngineMath.h"

class GameEngineFile;
class GameEngineSerializer
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

	void Write(const unsigned int& _Data);

	template<typename Struct>
	void Write(const Struct& _Data)
	{
		Write(reinterpret_cast<const void*>(&_Data), sizeof(Struct));
	}

	template<typename Value>
	void Write(std::vector<Value>& _Data)
	{
		unsigned int Size = static_cast<unsigned int>(_Data.size());
		Write(Size);

		if (Size <= 0)
		{
			return;
		}

		for (size_t i = 0; i < _Data.size(); i++)
		{
			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
			{
				Write(_Data[i]);
			}
			else 
			{
				GameEngineSerializer* Ser = reinterpret_cast<GameEngineSerializer*>(&_Data[i]);
				Ser->Write(*this);
			}

		}
	}

	template<typename Key, typename  Value>
	void Write(std::map<Key, Value>& _Data)
	{
		unsigned int Size = static_cast<unsigned int>(_Data.size());
		Write(Size);

		if (Size <= 0)
		{
			return;
		}

		for (std::pair<Key, Value> Pair : _Data)
		{
			if (false == std::is_base_of<GameEngineSerializer, Key>::value)
			{
				Write(Pair.first);
			}
			else
			{
				GameEngineSerializer* Ser = reinterpret_cast<GameEngineSerializer*>(&Pair.first);
				Ser->Write(*this);
			}

			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
			{
				Write(Pair.second);
			}
			else
			{
				GameEngineSerializer* Ser = reinterpret_cast<GameEngineSerializer*>(&Pair.second);
				Ser->Write(*this);
			}
		}
	}

	// 받는용 버퍼
	void Read(void* _ReadData, size_t _BufferSize, size_t _ReadSize);

	void Read(std::string& _Data);

	void Read(float4x4& _Data);

	void Read(float4& _Data);

	void Read(double& _Data);

	void Read(float& _Data);

	void Read(unsigned int& _Data);

	template<typename Struct>
	void Read(Struct& _Data)
	{
		Read(reinterpret_cast<void*>(&_Data), sizeof(Struct), sizeof(Struct));
	}

	template<typename Value>
	void Read(std::vector<Value>& _Data)
	{
		unsigned int Size = 0;
		Read(Size);

		if (Size <= 0)
		{
			return;
		}

		_Data.resize(Size);

		for (unsigned int i = 0; i < Size; i++)
		{
			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
			{
				Read(_Data[i]);
			}
			else
			{
				GameEngineSerializer* Ser = reinterpret_cast<GameEngineSerializer*>(&_Data[i]);
				Ser->Read(*this);
			}

		}
	}

	template<typename Key, typename  Value>
	void Read(std::map<Key, Value>& _Data)
	{
		unsigned int Size = 0;
		Read(Size);

		if (Size <= 0)
		{
			return;
		}

		for (unsigned int i = 0; i < Size; ++i)
		{
			std::pair<Key, Value> Pair;

			if (false == std::is_base_of<GameEngineSerializer, Key>::value)
			{
				Read(Pair.first);
			}
			else
			{
				GameEngineSerializer* Ser = reinterpret_cast<GameEngineSerializer*>(&Pair.first);
				Ser->Read(*this);
			}


			if (false == std::is_base_of<GameEngineSerializer, Value>::value)
			{
				Read(Pair.second);
			}
			else
			{
				GameEngineSerializer* Ser = reinterpret_cast<GameEngineSerializer*>(&Pair.second);
				Ser->Read(*this);
			}

			_Data.insert(Pair);
		}
	}

	std::string GetString();

	uintmax_t GetFileSize() const;


protected:

	


private:
	FILE* FilePtr;
};

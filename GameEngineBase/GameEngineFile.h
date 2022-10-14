#pragma once
#include "GameEnginePath.h"

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

	void Write(void* _WriteData, size_t _WriteSize);

	// 받는용 버퍼
	void Read(void* _ReadData, size_t _BufferSize, size_t _ReadSize);

	void Read();

	std::string GetString();

	uintmax_t GetFileSize() const;


protected:

	


private:
	FILE* FilePtr;
};


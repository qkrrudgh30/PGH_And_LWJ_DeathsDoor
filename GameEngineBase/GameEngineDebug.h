#pragma once
#include <crtdbg.h>
#include <string>
#include <assert.h>
#include <Windows.h>


// 설명 :
namespace GameEngineDebug
{
//public:
	void LeakCheckOn();
	void ConsoleOpen();

	void OutPutString(const std::string& _Text);

	void Destroy();

// protected:

// private:
	// static HANDLE hConsole;
	// constrcuter destructer
	//GameEngineDebug();
	//~GameEngineDebug();

	//// delete Function
	//GameEngineDebug(const GameEngineDebug& _Other) = delete;
	//GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	//GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	//GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

};

#define MsgBox(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK);  

#define MsgBoxAssert(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK); \
assert(false); 

#define MsgBoxAssertString(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK); \
assert(false); 

//namespace GameEngineDebug
//{
//	// 새기능
//};
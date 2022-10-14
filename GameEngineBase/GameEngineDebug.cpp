#include "PreCompile.h"
#include "GameEngineDebug.h"
#include <iostream>


namespace GameEngineDebug
{
	HANDLE hConsole = nullptr;
	//GameEngineDebug::GameEngineDebug() 
	//{
	//}
	//
	//GameEngineDebug::~GameEngineDebug() 
	//{
	//}

	void LeakCheckOn()
	{
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	}

	void ConsoleOpen()
	{

		if (AllocConsole())
		{
			FILE* FIle;
			freopen_s(&FIle, "CONIN$", "rb", stdin);
			freopen_s(&FIle, "CONOUT$", "wb", stdout);
			freopen_s(&FIle, "CONOUT$", "wb", stderr);

			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::cout << "Console Start" << std::endl;
		}
	}

	//void GameEngineDebug::MsgBoxAssert(const std::string& _Text)
	//{
	//	MessageBeep(0); 
	//	MessageBoxA(nullptr, _Text.c_str(), "Error", MB_OK); 
	//	assert(false);
	//	// 그냥 자기자신으로 띄웁니다.
	//	// 윈도우 핸들 넣어달라고 합니다
	//	// 니가 만든거면
	//	// 안넣어주면 알아서 window를 하나 만들어준다.
	//	
	//	
	//}

	void OutPutString(const std::string& _Text)
	{
		// #ifdef _DEBUG
		OutputDebugStringA((_Text + "\n").c_str());
		// #endif
	}

	void Destroy()
	{
		if (nullptr != hConsole)
		{
			FreeConsole();
		}
	}

}
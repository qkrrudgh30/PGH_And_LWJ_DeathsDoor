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

	void GetLastErrorPrint()
	{
		DWORD error = GetLastError();
		char* message = nullptr;

		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&message,
			0,
			nullptr);

		if (nullptr != message)
		{
			std::string Text = "Code : ";
			Text += std::to_string(error);
			Text += " Message : ";
			Text += message;

			MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK);
			// 운영체제가 준건 해제헤야 한다.
			// 서버면 더더더더더더욱
			// 실행중 발생하는 릭이 가장 위험하다.
			// 힙이 비대해지기 시작합니다.
			// 램을 초과하면서 터진다.
			LocalFree(message);
		}
	}
}
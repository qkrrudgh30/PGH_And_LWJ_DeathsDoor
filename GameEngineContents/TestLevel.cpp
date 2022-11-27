#include "PreCompile.h"
#include "TestLevel.h"
#include "Hall.h"
#include "ContentsBlur.h"
#include "TestActor.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start() 
{
}

void TestLevel::LevelStartEvent()
{
#pragma region LoadFBXMeshiesAndAnimation
	if (false == mbPrimitiveInitialized)
	{
		LoadCreaturesFromFile("08_TestLevel");
		mbPrimitiveInitialized = true;
	}
#pragma endregion

	CreateActor<Hall>(); 
	CreateActor<TestActor>(); 

	ContentsBlur::GetBlurInstance();
	// GEngine::GetCurrentLevel()->GetUICamera()->GetCameraRenderTarget()->AddEffect<ContentsBlur>();

}

void TestLevel::Update(float _DeltaTime) 
{
}

void TestLevel::End() {}

#include "PreCompile.h"
#include "TestLevel.h"
#include "Hall.h"
#include "ContentsBlur.h"

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

	CreateActor<Hall>(); // Test Code.

	msptrContentsBlur = GetMainCamera()->GetCameraRenderTarget()->AddEffect<ContentsBlur>();
	// msptrContentsBlur->SetBlurInfo(BlurType::eVerticalAndHorizontal, 0u);

}

void TestLevel::Update(float _DeltaTime) 
{
	int a = 100;
}

void TestLevel::End() {}

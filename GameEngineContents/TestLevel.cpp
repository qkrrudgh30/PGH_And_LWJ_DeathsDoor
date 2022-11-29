#include "PreCompile.h"
#include "TestLevel.h"
#include "Hall.h"
#include "ContentsBlur.h"
#include "ContentsBloom.h"
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

#pragma region EngineCode
	ContentsBlur::GetBlurInstance();
	ContentsBloom::GetBloomInstance();
#pragma endregion

	
	// GEngine::GetCurrentLevel()->GetUICamera()->GetCameraRenderTarget()->AddEffect<ContentsBlur>();

}

void TestLevel::Update(float _DeltaTime) 
{

#pragma region EngineCode

	msptrBlurCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());
	msptrBloomCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());

#pragma endregion

}

void TestLevel::End() {}

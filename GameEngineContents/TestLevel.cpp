#include "PreCompile.h"
#include "TestLevel.h"
#include "Hall.h"
#include "ContentsBlur.h"
#include "ContentsBloom.h"
#include "TestActor.h"
#include "TestStaticActor.h"
#include "WorldLight.h"

#include "TestBox.h"
#include "TestSphere.h"

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
	CreateActor<TestStaticActor>();

	CreateActor<TestBox>()->GetTransform().SetLocalMove(float4{ -600.f, 400.f, -100.f, 0.f });
	CreateActor<TestSphere>()->GetTransform().SetLocalMove(float4{ -100.f, 400.f, 0.f, 0.f });

	// CreateActor<TestActor>()->GetTransform().SetLocalMove(float4{ 100.f, 100.f, 100.f, 0.f });



	if (Player::GetMainPlayer())
	{
		Player::GetMainPlayer()->On();
	}
	 
#pragma region EngineCode
	msptrContentsBlur->InitializeContentsBlur(msptrContentsBlur);
	msptrContentsBloom->InitializeBloom(msptrContentsBloom);
#pragma endregion

	
	// GEngine::GetCurrentLevel()->GetUICamera()->GetCameraRenderTarget()->AddEffect<ContentsBlur>();

}

void TestLevel::Update(float _DeltaTime) 
{
	ContentsLevel::Update(_DeltaTime);

#pragma region EngineCode

	msptrBlurCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());
	msptrBloomCameraActor->GetTransform().Copy(GEngine::GetCurrentLevel()->GetMainCameraActorTransform());

#pragma endregion

}

void TestLevel::End() {}

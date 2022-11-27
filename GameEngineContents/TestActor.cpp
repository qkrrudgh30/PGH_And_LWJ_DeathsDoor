#include "PreCompile.h"
#include "TestActor.h"
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>


TestActor::TestActor()
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	std::shared_ptr<GameEngineFBXAnimationRenderer> FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();

	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 50.f, 50.f, 50.f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ -90.f, 180.f,0.f });
	FBXAnimationRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 100.f, 0.f });
	FBXAnimationRenderer->SetFBXMesh("Player.fbx", "TextureAnimation");
	FBXAnimationRenderer->ChangeCamera(CAMERAORDER::USER0);
	

	Event.ResourcesName = "Player_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.1f;
	FBXAnimationRenderer->CreateFBXAnimation("Player_Idle", Event);

	FBXAnimationRenderer->ChangeAnimation("Player_Idle");

	std::shared_ptr<GameEngineTextureRenderer> sptrTestPicture = CreateComponent<GameEngineTextureRenderer>();
	sptrTestPicture->SetTexture("TestPicture.png");
	sptrTestPicture->ScaleToTexture();
	sptrTestPicture->GetTransform().SetLocalScale({ 500, 500, 1 });
	sptrTestPicture->GetTransform().SetLocalRotation({ 0.f,0.f,-30.f });
	sptrTestPicture->GetTransform().SetLocalPosition({ -1500.f,1500.f, -250.f });
	sptrTestPicture->ChangeCamera(CAMERAORDER::MAINCAMERA);
}

void TestActor::Update(float _DeltaTime)
{
	
}


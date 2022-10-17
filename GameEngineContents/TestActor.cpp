#include "PreCompile.h"
#include "TestActor.h"

TestActor::TestActor()
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
}

void TestActor::Update(float _DeltaTime)
{
}


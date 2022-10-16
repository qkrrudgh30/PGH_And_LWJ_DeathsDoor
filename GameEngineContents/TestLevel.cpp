#include "PreCompile.h"
#include "TestLevel.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Start()
{
}

void TestLevel::Update(float _DeltaTime)
{
	GetMainCameraActor()->FreeCameraModeOnOff();
}

void TestLevel::End()
{
}

void TestLevel::LevelStartEvent()
{

}

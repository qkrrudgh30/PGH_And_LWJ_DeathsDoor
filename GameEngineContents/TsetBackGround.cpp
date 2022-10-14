#include "PreCompile.h"
#include "TsetBackGround.h"

TsetBackGround::TsetBackGround() 
{
}

TsetBackGround::~TsetBackGround() 
{
}

void TsetBackGround::Start()
{

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetWorldScale({ 1000.f,1000.f,1000.f });
		Renderer->GetTransform().SetWorldRotation({90.f, 0.f, 0.f});

	}
	

}
void TsetBackGround::Update(float _DeltaTime)
{
}
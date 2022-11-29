#include "PreCompile.h"
#include "SnapTarGet.h"

SnapTarGet::SnapTarGet() 
{
}

SnapTarGet::~SnapTarGet() 
{
}

void SnapTarGet::Start()
{

	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("target.png");
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 10.f });
		TexRenderer->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}



}

void SnapTarGet::Update(float _DeltaTime)
{

	TexRenderer->GetTransform().SetLocalRotate({0.f, 150.f * _DeltaTime, 0.f});


	m_fTime += _DeltaTime;

	if (m_fTime >= 3.f)
		Death();
}


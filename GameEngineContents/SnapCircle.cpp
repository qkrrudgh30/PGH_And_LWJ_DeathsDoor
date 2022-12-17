#include "PreCompile.h"
#include "SnapCircle.h"
#include "WaveRenderer.h"

SnapCircle::SnapCircle() 
{
}

SnapCircle::~SnapCircle() 
{
}

void SnapCircle::Start()
{
	float4 color = { 1.f,0.f,0.f,0.4f };

	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("Circle.png");
	TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 10.f });
	
	TexRenderer->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
	TexRenderer->GetPixelData().MulColor = color;
}

void SnapCircle::Update(float _DeltaTime)
{
	m_fScale += _DeltaTime * 20000.f;
	
	
	
	TexRenderer->GetTransform().SetLocalScale({ m_fScale ,m_fScale ,10.f});

	if (1.f < GetAccTime())
	{
		Death();
	}
}


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
	float4 color = { 1.f,0.f,0.f,1.f };

	m_wptrWaveRenderer = CreateComponent<WaveRenderer>();
	m_wptrWaveRenderer.lock()->SetTexture("Circle.png");
	m_wptrWaveRenderer.lock()->GetTransform().SetLocalScale({ 100.f, 100.f, 10.f });
	m_wptrWaveRenderer.lock()->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
	m_wptrWaveRenderer.lock()->GetPixelData().MulColor = color;
}

void SnapCircle::Update(float _DeltaTime)
{
	m_fScale += _DeltaTime * 20000.f;
	
	
	
	m_wptrWaveRenderer.lock()->GetTransform().SetLocalScale({ m_fScale ,m_fScale ,10.f});

	if (1.f < GetAccTime())
	{
		Death();
	}
}


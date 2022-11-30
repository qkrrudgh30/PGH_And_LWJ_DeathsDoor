

#include "PreCompile.h"
#include "LaserTarget.h"

LaserTarget::LaserTarget()
{
}

LaserTarget::~LaserTarget()
{
}

void LaserTarget::Start()
{

	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("target.png");
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 10.f });
		TexRenderer->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	GetTransform().SetWorldPosition(PlayerPos);



}

void LaserTarget::Update(float _DeltaTime)
{

	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

	float4 MyPos = GetTransform().GetWorldPosition();



	float4 LerpPos = float4::Lerp(MyPos, PlayerPos, _DeltaTime * 2.f);

	LerpPos.y = 10.f;

	GetTransform().SetWorldPosition(LerpPos);



	m_fTime += _DeltaTime;

}


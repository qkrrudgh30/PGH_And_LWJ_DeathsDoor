#include "PreCompile.h"
#include "PlayerShadow.h"

PlayerShadow::PlayerShadow() 
{
}

PlayerShadow::~PlayerShadow() 
{
}

void PlayerShadow::Start()
{


	TexRenderer = CreateComponent<GameEngineTextureRenderer>();
	TexRenderer->SetTexture("Shadow.png");
	TexRenderer->GetTransform().SetLocalScale({ 50.f, 50.f, 10.f });
	TexRenderer->SetRenderingOrder(10);
	TexRenderer->GetTransform().SetLocalRotation({ 90.f,0.f,0.f });
	TexRenderer->GetPixelData().MulColor.a = 0;





}

void PlayerShadow::Update(float _DeltaTime)
{
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	PlayerPos.y = 11.f;
	GetTransform().SetWorldPosition(PlayerPos);

}


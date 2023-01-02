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


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 2000.f, 400.0f, 300.f });
	AttCollision->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);



}

void SnapCircle::Update(float _DeltaTime)
{
	m_fScale += _DeltaTime * 20000.f;
	

	AttCollision->GetTransform().SetWorldBackMove(10000.f, _DeltaTime);


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&SnapCircle::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);
	
	TexRenderer->GetTransform().SetLocalScale({ m_fScale ,m_fScale ,10.f});

	if (1.f < GetAccTime())
	{
		Death();
	}
}

CollisionReturn SnapCircle::PlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	Player::GetMainPlayer()->m_bHitBackCheck = true;


	return CollisionReturn::Break;
}


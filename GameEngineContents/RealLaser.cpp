


#include "PreCompile.h"
#include "RealLaser.h"
#include"GameEngineBase/GameEngineRandom.h"

RealLaser::RealLaser()
{
}

RealLaser::~RealLaser()
{
}

void RealLaser::Start()
{

	m_fSpeed = 1200.f;


	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		
		TexRenderer->SetTexture("LightningBoltTexture.png");
		TexRenderer->SetPivot(PIVOTMODE::LEFT);
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 1.f });
		TexRenderer->GetTransform().SetLocalRotation({ 45.f,135.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}

	
	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		
		TexRenderer2->SetTexture("LightningBoltTexture.png");
		TexRenderer2->SetPivot(PIVOTMODE::LEFT);
		TexRenderer2->GetTransform().SetLocalScale({ 2000.f, 100.f, 1.f });
		TexRenderer2->GetTransform().SetLocalRotation({ 135.f,135.f,0.f });
		TexRenderer2->GetPixelData().MulColor = color;

	}

	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 380.f, 400.0f, 4000.f });
	AttCollision->GetTransform().SetLocalRotation({ -0.f,45.f,0.f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);
	



}

void RealLaser::Update(float _DeltaTime)
{

	if (m_bScalecheck)
	{
		


		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
			std::bind(&RealLaser::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
		);




		float RandomF = GameEngineRandom::MainRandom.RandomFloat(0, 400.f);

		TexRenderer->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });
		TexRenderer2->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });

	}
	else
	{
		float RandomF = GameEngineRandom::MainRandom.RandomFloat(0, 10.f);

		TexRenderer->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });
		TexRenderer2->GetTransform().SetLocalScale({ 2000.f, RandomF, 1.f });


	}
	

	
}

CollisionReturn RealLaser::PlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{

	Player::GetMainPlayer()->m_bHitBackCheck = true;


	return CollisionReturn::Break;
}

//-436  218  43



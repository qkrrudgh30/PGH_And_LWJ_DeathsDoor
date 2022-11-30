

#include "PreCompile.h"
#include "SnapBullet.h"
#include "SnapTarGet.h"

#pragma region TestCode

#include "SnapCircle.h"

#pragma endregion


SnapBullet::SnapBullet()
{
}

SnapBullet::~SnapBullet()
{
}

void SnapBullet::Start()
{
	m_Info.Dammage = 1;



	{
		
		float4 color = { 1.f,0.f,0.f, 1.f };

	
		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("BulletTest.png");
		//TexRenderer->ScaleToTexture();
		TexRenderer->GetTransform().SetLocalScale({ 40.f, 70.f, 10.f });
		TexRenderer->GetPixelData().MulColor = color;

	}


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 40.0f, 40.0f, 40.0f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);
	AttCollision->Off();

}

void SnapBullet::Update(float _DeltaTime)
{


	

	GetTransform().SetWorldDownMove(1000.f, _DeltaTime);



	float4 TarGetDir = m_pTarget.lock()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	float Len = TarGetDir.Length();

	if (Len <= 40.f)
	{

		AttCollision->On();

		AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Player), CollisionType::CT_OBB,
		std::bind(&SnapBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2));
	}


	if (Len <= 20.f)
	{

		m_pTarget.lock()->Death();
		m_pTarget.reset();

		Death();

	}


}

CollisionReturn SnapBullet::PlayerCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{
	if (m_pTarget.lock())
	{
		m_pTarget.lock()->Death();
		m_pTarget.reset();
	}


	Death();


	return CollisionReturn::Break;

}


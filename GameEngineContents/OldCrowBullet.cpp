
#include "PreCompile.h"
#include "OldCrowBullet.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"
OldCrowBullet::OldCrowBullet()
{
}

OldCrowBullet::~OldCrowBullet()
{
}

void OldCrowBullet::Start()
{

	m_fSpeed = 3000.f;


	{

		float4 color = { 0.1f,0.1f,0.1f,1.f };
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 1.5f, 1.5f, 1.5f });
		FBXStaticRenderer->GetTransform().SetLocalRotation(float4{ 90.f, 0.f, 0.f });
		FBXStaticRenderer->SetFBXMesh("SmallCrow.FBX", "PreviousColor");
		FBXStaticRenderer->GetAllRenderUnit()[0][0].ShaderResources.SetConstantBufferLink("ResultColor", color);

	}



	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 10.f, 500.0f, 10.0f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);

	m_fSpeed = 1000.f;


	Death(15.f);
}

void OldCrowBullet::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;
	if (m_fLifeTime >= 10.f)
	{
		Death();
	}


	if (m_bAttCheck  == false)
	{
		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::PlayerAtt, CollisionType::CT_OBB,
			std::bind(&OldCrowBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
		);


		float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
		float4 MyPos = GetTransform().GetWorldPosition();

		PlayerPos.y = 50.f;
		MyPos.y = 50.f;


		float4 TarGetDir = (PlayerPos - MyPos).Normalize3DReturn();

		float4 MoveDir = GetTransform().GetForwardVector();


		float4 Cross = float4::Cross3D(MoveDir, TarGetDir);

		// ¿ÞÂÊ 
		if (Cross.y > 0)
		{
			GetTransform().SetAddWorldRotation(float4(0.0f, 160.f * _DeltaTime, 0.0f));
		}
		// ¿À¸¥ÂÊ
		else
		{
			GetTransform().SetAddWorldRotation(float4(0.0f, -160.f * _DeltaTime, 0.0f));
		}


		GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);

	}
	else
	{

		AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
			std::bind(&OldCrowBullet::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
		);



			GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);


	}







}

CollisionReturn OldCrowBullet::MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= 1000;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_MaxHp = std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp;


	Death();


	return CollisionReturn::Break;
}

CollisionReturn OldCrowBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	MoveDir = Player::GetMainPlayer()->FBXAnimationRenderer->GetTransform().GetForwardVector();


	float AttAngle = DirToRot(MoveDir, GetTransform().GetWorldPosition());

	GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });



	m_bAttCheck = true;
	m_fSpeed = 3000.f;





	return CollisionReturn::Break;
}


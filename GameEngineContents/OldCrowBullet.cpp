
#include "PreCompile.h"
#include "OldCrowBullet.h"
#include "OldCrowFog.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"
#include"GameEngineBase/GameEngineRandom.h"

OldCrowBullet::OldCrowBullet()
{
}

OldCrowBullet::~OldCrowBullet()
{



	for (size_t i = 0; i < m_vOldCrowFog.size(); i++)
	{
		m_vOldCrowFog[i]->Death();
	}





}

void OldCrowBullet::Start()
{

	m_fSpeed = 3000.f;



	{

		float4 color = { 0.1f,0.1f,0.1f,1.f };
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 1.f, 1.f, 1.f });
		FBXStaticRenderer->GetTransform().SetLocalRotation(float4{ 90.f, 0.f, 0.f });
		FBXStaticRenderer->SetFBXMesh("SmallCrow.FBX", "PreviousColor");
		FBXStaticRenderer->GetAllRenderUnit()[0][0]->ShaderResources.SetConstantBufferLink("ResultColor", color);

	}

	for (size_t i = 0; i < 10; i++)
	{
		std::shared_ptr < OldCrowFog> Bullet = GetLevel()->CreateActor<OldCrowFog>(OBJECTORDER::Eff);
		float4 MyPos = GetTransform().GetWorldPosition();
		Bullet->GetTransform().SetWorldPosition(MyPos);
		float m_fScaleMax = GameEngineRandom::MainRandom.RandomFloat(40.f, 60.f);
		Bullet->m_fScaleMax = m_fScaleMax;
		Bullet->m_fStartPos = MyPos;

		m_vOldCrowFog.push_back(Bullet);

	}


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 10.f, 500.0f, 10.0f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);

	m_fSpeed = 500.f;


	Death(15.f);
}

void OldCrowBullet::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;


	for (size_t i = 0; i < m_vOldCrowFog.size(); i++)
	{
	
		float4 MyPos = GetTransform().GetWorldPosition();
		m_vOldCrowFog[i]->m_fStartPos = (MyPos);
	
	
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
	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("03-2_PlayerParryingAttackHitted.mp3");

	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= 1000;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_MaxHp = std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp;



	for (size_t i = 0; i < m_vOldCrowFog.size(); i++)
	{
		m_vOldCrowFog[i]->Death();
	}


	Death();


	return CollisionReturn::Break;
}

CollisionReturn OldCrowBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{
	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("03-1_PlayerParryingAttack.mp3");

	MoveDir = Player::GetMainPlayer()->FBXAnimationRenderer->GetTransform().GetForwardVector();
	float4 PlayerPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();

	float AttAngle = DirToRot(PlayerPos + MoveDir * 100.f , PlayerPos );

	GetTransform().SetLocalRotation({ 0.0f,AttAngle, 0.0f });



	m_bAttCheck = true;
	m_fSpeed = 3000.f;



	for (size_t i = 0; i < m_vOldCrowFog.size(); i++)
	{
		m_vOldCrowFog[i]->ChangeColorBlue();
	}


	return CollisionReturn::Break;
}


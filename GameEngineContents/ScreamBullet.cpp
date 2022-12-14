


#include "PreCompile.h"
#include "ScreamBullet.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "SWEffMgr.h"


ScreamBullet::ScreamBullet()
{
}

ScreamBullet::~ScreamBullet()
{
}

void ScreamBullet::Start()
{

	m_fSpeed = 3000.f;


	{

		// float4 color = { 0.1f,0.1f,0.1f,1.f };
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
		FBXStaticRenderer->GetTransform().SetLocalRotation(float4{ 90.f, 0.f, 0.f });
		FBXStaticRenderer->SetFBXMesh("SmallCrow.FBX", "PreviousColor");
		FBXStaticRenderer->GetAllRenderUnit()[0][0].ShaderResources.SetConstantBufferLink("ResultColor", float4{ 0.1f, 0.1f, 0.1f, 1.f });
	}



	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 10.f, 500.0f, 10.0f });
	AttCollision->ChangeOrder(OBJECTORDER::MonsterAtt);

	m_fSpeed = 800.f;


	Death(15.f);
}

void ScreamBullet::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;

	if (m_fLifeTime >= 1.f)
	{


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

		float4 MoveDir = GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);
	}


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::PlayerAtt, CollisionType::CT_OBB,
		std::bind(&ScreamBullet::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	);





}

CollisionReturn ScreamBullet::MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{

	std::weak_ptr < SWEffMgr> Bullet = GEngine::GetCurrentLevel()->CreateActor<SWEffMgr>(OBJECTORDER::Eff);

	Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());


	Death();
	return CollisionReturn::Break;
}


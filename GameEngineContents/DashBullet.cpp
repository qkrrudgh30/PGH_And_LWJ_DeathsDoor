

#include "PreCompile.h"
#include "DashBullet.h"
#include "DashTrail.h"
#include "OldCrow.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
DashBullet::DashBullet()
{
}

DashBullet::~DashBullet()
{
}

void DashBullet::Start()
{

	m_fSpeed = 4000.f;

	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 1.f, 1.f });
		FBXStaticRenderer->SetFBXMesh("Arrow.FBX", "Texture");


	}



	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 500.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerHook);



}

void DashBullet::Update(float _DeltaTime)
{



	if (m_OldCorw.lock() == nullptr)
	{
		Death();
		return;

	}

	float4 TarGetPos = m_OldCorw.lock()->GetTransform().GetWorldPosition();
	float4 myPos = GetTransform().GetWorldPosition();


	float Len = (TarGetPos - myPos).Length();

	m_ftrailTime += _DeltaTime;

	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&DashBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);

	float4 MoveDir = GetTransform().GetForwardVector();



	if (m_ftrailTime >= 0.005f)
	{
		if (Len >= 150.f)
		{
			m_ftrailTime -= 0.005f;
			std::weak_ptr< DashTrail> HookTrail = GetLevel()->CreateActor<DashTrail>(OBJECTORDER::PlayerHookTrail);
			HookTrail.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			HookTrail.lock()->GetTransform().SetLocalRotation(GetTransform().GetLocalRotation());
			HookTrail.lock()->m_cHook = std::dynamic_pointer_cast<DashBullet>(shared_from_this());
			HookTrail.lock()->m_OldCorw = m_OldCorw;


		}
		
	
	}

	if(!m_bGoCheck)
	{
		if (Len <= 3500.f)
		{
			GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);
			
		}
		else
		{
			m_OldCorw.lock()->DashStartCheck = true;
			m_bGoCheck = true;
		}
	}
	else
	{

		if (Len <= 70.f)
		{
			
			m_OldCorw.lock()->DashEndCheck = true;


		}

	}

	



}



CollisionReturn DashBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	return CollisionReturn::Break;
}


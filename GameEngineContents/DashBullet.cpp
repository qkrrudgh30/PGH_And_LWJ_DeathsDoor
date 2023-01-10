

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
	int A = 0;
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

	float4 MoveDir = GetTransform().GetForwardVector();








	if(!m_bGoCheck)
	{
		if (Len <= 3500.f)
		{
			GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);
			

			if (Len >= 150.f)
			{
  				std::weak_ptr< DashTrail> HookTrail = GetLevel()->CreateActor<DashTrail>(OBJECTORDER::CrowDash);
				HookTrail.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				HookTrail.lock()->GetTransform().SetLocalRotation(GetTransform().GetLocalRotation());
				HookTrail.lock()->m_cHook = std::dynamic_pointer_cast<DashBullet>(shared_from_this());
				HookTrail.lock()->m_OldCorw = m_OldCorw;
				
			}


		}
		else
		{
			m_OldCorw.lock()->DashStartCheck = true;
			m_bGoCheck = true;
		}
	}
	else
	{

		if (Len <= 150.f)
		{
			
			m_OldCorw.lock()->DashEndCheck = true;


		}

	}

	



}



CollisionReturn DashBullet::PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	return CollisionReturn::Break;
}


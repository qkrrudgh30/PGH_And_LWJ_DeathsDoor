#include "PreCompile.h"
#include "StaticMesh.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

StaticMesh::StaticMesh() 
	: mpFBXStaticRenderer(nullptr)
	, mpCollider(nullptr)
	, mbPriorityInitialzed(true)
	, mbWithCollision(true)
{
}

StaticMesh::~StaticMesh() 
{
}

void StaticMesh::Start()
{
	mpFBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
	
	mpCollider = CreateComponent<GameEngineCollision>();
	mpCollider->ChangeOrder(OBJECTORDER::StaticMesh);

}

void StaticMesh::Update(float _DeltaTime)
{
	if (!m_bRenderOncheck)
	{
		m_bRenderOncheck = true;
		float4 CheckScale = GetTransform().GetLocalScale();
		if (CheckScale.x == 1 && CheckScale.y == 1 && CheckScale.z == 1)
		{
			mpFBXStaticRenderer->Off();
		}

	}
	



	if (false == mbPriorityInitialzed)
	{
		if (true == mbWithCollision)
		{
			
			// mpCollider->GetTransform().SetLocalScale(GetTransform().GetLocalScale());
			
		}
		
		mbPriorityInitialzed = true;
	}


	//mpCollider->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
	//	std::bind(&StaticMesh::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);


	if (true == mpCollider->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB))
	{
		Player* mainPlayer = Player::GetMainPlayer();
		float PlayerSpeed = 0.f;

		if (mainPlayer->StateManager.GetCurStateStateName() == "Slide")
		{
			PlayerSpeed = mainPlayer->m_fSlideSpeed;

		}
		else if (mainPlayer->StateManager.GetCurStateStateName() == "HookAtt")
		{
			PlayerSpeed = mainPlayer->m_fSpeed;

		}
		else if (mainPlayer->StateManager.GetCurStateStateName() == "Move")
		{
			PlayerSpeed = mainPlayer->Speed;

		}
		else
		{
			PlayerSpeed = 200.f;

		}

		mainPlayer->GetMainPlayer()->GetTransform().SetWorldMove(-(mainPlayer->m_fStaticCollDir) * PlayerSpeed * _DeltaTime);

	}


}

CollisionReturn StaticMesh::PlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	Player* mainPlayer = Player::GetMainPlayer();
	float PlayerSpeed = 0.f;
	if (mainPlayer->StateManager.GetCurStateStateName() == "Slide")
	{
		PlayerSpeed = mainPlayer->m_fSlideSpeed;

	}
	else if (mainPlayer->StateManager.GetCurStateStateName() == "HookAtt")
	{
		PlayerSpeed = mainPlayer->m_fSpeed;

	}
	else if (mainPlayer->StateManager.GetCurStateStateName() == "Move")
	{
		PlayerSpeed = mainPlayer->Speed;

	}


	//float4 PlayerPos = 

	float4 CollDir = Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	CollDir = CollDir.Normalize3DReturn();
	//GetTransform().SetWorldMove(CollDir * PlayerSpeed * _DeltaTime);

	return CollisionReturn::ContinueCheck;
}


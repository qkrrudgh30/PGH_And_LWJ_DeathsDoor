#include "PreCompile.h"
#include "Elevator.h"
#include "ContentsLevel.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

Elevator::Elevator()
{
}

Elevator::~Elevator()
{
}

void Elevator::Start()
{
	m_fSpeed = 500.f;

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 500.0f, 500.0f, 500.0f });
	Collision->ChangeOrder(OBJECTORDER::MoveStatic);

	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.45f, 0.45f, 0.45f });
		FBXStaticRenderer->GetTransform().SetLocalRotation({ 0.f, 0.f, 0.f });
		FBXStaticRenderer->SetFBXMesh("Elevator.FBX", "Texture");
	}

}

void Elevator::Update(float _DeltaTime)
{

	if (true == Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB))
	{
		m_fColTime += _DeltaTime;

		if (m_fColTime >= 3.f)
		{
			//플레이어 위치 고정 && 내려가기


			GetTransform().SetWorldDownMove(m_fSpeed,_DeltaTime);

			Player::GetMainPlayer()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());

		}

	}
	else
	{ 
		m_fColTime = 0.f;


	}

}

CollisionReturn Elevator::CollisionPlayer(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{

	return CollisionReturn::ContinueCheck;
}


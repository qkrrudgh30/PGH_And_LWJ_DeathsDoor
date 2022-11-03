
#include "PreCompile.h"
#include "Potal.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>

Potal::Potal()
{
}

Potal::~Potal()
{
}

void Potal::Start()
{


	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::NPC);



	{
		FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
		FBXRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXRenderer->GetTransform().SetLocalScale(float4{ 0.25f, 0.25f, 0.25f });
		FBXRenderer->GetTransform().SetLocalRotation({ 0.f, 45.f, 0.f });
		{
			FBXRenderer->SetFBXMesh("woodDoor.FBX", "Texture");
		}
		
	}


}

void Potal::Update(float _DeltaTime)
{

	Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&Potal::CollisionPlayer, this, std::placeholders::_1, std::placeholders::_2)
	);


}

CollisionReturn Potal::CollisionPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	 

	if (m_PotalType == PotalType::LoginToStage1)
	{
		GEngine::ChangeLevel("Hunting1");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}
	if (m_PotalType == PotalType::Stage1ToStage2)
	{
		GEngine::ChangeLevel("Hunting2");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage2ToStage3)
	{
		GEngine::ChangeLevel("Hunting3");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage3ToStage4)
	{
		GEngine::ChangeLevel("Hunting4");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage4ToStage5)
	{
		GEngine::ChangeLevel("Hunting5");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage5ToStageBoss)
	{
		GEngine::ChangeLevel("Boss");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage5ToStage4)
	{
		GEngine::ChangeLevel("Hunting4");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage4ToStage3)
	{
		GEngine::ChangeLevel("Hunting3");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage3ToStage2)
	{
		GEngine::ChangeLevel("Hunting2");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage2ToStage1)
	{
		GEngine::ChangeLevel("Hunting1");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage1ToSLogin)
	{
		GEngine::ChangeLevel("Login");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}




	return CollisionReturn::ContinueCheck;
}


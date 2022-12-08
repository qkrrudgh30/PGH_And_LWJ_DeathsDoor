#include "PreCompile.h"
#include "PlayerSWAtt3.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
PlayerSWAtt3::PlayerSWAtt3()
{
}

PlayerSWAtt3::~PlayerSWAtt3()
{
}

void PlayerSWAtt3::Start()
{

	m_Info.Dammage = 2;
	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 150.0f, 500.0f, 150.0f });
	AttCollision->GetTransform().SetLocalPosition(AttCollision->GetTransform().GetForwardVector() * 100.f);

	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);
	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.35f, 0.35f, 0.35f });
		FBXStaticRenderer->SetFBXMesh("Sworld_Trail_2.fbx", "StaticPaperBurn");
		FBXStaticRenderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
		// FBXStaticRenderer->GetAllRenderUnit()[0][0].GetCloneMaterial()->SetOutputMergerBlend("Lighten");

#pragma region StaticPaperBurn

		InitializePaperBurn(FBXStaticRenderer);
		m_fAccTimeForPaperburn = 0.f;
		mfPaperburnDeathTime = 5.f;

#pragma endregion


	}


}

void PlayerSWAtt3::Update(float _DeltaTime)
{

	//AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
	//	std::bind(&PlayerSWAtt3::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);



	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Monster), CollisionType::CT_OBB,
		std::bind(&PlayerSWAtt3::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	);

	

#pragma region StaticPaperBurn
	m_fAccTimeForPaperburn += _DeltaTime * mfPaperburnDeathTime;
	SetPaperBurnInfo(1u, m_fAccTimeForPaperburn);
#pragma endregion	
}

CollisionReturn PlayerSWAtt3::MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{

	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_bHitCheck = true;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_fHitPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_bHitActionCheck = true;


	return CollisionReturn::Break;

}


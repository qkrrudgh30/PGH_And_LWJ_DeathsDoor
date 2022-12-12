#include "PreCompile.h"
#include "PlayerSWAttSlide.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
PlayerSWAttSlide::PlayerSWAttSlide()
{
}

PlayerSWAttSlide::~PlayerSWAttSlide()
{
}

void PlayerSWAttSlide::Start()
{


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 50.0f, 500.0f, 150.0f });
	AttCollision->GetTransform().SetLocalPosition(AttCollision->GetTransform().GetForwardVector() * 100.f);

	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	
	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
		FBXStaticRenderer->SetFBXMesh("Sworld_Trail_3.fbx", "StaticPaperBurn");
		// FBXStaticRenderer->GetAllRenderUnit()[0][0].GetCloneMaterial()->SetOutputMergerBlend("Lighten");
		
#pragma region StaticPaperBurn

		InitializePaperBurn(FBXStaticRenderer);
		m_fAccTimeForPaperburn = 0.f;
		mfPaperburnDeathTime = 5.f;

#pragma endregion

	}



}

void PlayerSWAttSlide::Update(float _DeltaTime)
{



	//AttCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
	//	std::bind(&PlayerSWAttSlide::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);


	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Monster), CollisionType::CT_OBB,
		std::bind(&PlayerSWAttSlide::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



#pragma region StaticPaperBurn
	m_fAccTimeForPaperburn += _DeltaTime * mfPaperburnDeathTime;
	SetPaperBurnInfo(1u, m_fAccTimeForPaperburn);
#pragma endregion	
}

CollisionReturn PlayerSWAttSlide::MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{


	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_bHitActionCheck = true;



	return CollisionReturn::Break;
}


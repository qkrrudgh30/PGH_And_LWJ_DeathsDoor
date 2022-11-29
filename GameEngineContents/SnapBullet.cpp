

#include "PreCompile.h"
#include "SnapBullet.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>


SnapBullet::SnapBullet()
{
}

SnapBullet::~SnapBullet()
{
}

void SnapBullet::Start()
{
	m_Info.Dammage = 1;



	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
		FBXStaticRenderer->SetFBXMesh("Sworld_Trail_4.fbx", "Texture");

	}



	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 50.0f });
	AttCollision->GetTransform().SetLocalPosition(AttCollision->GetTransform().GetForwardVector() * 100.f);
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);


}

void SnapBullet::Update(float _DeltaTime)
{

	

	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB, static_cast<int>(OBJECTORDER::Player), CollisionType::CT_OBB,
		std::bind(&SnapBullet::PlayerCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



}

CollisionReturn SnapBullet::PlayerCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{


	

	return CollisionReturn::Break;

}


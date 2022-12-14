
#include "PreCompile.h"
#include "PlayerArrowAtt.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "ArrowEffMgr.h"

PlayerArrowAtt::PlayerArrowAtt() 
{
}

PlayerArrowAtt::~PlayerArrowAtt()
{
}

void PlayerArrowAtt::Start()
{

	m_fSpeed = 3000.f;


	//{


	//	Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//	Renderer->SetPipeLine("Color");
	//	Renderer->GetRenderUnit().SetMesh("Box");
	//	float4 ResultColor = { 1.f,1.f,1.f,1.f };

	//	Renderer->GetTransform().SetLocalScale({ 20.f, 20.0f, 50.0f });
	//	Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);

	//}

	//float4 ResultColor = float4{ 0.9f, 0.9f, 0.9f, 1.f };

	//{
	//	FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
	//	FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
	//	FBXStaticRenderer->SetFBXMesh("Arrow.fbx", "Color");
	//	FBXStaticRenderer->GetAllRenderUnit()[0][0].ShaderResources.SetConstantBufferLink("ResultColor", ResultColor);


	//}





	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 1.f, 1.f });
		FBXStaticRenderer->SetFBXMesh("Arrow.FBX", "Texture");
		

	}



	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 20.f, 500.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);



}

void PlayerArrowAtt::Update(float _DeltaTime)
{

	m_fLifeTime += _DeltaTime;

	if (m_fLifeTime >= 2.f)
	{
		Death();
	}


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		std::bind(&PlayerArrowAtt::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	);


	AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::StaticMesh, CollisionType::CT_OBB,
		std::bind(&PlayerArrowAtt::StaticCollision, this, std::placeholders::_1, std::placeholders::_2)
	);



	float4 MoveDir = FBXStaticRenderer->GetTransform().GetForwardVector();
	GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);

}

CollisionReturn PlayerArrowAtt::MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{

	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("07-1_PlayerBowHitted.mp3");

	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_bHitCheck = true;
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_fHitPos = Player::GetMainPlayer()->GetTransform().GetWorldPosition();
	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_bHitActionCheck = true;
	
	
	std::weak_ptr < ArrowEffMgr> Bullet = GEngine::GetCurrentLevel()->CreateActor<ArrowEffMgr>(OBJECTORDER::Eff);

	Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());


	Death();
	return CollisionReturn::Break;
}

CollisionReturn PlayerArrowAtt::StaticCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{

	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("07-1_PlayerBowHitted.mp3");



	std::weak_ptr < ArrowEffMgr> Bullet = GEngine::GetCurrentLevel()->CreateActor<ArrowEffMgr>(OBJECTORDER::Eff);

	Bullet.lock()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());



	Death();
	return CollisionReturn::Break;


}

#include "PreCompile.h"
#include "Potal.h"
#include "ContentsLevel.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

Potal::Potal()	:
	m_PotalType()
{
}

Potal::~Potal()
{
}

void Potal::Start()
{
	m_fSpeed = 2000.f;

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::NPC);



	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
		FBXStaticRenderer->GetTransform().SetLocalRotation({ 0.f, 45.f, 0.f });

		for (size_t i = 0; i <= 23; ++i)
		{
			if (6 != i)
			{
				FBXStaticRenderer->SetFBXMesh("Door.FBX", "Texture", i);
			}
			else
			{
				FBXStaticRenderer->SetFBXMesh("Door.FBX", "Color", i);
				FBXStaticRenderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::RED);
				// FBXStaticRenderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4{0.6f, 0.06f, 0.11f, 1.f});
			}
		}
		
	}


}

void Potal::Update(float _DeltaTime)
{

	Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Player, CollisionType::CT_OBB,
		std::bind(&Potal::CollisionPlayer, this, std::placeholders::_1, std::placeholders::_2)
	);



	float Len = (Player::GetMainPlayer()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition()).Length();

	float4 MyPos = FBXStaticRenderer->GetTransform().GetWorldPosition();
	if (Len >= 400.f)
	{


		if (MyPos.y <= 0.f)
		{
			MyPos.y = 0.f;

			FBXStaticRenderer->GetTransform().SetWorldPosition(MyPos);

			m_fSpeed = 2000.f;
		}
		else
		{

			m_fSpeed += 1500.f * _DeltaTime;

			FBXStaticRenderer->GetTransform().SetWorldDownMove(m_fSpeed, _DeltaTime);
		}

	}
	else
	{
		if (MyPos.y >= 1000.f)
		{
			MyPos.y = 1000.f;
			FBXStaticRenderer->GetTransform().SetWorldPosition(MyPos);

			m_fSpeed = 2000.f;
		}
		else
		{

			m_fSpeed += 1500.f * _DeltaTime;


			FBXStaticRenderer->GetTransform().SetWorldUpMove(m_fSpeed, _DeltaTime);
		}

	}





}

CollisionReturn Potal::CollisionPlayer(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{
	 
	// 포탈 충돌 > 다음레벨설정 or 이전레벨설정 > EditLevel > 다음레벨에셋준비 or 안함 > 다음레벨이동
	if (m_PotalType == PotalType::LoginToStage1)
	{
		ContentsLevel::mstrNextLevelName = "01_HuntingLevel1";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}
	if (m_PotalType == PotalType::Stage1ToStage2)
	{
		ContentsLevel::mstrNextLevelName = "02_HuntingLevel2";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage2ToStage3)
	{
		ContentsLevel::mstrNextLevelName = "03_HuntingLevel3";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage3ToStage4)
	{
		ContentsLevel::mstrNextLevelName = "05_HuntingLevel5";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage4ToStage5)
	{
		ContentsLevel::mstrNextLevelName = "05_HuntingLevel5";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage5ToStageBoss)
	{
		ContentsLevel::mstrNextLevelName = "06_BossLevel";
		ContentsLevel::mstrPrevLevelName = "05_HuntingLevel5";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage5ToStage4)
	{
		ContentsLevel::mstrNextLevelName = "Previous";
		ContentsLevel::mstrPrevLevelName = "03_HuntingLevel3";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage4ToStage3)
	{
		ContentsLevel::mstrNextLevelName = "Previous";
		ContentsLevel::mstrPrevLevelName = "03_HuntingLevel3";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage3ToStage2)
	{
		ContentsLevel::mstrNextLevelName = "Previous";
		ContentsLevel::mstrPrevLevelName = "02_HuntingLevel2";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage2ToStage1)
	{
		ContentsLevel::mstrNextLevelName = "Previous";
		ContentsLevel::mstrPrevLevelName = "01_HuntingLevel1";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}

	if (m_PotalType == PotalType::Stage1ToSLogin)
	{
		ContentsLevel::mstrNextLevelName = "Previous";
		ContentsLevel::mstrPrevLevelName = "00_LoginLevel";
		GEngine::ChangeLevel("07_EditLevel");
		Player::GetMainPlayer()->GetTransform().SetWorldPosition({ 0.F,0.F,-100.F });
	}


	m_structSoundPlayer.Stop();
	m_structSoundPlayer = GameEngineSound::SoundPlayControl("02_Portal.mp3");

	return CollisionReturn::ContinueCheck;
}


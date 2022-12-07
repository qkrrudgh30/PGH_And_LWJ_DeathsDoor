#include "PreCompile.h"
#include "PlayerSWAtt1.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
// #include <>


PlayerSWAtt1::PlayerSWAtt1() 
{
}

PlayerSWAtt1::~PlayerSWAtt1() 
{
}

void PlayerSWAtt1::Start()
{
	m_Info.Dammage = 1;



	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
		FBXStaticRenderer->SetFBXMesh("Sworld_Trail_4.fbx", "StaticPaperBurn");
		FBXStaticRenderer->ChangeCamera(CAMERAORDER::MAINCAMERA);
		
		// FBXStaticRenderer->GetAllRenderUnit()[0][0].GetCloneMaterial()->SetOutputMergerBlend("TransparentBlend");

#pragma region StaticPaperBurn

		InitializePaperBurn(FBXStaticRenderer);
		m_fAccTimeForPaperburn = 0.f;
		mfPaperburnDeathTime = 5.f;

#pragma endregion

		
		

		//static bool bOnce = false;
		//if (false == bOnce)
		//{
			// std::shared_ptr<GameEngineMaterial> sptrMaterial = GameEngineMaterial::Create("Lighten");
			// sptrMaterial->Copy(FBXStaticRenderer->GetAllRenderUnit()[0][0].GetMaterial());
			// sptrMaterial->SetOutputMergerBlend("Lighten");
			// bOnce = true;
		//}
		// FBXStaticRenderer->GetAllRenderUnit()[0][0].SetPipeLine("Lighten");

		// FBXStaticRenderer->GetAllRenderUnit()[0][0].ShaderResources.SetConstantBufferLink("TRANSFORMDATA", FBXStaticRenderer->GetTransformData());
		// FBXStaticRenderer->GetAllRenderUnit()[0][0].ShaderResources.SetConstantBufferLink("RENDEROPTION", FBXStaticRenderer->RenderOptionInst);
	}

	

	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 120.0f, 500.0f, 120.0f });
	AttCollision->GetTransform().SetLocalPosition(AttCollision->GetTransform().GetForwardVector()* 100.f);
	AttCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
	AttCollision->SetCollisionMode(CollisionMode::Ex);


}

void PlayerSWAtt1::Update(float _DeltaTime)
{

	//AttCollision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
	//	std::bind(&PlayerSWAtt1::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);

	AttCollision->IsCollisionEnterBase(CollisionType::CT_OBB,static_cast<int>(OBJECTORDER::Monster), CollisionType::CT_OBB,
		std::bind(&PlayerSWAtt1::MonsterCollision,this, std::placeholders::_1, std::placeholders::_2)
	);

#pragma region StaticPaperBurn
	m_fAccTimeForPaperburn += _DeltaTime * mfPaperburnDeathTime;
	SetPaperBurnInfo(1u, m_fAccTimeForPaperburn);
#pragma endregion	
}

CollisionReturn PlayerSWAtt1::MonsterCollision(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other)
{


	std::dynamic_pointer_cast<UnitBase>(_Other->GetParent())->m_Info.m_Hp -= m_Info.Dammage;


	return CollisionReturn::Break;
	
}


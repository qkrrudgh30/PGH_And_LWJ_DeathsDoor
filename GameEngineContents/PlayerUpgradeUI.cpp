#include "PreCompile.h"
#include "PlayerUpgradeUI.h"

PlayerUpgradeUI::PlayerUpgradeUI() 
{
}

PlayerUpgradeUI::~PlayerUpgradeUI() 
{
}

void PlayerUpgradeUI::Start()
{


	GameEngineInput::GetInst()->CreateKey("UIMouseClick", VK_LBUTTON);


	//왼쪽 틀
	{
		GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("upgrade_bg.png");
		Renderer->GetTransform().SetLocalScale({ 400.f, 400.f, 1 });
		Renderer->GetTransform().SetLocalPosition({ -200.f,0.f, -220.f });
		Renderer->GetPixelData().MulColor.a = 0.5f;
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}


	//오른쪽 틀
	{
		GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture("Info Frame.png");
		Renderer->GetTransform().SetLocalScale({ 300.f, 400.f, 1 });
		Renderer->GetPixelData().MulColor.a = 0.5f;
		Renderer->GetTransform().SetLocalPosition({ 300.f,0.f, -220.f });
		Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	}




	//무기 종류 2개씩 4개 
	//칼
	{
		RendererSword = CreateComponent<GameEngineUIRenderer>();
		RendererSword->SetTexture("cutCursor.png");
		RendererSword->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererSword->GetTransform().SetLocalPosition({ -320.f,140.f, -200.f });
		RendererSword->ChangeCamera(CAMERAORDER::UICAMERA);
	}


	{
		RendererSwordBack = CreateComponent<GameEngineUIRenderer>();
		RendererSwordBack->SetTexture("upgrade_ability_box.png");
		RendererSwordBack->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererSwordBack->GetTransform().SetLocalPosition({ -320.f,140.f, -200.f });
		RendererSwordBack->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererSwordBack->GetPixelData().MulColor.a = 0.5f;
	}


	//화살
	{
		RendererArrow = CreateComponent<GameEngineUIRenderer>();
		RendererArrow->SetTexture("Icon_Arrow.png");
		RendererArrow->ScaleToTexture();
		RendererArrow->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererArrow->GetTransform().SetLocalPosition({ -320.f,50.f, -200.f });
		RendererArrow->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererArrow->GetPixelData().MulColor.a = 0.5f;
	}

	{
		RendererArrowBack = CreateComponent<GameEngineUIRenderer>();
		RendererArrowBack->SetTexture("upgrade_ability_box.png");
		RendererArrowBack->ScaleToTexture();
		RendererArrowBack->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererArrowBack->GetTransform().SetLocalPosition({ -320.f,50.f, -200.f });
		RendererArrowBack->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererArrowBack->GetPixelData().MulColor.a = 0.5f;
	}

	//후크
	{
		RendererHook = CreateComponent<GameEngineUIRenderer>();
		RendererHook->SetTexture("Icon_Hook.png");
		RendererHook->ScaleToTexture();
		RendererHook->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHook->GetTransform().SetLocalPosition({ -320.f,-40.f, -200.f });
		RendererHook->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererHook->GetPixelData().MulColor.a = 0.5f;
	}

	{
		RendererHookBack = CreateComponent<GameEngineUIRenderer>();
		RendererHookBack->SetTexture("upgrade_ability_box.png");
		RendererHookBack->ScaleToTexture();
		RendererHookBack->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererHookBack->GetTransform().SetLocalPosition({ -320.f,-40.f, -200.f });
		RendererHookBack->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHookBack->GetPixelData().MulColor.a = 0.5f;
	}


	//마법
	{
		RendererFire = CreateComponent<GameEngineUIRenderer>();
		RendererFire->SetTexture("Icon_Fireball.png");
		RendererFire->ScaleToTexture();
		RendererFire->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererFire->GetTransform().SetLocalPosition({ -320.f,-130.f, -200.f });
		RendererFire->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererFire->GetPixelData().MulColor.a = 0.5f;
	}

	{
		RendererFireBack = CreateComponent<GameEngineUIRenderer>();
		RendererFireBack->SetTexture("upgrade_ability_box.png");
		RendererFireBack->ScaleToTexture();
		RendererFireBack->GetTransform().SetLocalScale({ 100, 100, 1 });
		RendererFireBack->GetTransform().SetLocalPosition({ -320.f,-130.f, -200.f });
		RendererFireBack->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererFireBack->GetPixelData().MulColor.a = 0.5f;
	}


	for (int i = 0; i < 5; ++i)
	{


		RendererSwordUpBack[i] = CreateComponent<GameEngineUIRenderer>();
		RendererSwordUpBack[i]->SetTexture("upgrade_slot_empty-1.png");
		RendererSwordUpBack[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererSwordUpBack[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),140.f, -200.f });
		RendererSwordUpBack[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererArrowUpBack[i]->Off();


		RendererSwordUp[i] = CreateComponent<GameEngineUIRenderer>();
		RendererSwordUp[i]->SetTexture("upgrade_slot_glow-1.png");
		RendererSwordUp[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererSwordUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),140.f, -190.f });
		RendererSwordUp[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererSwordUp[i]->Off();


		CollisionSwordUp[i] = CreateComponent<GameEngineCollision>();
		CollisionSwordUp[i]->GetTransform().SetLocalScale({ 30.f,30.f,1.f });
		CollisionSwordUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),140.f,-10.f });
		CollisionSwordUp[i]->ChangeOrder(OBJECTORDER::UI);




		RendererArrowUpBack[i] = CreateComponent<GameEngineUIRenderer>();
		RendererArrowUpBack[i]->SetTexture("upgrade_slot_empty-1.png");
		RendererArrowUpBack[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererArrowUpBack[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),50.f, -200.f});
		RendererArrowUpBack[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererArrowUpBack[i]->Off();


		RendererArrowUp[i] = CreateComponent<GameEngineUIRenderer>();
		RendererArrowUp[i]->SetTexture("upgrade_slot_glow-1.png");
		RendererArrowUp[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererArrowUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),50.f, -190.f });
		RendererArrowUp[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererArrowUp[i]->Off();

		CollisionArrowUp[i] = CreateComponent<GameEngineCollision>();
		CollisionArrowUp[i]->GetTransform().SetLocalScale({ 30.f,30.f,1.f });
		CollisionArrowUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),50.f,-10.f });
		CollisionArrowUp[i]->ChangeOrder(OBJECTORDER::UI);





		RendererHookUpBack[i] = CreateComponent<GameEngineUIRenderer>();
		RendererHookUpBack[i]->SetTexture("upgrade_slot_empty-1.png");
		RendererHookUpBack[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHookUpBack[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-40.f, -200.f });
		RendererHookUpBack[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererArrowUpBack[i]->Off();


		RendererHookUp[i] = CreateComponent<GameEngineUIRenderer>();
		RendererHookUp[i]->SetTexture("upgrade_slot_glow-1.png");
		RendererHookUp[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererHookUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-40.f, -190.f });
		RendererHookUp[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererHookUp[i]->Off();

		CollisionHookUp[i] = CreateComponent<GameEngineCollision>();
		CollisionHookUp[i]->GetTransform().SetLocalScale({ 30.f,30.f,1.f });
		CollisionHookUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-40.f,-10.f });
		CollisionHookUp[i]->ChangeOrder(OBJECTORDER::UI);




		RendererFireUpBack[i] = CreateComponent<GameEngineUIRenderer>();
		RendererFireUpBack[i]->SetTexture("upgrade_slot_empty-1.png");
		RendererFireUpBack[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererFireUpBack[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-130.f, -200.f });
		RendererFireUpBack[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		//RendererArrowUpBack[i]->Off();


		RendererFireUp[i] = CreateComponent<GameEngineUIRenderer>();
		RendererFireUp[i]->SetTexture("upgrade_slot_glow-1.png");
		RendererFireUp[i]->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererFireUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-130.f, -190.f });
		RendererFireUp[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		RendererFireUp[i]->Off();

		CollisionFireUp[i] = CreateComponent<GameEngineCollision>();
		CollisionFireUp[i]->GetTransform().SetLocalScale({ 30.f,30.f,1.f });
		CollisionFireUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-130.f,-10.f });
		CollisionFireUp[i]->ChangeOrder(OBJECTORDER::UI);







	}


}

void PlayerUpgradeUI::Update(float _DeltaTime)
{


	if (true == GameEngineInput::GetInst()->IsPress("UIMouseClick"))
	{

		//칼

		CollisionSwordUp[0]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionSword1, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionSwordUp[1]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionSword2, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionSwordUp[2]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionSword3, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionSwordUp[3]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionSword4, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionSwordUp[4]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionSword5, this, std::placeholders::_1, std::placeholders::_2)
		);




		//화살

		CollisionArrowUp[0]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionArrowUp1, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionArrowUp[1]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionArrowUp2, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionArrowUp[2]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionArrowUp3, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionArrowUp[3]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionArrowUp4, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionArrowUp[4]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionArrowUp5, this, std::placeholders::_1, std::placeholders::_2)
		);



		//후크

		CollisionHookUp[0]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionHookUp1, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionHookUp[1]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionHookUp2, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionHookUp[2]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionHookUp3, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionHookUp[3]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionHookUp4, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionHookUp[4]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionHookUp5, this, std::placeholders::_1, std::placeholders::_2)
		);


		//불

		CollisionFireUp[0]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionFireUp1, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionFireUp[1]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionFireUp2, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionFireUp[2]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionFireUp3, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionFireUp[3]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionFireUp4, this, std::placeholders::_1, std::placeholders::_2)
		);

		CollisionFireUp[4]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
			std::bind(&PlayerUpgradeUI::CollisionFireUp5, this, std::placeholders::_1, std::placeholders::_2)
		);


	}



}


//화살

CollisionReturn PlayerUpgradeUI::CollisionArrowUp1(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (false == RendererArrowUp[0]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererArrowUp[0]->On();

		}


	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionArrowUp2(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererArrowUp[0]->IsUpdate() && false == RendererArrowUp[1]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererArrowUp[1]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionArrowUp3(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == RendererArrowUp[1]->IsUpdate() && false == RendererArrowUp[2]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererArrowUp[2]->On();

		}

	}


	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionArrowUp4(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == RendererArrowUp[2]->IsUpdate() && false == RendererArrowUp[3]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererArrowUp[3]->On();

		}

	}
	
	
	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionArrowUp5(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererArrowUp[3]->IsUpdate() && false == RendererArrowUp[4]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererArrowUp[4]->On();

		}

	}

		

	return CollisionReturn::Break;
}

//칼



CollisionReturn PlayerUpgradeUI::CollisionSword1(GameEngineCollision* _This, GameEngineCollision* _Other)
{



	if (false == RendererSwordUp[0]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererSwordUp[0]->On();

		}


	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionSword2(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererSwordUp[0]->IsUpdate() && false == RendererSwordUp[1]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererSwordUp[1]->On();

		}

	}




	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionSword3(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == RendererSwordUp[1]->IsUpdate() && false == RendererSwordUp[2]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererSwordUp[2]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionSword4(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == RendererSwordUp[2]->IsUpdate() && false == RendererSwordUp[3]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererSwordUp[3]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionSword5(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == RendererSwordUp[3]->IsUpdate() && false == RendererSwordUp[4]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererSwordUp[4]->On();

		}

	}

	return CollisionReturn::Break;
}



//후크


CollisionReturn PlayerUpgradeUI::CollisionHookUp1(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (false == RendererHookUp[0]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererHookUp[0]->On();

		}


	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionHookUp2(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererHookUp[0]->IsUpdate() && false == RendererHookUp[1]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererHookUp[1]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionHookUp3(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == RendererHookUp[1]->IsUpdate() && false == RendererHookUp[2]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererHookUp[2]->On();

		}

	}


	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionHookUp4(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == RendererHookUp[2]->IsUpdate() && false == RendererHookUp[3]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererHookUp[3]->On();

		}

	}


	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionHookUp5(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererHookUp[3]->IsUpdate() && false == RendererHookUp[4]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererHookUp[4]->On();

		}

	}

	return CollisionReturn::Break;
}


//불
CollisionReturn PlayerUpgradeUI::CollisionFireUp1(GameEngineCollision* _This, GameEngineCollision* _Other)
{



	if (false == RendererFireUp[0]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererFireUp[0]->On();

		}


	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionFireUp2(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererFireUp[0]->IsUpdate() && false == RendererFireUp[1]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererFireUp[1]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionFireUp3(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererFireUp[1]->IsUpdate() && false == RendererFireUp[2]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererFireUp[2]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionFireUp4(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererFireUp[2]->IsUpdate() && false == RendererFireUp[3]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererFireUp[3]->On();

		}

	}

	return CollisionReturn::Break;
}


CollisionReturn PlayerUpgradeUI::CollisionFireUp5(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == RendererFireUp[3]->IsUpdate() && false == RendererFireUp[4]->IsUpdate())
	{
		if (m_Player->m_Info.Gold >= 150)
		{
			m_Player->m_Info.Gold -= 150;

			RendererFireUp[4]->On();

		}

	}

	return CollisionReturn::Break;
}
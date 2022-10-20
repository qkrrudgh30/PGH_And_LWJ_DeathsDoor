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
		CollisionSwordUp[i]->GetTransform().SetLocalScale({ 50.f,50.f,1.f });
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
		CollisionArrowUp[i]->GetTransform().SetLocalScale({ 50.f,50.f,1.f });
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
		CollisionHookUp[i]->GetTransform().SetLocalScale({ 50.f,50.f,1.f });
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
		CollisionFireUp[i]->GetTransform().SetLocalScale({ 50.f,50.f,1.f });
		CollisionFireUp[i]->GetTransform().SetLocalPosition({ -250.f + (i * 50.f),-130.f,-10.f });
		CollisionFireUp[i]->ChangeOrder(OBJECTORDER::UI);







	}


}

void PlayerUpgradeUI::Update(float _DeltaTime)
{



	CollisionSwordUp[0]->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::MouseUI, CollisionType::CT_OBB2D,
		std::bind(&PlayerUpgradeUI::CollisionArrowUp1, this, std::placeholders::_1, std::placeholders::_2)
	);





}




CollisionReturn PlayerUpgradeUI::CollisionArrowUp1(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (true == GameEngineInput::GetInst()->IsPress("UIMouseClick"))
	{

		int a = 0;
	}

	return CollisionReturn::Break;
}


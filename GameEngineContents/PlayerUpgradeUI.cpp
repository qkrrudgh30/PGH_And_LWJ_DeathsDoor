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





}

void PlayerUpgradeUI::Update(float _DeltaTime)
{
}


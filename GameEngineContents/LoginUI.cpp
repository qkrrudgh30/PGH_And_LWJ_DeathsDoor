#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

LoginUI::LoginUI()
	: TimeAngle(0.0f)
	, m_ILevelType(0)
	, m_ILevelTypeCheck(0)
	, m_bButtoncheck(false)
	, RendererButton1()
	, RendererButton2()
	, FontPlay()
	, FontEdit()
	, m_fPlayPos2()
	, m_fPlayPos1()
	, m_fEditPos1()
	, m_fEditPos2()
{
}

LoginUI::~LoginUI()
{
}


void LoginUI::Start()
{

	//DeathDoorName

	if (false == GameEngineInput::GetInst()->IsKey("LevelselectButton"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelselectButton", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("LevelUpButton", VK_UP);
		GameEngineInput::GetInst()->CreateKey("LevelDownButton", VK_DOWN);
	}



	{
		std::shared_ptr < GameEngineUIRenderer > RendererLogo = CreateComponent<GameEngineUIRenderer>();
		RendererLogo->SetTexture("DeathDoorlogo.png");
		RendererLogo->ScaleToTexture();
		RendererLogo->GetTransform().SetLocalScale({ 500, 300, 1 });
		RendererLogo->GetTransform().SetLocalPosition({ 0.f,100.f, -250.f });
		RendererLogo->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererButton1 = CreateComponent<GameEngineUIRenderer>();
		RendererButton1->SetTexture("ClickButton.png");
		RendererButton1->ScaleToTexture();
		RendererButton1->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererButton1->GetTransform().SetLocalPosition({ -100.f,-200.f, -250.f });
		RendererButton1->GetTransform().SetLocalRotation({ 0.f,0.f,-90.f });
		RendererButton1->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererButton2 = CreateComponent<GameEngineUIRenderer>();
		RendererButton2->SetTexture("ClickButton.png");
		RendererButton2->ScaleToTexture();
		RendererButton2->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererButton2->GetTransform().SetLocalPosition({ 100.f,-200.f, -250.f });
		RendererButton2->GetTransform().SetLocalRotation({ 0.f,0.f,90.f });
		RendererButton2->ChangeCamera(CAMERAORDER::UICAMERA);

	}


	m_fPlayPos1 = { -100.f,-200.f, -250.f };
	m_fEditPos1 = { -100.f,-250.f, -250.f };

	m_fPlayPos2 = { 100.f,-200.f, -250.f };
	m_fEditPos2 = { 100.f,-250.f, -250.f };


	{
		FontPlay = CreateComponent<GameEngineUIRenderer>();
		FontPlay->SetTexture("Start.png");
		FontPlay->ScaleToTexture();
		FontPlay->GetTransform().SetLocalScale({ 150, 50, 1 });
		FontPlay->GetTransform().SetLocalPosition({ 0.f,-200.f, -250.f });
		FontPlay->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
		FontPlay->ChangeCamera(CAMERAORDER::UICAMERA);

	}


	{
		FontEdit = CreateComponent<GameEngineUIRenderer>();
		FontEdit->SetTexture("Exit.png");
		FontEdit->ScaleToTexture();
		FontEdit->GetTransform().SetLocalScale({ 150, 50, 1 });
		FontEdit->GetTransform().SetLocalPosition({ 0.f,-250.f, -250.f });
		FontEdit->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
		FontEdit->ChangeCamera(CAMERAORDER::UICAMERA);

	}




	//{
	//	FontPlay = CreateComponent<GameEngineFontRenderer>();
	//	FontPlay->SetRenderingOrder(10000);
	//	FontPlay->SetText("Playddddd", "¸¼À½");
	//	FontPlay->SetColor({ 1.0f, 0.0f, 1.0f, 1.f });
	//	FontPlay->SetSize(100);
	//	FontPlay->SetScreenPostion({ 200, 500 });
	//	FontPlay->ChangeCamera(CAMERAORDER::UICAMERA);

	//}

	//{
	//	FontEdit = CreateComponent<GameEngineFontRenderer>();
	//	FontEdit->SetRenderingOrder(10000);
	//	FontEdit->SetText("Edit", "Starcraft");
	//	FontEdit->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });
	//	FontEdit->SetSize(20);
	//	FontEdit->SetScreenPostion({ 350.f, -80.f });
	//	FontEdit->ChangeCamera(CAMERAORDER::UICAMERA);

	//}


}

void LoginUI::Update(float _DeltaTime)
{

	if (true == GameEngineInput::GetInst()->IsPress("LevelselectButton"))
	{

	
		if (m_ILevelType == 0)
		{

			Player* NewPlayer = Player::GetMainPlayer();
			NewPlayer->UIOn();
			NewPlayer->m_bLogoLevelCheck = false;

			GetLevel()->GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
			GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });
	

			Off();
		}
		else
		{
			GEngine::ChangeLevel("Edit");
		}
		m_ILevelType = 0;
		m_ILevelTypeCheck = 0;
		RendererButton2->GetTransform().SetLocalPosition({ 100.f,-200.f, -250.f });
		RendererButton1->GetTransform().SetLocalPosition({ -100.f,-200.f, -250.f });


	}

	if (true == GameEngineInput::GetInst()->IsPress("LevelUpButton") 
		&& true == GameEngineInput::GetInst()->IsFree("LevelDownButton"))
	{

		if (!m_bButtoncheck)
		{


			
				m_bButtoncheck = true;
				m_ILevelType = 0;
				

			
		}
		else
		{
			if (m_ILevelTypeCheck == m_ILevelType)
			{
				m_bButtoncheck = false;
			}

		}
			

	}


	if (true == GameEngineInput::GetInst()->IsPress("LevelDownButton")
		&& true == GameEngineInput::GetInst()->IsFree("LevelUpButton"))
	{
		if (!m_bButtoncheck)
		{

			
				m_bButtoncheck = true;
				m_ILevelType = 1;
		

		
		}
		else
		{
			if (m_ILevelTypeCheck == m_ILevelType)
			{
				m_bButtoncheck = false;
			}

		}
		
	}


	if (m_ILevelTypeCheck != m_ILevelType)
	{
		if (m_ILevelType == 0)
		{

			
		
			float4 StartPos1 = RendererButton1->GetTransform().GetLocalPosition();
			float4 StartPos2 = RendererButton2->GetTransform().GetLocalPosition();

			float4 LerpPos1 = float4::Lerp(StartPos1, m_fPlayPos1, _DeltaTime * 10.f);
			float4 LerpPos2 = float4::Lerp(StartPos2, m_fPlayPos2, _DeltaTime * 10.f);
			RendererButton1->GetTransform().SetLocalPosition(LerpPos1);
			RendererButton2->GetTransform().SetLocalPosition(LerpPos2);


			if (m_fPlayPos1.y + 5.f  >= StartPos1.y  && m_fPlayPos1.y - 5.f <= StartPos1.y )
			{
				m_ILevelTypeCheck = 0;
				m_ILevelType = 0;
				m_bButtoncheck = false;
			}


		}
		else
		{
			float4 StartPos1 = RendererButton1->GetTransform().GetLocalPosition();
			float4 StartPos2 = RendererButton2->GetTransform().GetLocalPosition();

			float4 LerpPos1 = float4::Lerp(StartPos1, m_fEditPos1, _DeltaTime * 10.f);
			float4 LerpPos2 = float4::Lerp(StartPos2, m_fEditPos2, _DeltaTime * 10.f);
			RendererButton1->GetTransform().SetLocalPosition(LerpPos1);
			RendererButton2->GetTransform().SetLocalPosition(LerpPos2);


			if (m_fEditPos1.y + 5.f >= StartPos1.y && m_fEditPos1.y - 5.f <= StartPos1.y)
			{
				m_ILevelTypeCheck = 1;
				m_ILevelTypeCheck = 1;
				m_bButtoncheck = false;
			}
		}

	}





}

void LoginUI::End()
{
	
}





 
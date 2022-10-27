#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

LoginUI::LoginUI()
	: TimeAngle(0.0f)
	, m_ILevelType(0)
	, m_ILevelTypeCheck(0)
	, m_bButtoncheck(false)
{
}

LoginUI::~LoginUI()
{
}


void LoginUI::Start()
{

	if (false == GameEngineInput::GetInst()->IsKey("LevelselectButton"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelselectButton", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("LevelUpButton", VK_UP);
		GameEngineInput::GetInst()->CreateKey("LevelDownButton", VK_DOWN);
	}




	{
		RendererButton1 = CreateComponent<GameEngineUIRenderer>();
		RendererButton1->SetTexture("ClickButton.png");
		RendererButton1->ScaleToTexture();
		RendererButton1->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererButton1->GetTransform().SetLocalPosition({ -450.f,-200.f, -250.f });
		RendererButton1->GetTransform().SetLocalRotation({ 0.f,0.f,-90.f });
		RendererButton1->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererButton2 = CreateComponent<GameEngineUIRenderer>();
		RendererButton2->SetTexture("ClickButton.png");
		RendererButton2->ScaleToTexture();
		RendererButton2->GetTransform().SetLocalScale({ 50, 50, 1 });
		RendererButton2->GetTransform().SetLocalPosition({ -250.f,-200.f, -250.f });
		RendererButton2->GetTransform().SetLocalRotation({ 0.f,0.f,90.f });
		RendererButton2->ChangeCamera(CAMERAORDER::UICAMERA);

	}


	m_fPlayPos1 = { -450.f,-200.f, -250.f };
	m_fEditPos1 = { -450.f,-250.f, -250.f };

	m_fPlayPos2 = { -250.f,-200.f, -250.f };
	m_fEditPos2 = { -250.f,-250.f, -250.f };



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
			GEngine::ChangeLevel("Test");
		}
		else
		{
			GEngine::ChangeLevel("Edit");
		}
		m_ILevelType = 0;
		m_ILevelTypeCheck = 0;
		RendererButton2->GetTransform().SetLocalPosition({ -250.f,-200.f, -250.f });
		RendererButton1->GetTransform().SetLocalPosition({ -450.f,-200.f, -250.f });


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


	//if (m_ILevelType == 0)
	//{
	//	RendererButton1->GetTransform().SetLocalPosition({ -450.f,-200.f, -250.f });
	//	RendererButton2->GetTransform().SetLocalPosition({ -250.f,-200.f, -250.f });

	//}
	//else if (m_ILevelType == 1)
	//{
	//	RendererButton1->GetTransform().SetLocalPosition({ -450.f,-250.f, -250.f });
	//	RendererButton2->GetTransform().SetLocalPosition({ -250.f,-250.f, -250.f });
	//}




}

void LoginUI::End()
{
	
}
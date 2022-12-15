
#include "PreCompile.h"
#include "OldCrowUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

OldCrowUI::OldCrowUI()
	: TimeAngle(0.0f)
	, m_bButtoncheck(false)
	, RendererButton1()
	, RendererButton2()
{
}

OldCrowUI::~OldCrowUI()
{
}


void OldCrowUI::Start()
{


	


	{
		RendererButton1 = CreateComponent<GameEngineUIRenderer>();
		RendererButton1->SetTexture("The.png");
		//RendererButton1->ScaleToTexture();
		RendererButton1->GetTransform().SetLocalScale({ 1000, 200, 1 });
		RendererButton1->GetTransform().SetLocalPosition({ -180.f,180.f, -250.f });
		RendererButton1->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
		RendererButton1->GetPixelData().MulColor.a = 0.f;
		RendererButton1->ChangeCamera(CAMERAORDER::UICAMERA);

	}



	{
		RendererButton2 = CreateComponent<GameEngineUIRenderer>();
		RendererButton2->SetTexture("OldCrow.png");
		//RendererButton2->ScaleToTexture();
		RendererButton2->GetTransform().SetLocalScale({ 1000, 200, 1 });
		RendererButton2->GetTransform().SetLocalPosition({ 0.f,60.f, -250.f });
		RendererButton2->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
		RendererButton2->GetPixelData().MulColor.a = 0.f;
		RendererButton2->ChangeCamera(CAMERAORDER::UICAMERA);

	}




}

void OldCrowUI::Update(float _DeltaTime)
{

	if (m_bStartCheck)
	{

		RendererButton1->GetPixelData().MulColor.a += _DeltaTime;


		if (RendererButton1->GetPixelData().MulColor.a >= 1.f)
		{
			RendererButton1->GetPixelData().MulColor.a = 1.f;
			m_bButtoncheck = true;

		}

		if (m_bButtoncheck)
		{
			RendererButton2->GetPixelData().MulColor.a += _DeltaTime;

		}

	}


}

void OldCrowUI::End()
{

}






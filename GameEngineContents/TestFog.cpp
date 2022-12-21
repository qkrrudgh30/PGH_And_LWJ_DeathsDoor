

#include "PreCompile.h"
#include "TestFog.h"

#include "BillboardRenderer.h"


TestFog::TestFog()
{
}

TestFog::~TestFog()
{


}

void TestFog::Start()
{


	//sptrTestPicture = CreateComponent<BillboardRenderer>();
	//sptrTestPicture->SetTexture("SimpleTestParticle.png");
	//sptrTestPicture->SetRenderingOrder(5);
	//sptrTestPicture->GetTransform().SetLocalScale({ 3000.f, 3000.f, 1 });
	//sptrTestPicture->GetPixelData().MulColor.a = 0.2f;
	//sptrTestPicture->SetBillboardInfo(1);



	{
		FogRender = CreateComponent<GameEngineUIRenderer>();
		FogRender->SetTexture("SimpleTestParticle.png");
		FogRender->GetTransform().SetLocalScale({ 1500, 1500, 1 });
		FogRender->GetTransform().SetLocalRotate({0.f,0.f,90.f});
		FogRender->GetTransform().SetLocalPosition({1000.f,-0.f, 0.f });
		FogRender->ChangeCamera(CAMERAORDER::UICAMERA);
		FogRender->GetPixelData().MulColor.a = 0.5f;
		StartPos1 = FogRender->GetTransform().GetLocalPosition();

	}


	{
		FogRender2 = CreateComponent<GameEngineUIRenderer>();
		FogRender2->SetTexture("SimpleTestParticle.png");
		FogRender2->GetTransform().SetLocalScale({ 1500, 1500, 1 });
		FogRender2->GetTransform().SetLocalPosition({2200.f,0.f, 0.f });
		FogRender2->ChangeCamera(CAMERAORDER::UICAMERA);
		FogRender2->GetPixelData().MulColor.a = 0.5f;
		StartPos2 = FogRender2->GetTransform().GetLocalPosition();
	}



}

void TestFog::Update(float _DeltaTime)
{

	m_fSpeed += _DeltaTime;

	if (m_fSpeed >= 30.f)
	{
		m_fSpeed -= 30.f;
		FogRender->GetTransform().SetLocalPosition(StartPos1);

		FogRender2->GetTransform().SetLocalPosition(StartPos2);

	}


	float4 Pos1 = FogRender->GetTransform().GetLocalPosition();

	float4 Pos2 = FogRender2->GetTransform().GetLocalPosition();

	Pos1.x -= 100.f * _DeltaTime;
	Pos2.x -= 100.f * _DeltaTime;

	FogRender->GetTransform().SetLocalPosition(Pos1);

	FogRender2->GetTransform().SetLocalPosition(Pos2);





}

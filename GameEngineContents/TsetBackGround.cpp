
#include "PreCompile.h"
#include "TsetBackGround.h"

#include "BillboardRenderer.h"


TsetBackGround::TsetBackGround()
{
}

TsetBackGround::~TsetBackGround()
{
	

}

void TsetBackGround::Start()
{


//	float4 color = { 50.f ,50.f,50.f,1.f };
	sptrTestPicture = CreateComponent<BillboardRenderer>();
	sptrTestPicture->SetTexture("soul_keyhole.png");
	sptrTestPicture->GetTransform().SetLocalScale({ 1000.f, 1000.f, 1 });
	sptrTestPicture->SetBillboardInfo(1);
	//sptrTestPicture->ChangeCamera(CAMERAORDER::MAINCAMERA);
//	sptrTestPicture->ChangeCamera(CAMERAORDER::USER1);

}

void TsetBackGround::Update(float _DeltaTime)
{


}

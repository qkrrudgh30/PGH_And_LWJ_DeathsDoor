

#include "PreCompile.h"
#include "UIMouse.h"

UIMouse::UIMouse() :
	Renderer(nullptr)
	, UnitCol(false)
	, Collision()
	, UnitPos()
{
}

UIMouse::~UIMouse()
{
}

void UIMouse::Start()
{

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 5.f, 5.f, 5.f });
		Collision->ChangeOrder(OBJECTORDER::MouseUI);
		Collision->SetUIDebugCamera();
	}

	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->SetTexture("target.png");
	Renderer->GetTransform().SetLocalScale({50.f,50.f,1.f});
	Renderer->GetTransform().SetLocalPosition({ 0.f,0.f,-300.f });
	Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
}


void UIMouse::Update(float _DeltaTime)
{


	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();


	MousePos.x -= 640.f;
	MousePos.y = -MousePos.y;
	MousePos.y += 360.f;



	MousePos.z = -300.f;



	Renderer->GetTransform().SetLocalPosition(MousePos);
	Collision->GetTransform().SetLocalPosition(MousePos);
	



}
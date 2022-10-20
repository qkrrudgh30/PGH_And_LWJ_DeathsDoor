

#include "PreCompile.h"
#include "UIMouse.h"

UIMouse::UIMouse() :
	Renderer(nullptr)
	, UnitCol(false)
{
}

UIMouse::~UIMouse()
{
}

void UIMouse::Start()
{

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 1.f, 1.f, 1.f });
		Collision->ChangeOrder(OBJECTORDER::MouseUI);


	}


}


void UIMouse::Update(float _DeltaTime)
{


	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	MousePos.x -= 640.f;
	MousePos.y = -MousePos.y;
	MousePos.y += 360.f;
	MousePos.z = -300.f;




	Collision->GetTransform().SetLocalPosition(MousePos);




}
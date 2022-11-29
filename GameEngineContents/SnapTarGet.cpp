#include "PreCompile.h"
#include "SnapTarGet.h"
#include "SnapBullet.h"

SnapTarGet::SnapTarGet() 
{
}

SnapTarGet::~SnapTarGet() 
{
}

void SnapTarGet::Start()
{

	{
		float4 color = { 1.f,0.f,0.f,1.f };

		TexRenderer = CreateComponent<GameEngineTextureRenderer>();
		TexRenderer->SetTexture("target.png");
		TexRenderer->GetTransform().SetLocalScale({ 100.f, 100.f, 10.f });
		TexRenderer->GetTransform().SetLocalRotation({ -90.f,0.f,0.f });
		TexRenderer->GetPixelData().MulColor = color;

	}



}

void SnapTarGet::Update(float _DeltaTime)
{

	TexRenderer->GetTransform().SetLocalRotate({0.f, 150.f * _DeltaTime, 0.f});


	m_fTime += _DeltaTime;



	if (!m_bMakeCheck)
	{
		m_bMakeCheck = true;
		float4 MyPos = GetTransform().GetWorldPosition();
		MyPos.y += 1500.f;

		std::weak_ptr < SnapBullet> Bullet = GetLevel()->CreateActor<SnapBullet>(OBJECTORDER::MonsterAtt);
		Bullet.lock()->GetTransform().SetWorldPosition(MyPos);
		Bullet.lock()->m_pTarget = std::dynamic_pointer_cast<SnapTarGet>(shared_from_this());


	
	}





}


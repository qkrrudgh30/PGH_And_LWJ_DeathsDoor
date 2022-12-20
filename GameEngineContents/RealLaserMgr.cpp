

#include "PreCompile.h"
#include "RealLaserMgr.h"

#include "RealLaserTarget.h"
#include"GameEngineBase/GameEngineRandom.h"
#include "RealLaser.h"

RealLaserMgr::RealLaserMgr()
{
}

RealLaserMgr::~RealLaserMgr()
{
}



void RealLaserMgr::Start()
{

}

void RealLaserMgr::Update(float _DeltaTime)
{

}

void RealLaserMgr::DeleteAll()
{
	for (size_t i = 0; i < m_vTarget.size(); i++)
	{
		m_vTarget[i]->Death();
	}
	for (size_t i = 0; i < m_vTarget.size(); i++)
	{
		m_vRealLaser[i]->Death();
	}
}

void RealLaserMgr::MakeTarget()
{
	m_iCount = GameEngineRandom::MainRandom.RandomInt(0,4);
	//1907
	float4 A = { -208.f,10.f,763.f };
	float4 B = { 1079.f, 10.f,-529.f };


	float4 PosDir = float4::Normalize3DReturn(B - A);

	float4 MyPos = { -208.f,10.f,763.f };

	for (int i = 0; i <= 4; ++i)
	{
		if (m_iCount == i)
		{
			continue;
		}

		
		{
			std::shared_ptr < RealLaserTarget> Bullet = GetLevel()->CreateActor<RealLaserTarget>(OBJECTORDER::Eff);
			Bullet->GetTransform().SetWorldPosition(MyPos + ( PosDir * 160.f ) + (PosDir * 380.f * i));
			m_vTarget.push_back(Bullet);

		}



	}

}

void RealLaserMgr::MakeLaser()
{

	float4 A = { -208.f,200.f,763.f };
	float4 B = { 1079.f, 200.f,-529.f };


	float4 PosDir = float4::Normalize3DReturn(B - A);

	float4 MyPos = { -208.f,200.f,763.f };

	for (int i = 0; i <= 4; ++i)
	{
		if (m_iCount == i)
		{
			continue;
		}

		{
			std::shared_ptr < RealLaser> Bullet = GetLevel()->CreateActor<RealLaser>(OBJECTORDER::Eff);
			Bullet->GetTransform().SetWorldPosition(MyPos + (PosDir * 160.f) + (PosDir * 380.f * i));
			m_vRealLaser.push_back(Bullet);

		}

	}



	//for (int i = 0; i <= 4; ++i)
	//{
	//	if (m_iCount == i)
	//	{
	//		continue;
	//	}

	//	if (i == 0)
	//	{
	//		std::shared_ptr < RealLaser> Bullet = GetLevel()->CreateActor<RealLaser>(OBJECTORDER::Eff);
	//		float4 MyPos = { -124.f,100.f,547.f };
	//		Bullet->GetTransform().SetWorldPosition(MyPos);
	//		m_vRealLaser.push_back(Bullet);

	//	}
	//	else if (i == 1)
	//	{
	//		std::shared_ptr < RealLaser> Bullet = GetLevel()->CreateActor<RealLaser>(OBJECTORDER::Eff);
	//		float4 MyPos = { 112.f,100.f,305.f };
	//		Bullet->GetTransform().SetWorldPosition(MyPos);
	//		m_vRealLaser.push_back(Bullet);

	//	}
	//	else if (i == 2)
	//	{
	//		std::shared_ptr < RealLaser> Bullet = GetLevel()->CreateActor<RealLaser>(OBJECTORDER::Eff);
	//		float4 MyPos = { 358.f,100.f,62.f };
	//		Bullet->GetTransform().SetWorldPosition(MyPos);
	//		m_vRealLaser.push_back(Bullet);

	//	}
	//	else if (i == 3)
	//	{

	//		std::shared_ptr < RealLaser> Bullet = GetLevel()->CreateActor<RealLaser>(OBJECTORDER::Eff);
	//		float4 MyPos = { 673.f,100.f,269.f };
	//		Bullet->GetTransform().SetWorldPosition(MyPos);
	//		m_vRealLaser.push_back(Bullet);
	//	}
	//	else if (i == 4)
	//	{

	//		std::shared_ptr < RealLaser> Bullet = GetLevel()->CreateActor<RealLaser>(OBJECTORDER::Eff);
	//		float4 MyPos = { 872.f,100.f,-468.f };
	//		Bullet->GetTransform().SetWorldPosition(MyPos);
	//		m_vRealLaser.push_back(Bullet);
	//	}




	//}
}


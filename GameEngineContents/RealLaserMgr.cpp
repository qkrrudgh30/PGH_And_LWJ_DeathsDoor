

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
			Bullet->GetTransform().SetWorldPosition(MyPos + ( PosDir * 160.f ) + (PosDir * 380.f * float(i)));
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
			Bullet->GetTransform().SetWorldPosition(MyPos + (PosDir * 160.f) + (PosDir * 380.f * float(i)));
			m_vRealLaser.push_back(Bullet);

		}

	}


}

void RealLaserMgr::StartLaser()
{

	for (size_t i = 0; i < m_vTarget.size(); i++)
	{
		m_vRealLaser[i]->m_bScalecheck = true;
	}


}





#include "PreCompile.h"
#include "FeatherMgr.h"
#include "OldCrowFeather.h"

#include"GameEngineBase/GameEngineRandom.h"





FeatherMgr::FeatherMgr()
{
}

FeatherMgr::~FeatherMgr()
{
}



void FeatherMgr::Start()
{

	m_fSpeed = 0.5f;
	for (size_t i = 0; i < 6; i++)
	{   
		std::shared_ptr < OldCrowFeather> Bullet = GetLevel()->CreateActor<OldCrowFeather>(OBJECTORDER::Eff);
		float4 MyPos = GetTransform().GetWorldPosition();
		Bullet->GetTransform().SetWorldPosition(MyPos);
		Bullet->m_fStartPos = MyPos;

		m_vFeather.push_back(Bullet);


		Bullet = GetLevel()->CreateActor<OldCrowFeather>(OBJECTORDER::Eff);
	
		Bullet->GetTransform().SetWorldPosition(MyPos);
		Bullet->m_fStartPos = MyPos;

		m_vFeather2.push_back(Bullet);

	}
}

void FeatherMgr::Update(float _DeltaTime)
{

	if (!StartTimeCheck)
	{
		m_fSpeed += _DeltaTime;

		if (m_fSpeed >= 0.2f)
		{
			m_fSpeed -= 0.2f;

			m_vFeather[m_iFeatherCount]->StartCheck = true;
			m_vFeather2[m_iFeatherCount]->StartCheck = true;


			++m_iFeatherCount;

			if (m_iFeatherCount > 5)
			{
				StartTimeCheck = !StartTimeCheck;
			}

		}

	}

	float4 Mypos = GetTransform().GetWorldPosition();
	for (size_t i = 0; i < m_vFeather.size(); i++)
	{
		m_vFeather[i]->m_fStartPos = Mypos;
		m_vFeather2[i]->m_fStartPos = Mypos;
	}
	







	if (DeathCheck)
	{

		for (size_t i = 0; i < m_vFeather.size(); i++)
		{
			m_vFeather[i]->Death();
			m_vFeather2[i]->Death();
		}

	}

}


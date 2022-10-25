#include "PreCompile.h"
#include "UnitBase.h"

UnitBase::UnitBase() :
	m_fLifeTime(0.f)
	,m_fSpeed(0.f)
{
	m_Info.Dammage = 3;
	m_Info.Gold = 1000;
	m_Info.m_Hp = 8;
	m_Info.ArrowCount = 4;
	m_Info.m_MaxHp = 8;
	m_Info.Weapontype = WEAPONTYPE::Sword;
}

UnitBase::~UnitBase() 
{
}


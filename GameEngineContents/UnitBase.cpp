#include "PreCompile.h"
#include "UnitBase.h"

UnitBase::UnitBase() 
{
	m_Info.Dammage = 1.f;
	m_Info.Gold = 0;
	m_Info.m_Hp = 8;
	m_Info.ArrowCount = 4;
	m_Info.m_MaxHp = 8;
	m_Info.Weapontype = WEAPONTYPE::Sword;
}

UnitBase::~UnitBase() 
{
}


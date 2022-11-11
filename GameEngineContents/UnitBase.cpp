#include "PreCompile.h"
#include "UnitBase.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>

UnitBase::UnitBase() :
	m_fLifeTime(0.f)
	,m_fSpeed(0.f)
	,Renderer()
	,FBXAnimationRenderer()
	,Collision()
	,AttCollision()
	, StateManager()
	, m_Info()
	, m_fHitPos()
	, m_bHitCheck()
	, m_fHitDir()
	, hitTime()
	, m_fHitTime()
	, m_bhitCheck()
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


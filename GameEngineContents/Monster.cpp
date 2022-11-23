#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
#include "GameEngineCore/GameEngineFBXAnimationRenderer.h"
Monster::Monster() :
	StartPostion()
	, DirPower()
	, Pos()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{


	m_Info.m_Hp = 10;
	m_Info.m_MaxHp = 10;
	m_Info.Dammage = 1;
	m_fSpeed = 150.f;
	




	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->SetFBXMesh("Fire.fbx", "TextureAnimation");
	FBXAnimationRenderer->GetTransform().SetLocalScale({ 100.f,100.f,100.f });





}

void Monster::Update(float _DeltaTime) 
{

	





}






void Monster::MoveStart(const StateInfo& _Info)
{

}
void Monster::MoveEnd(const StateInfo& _Info)
{

}
void Monster::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{

}



void Monster::StunStart(const StateInfo& _Info)
{
	m_fHitDir = GetTransform().GetWorldPosition() - m_fHitPos;
	m_fHitDir = m_fHitDir.Normalize3DReturn();
}
void Monster::StunEnd(const StateInfo& _Info)
{

	

}
void Monster::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{

	



}
	 





void Monster::AttStart(const StateInfo& _Info)
{
	
}
void Monster::AttEnd(const StateInfo& _Info)
{

}
void Monster::AttUpdate(float _DeltaTime, const StateInfo& _Info)
{


}




void Monster::IdleStart(const StateInfo& _Info)
{

}
void Monster::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	


}

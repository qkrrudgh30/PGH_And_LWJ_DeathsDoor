#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalContentsValue.h"






typedef struct UnitInfo
{
	float m_Hp;
	float m_MaxHp;
	int Gold;
	float Dammage;


}UINFO;


// Ό³Έν :
class UnitBase : public GameEngineActor
{
public:
	// constrcuter destructer
	UnitBase();
	~UnitBase();

	// delete Function
	UnitBase(const UnitBase& _Other) = delete;
	UnitBase(UnitBase&& _Other) noexcept = delete;
	UnitBase& operator=(const UnitBase& _Other) = delete;
	UnitBase& operator=(UnitBase&& _Other) noexcept = delete;

protected:
	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;
	GameEngineCollision* AttCollision;
	UINFO	m_Info;
	GameEngineStateManager StateManager;


private:

};


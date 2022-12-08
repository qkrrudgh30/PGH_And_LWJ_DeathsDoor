#pragma once

enum class WEAPONTYPE
{
	Sword,
	Arrow,
	Fire,
	Hook,

};
typedef struct UnitInfo
{
	int m_Hp;
	int m_MaxHp;
	int Gold;
	int ArrowCount;
	int Dammage;
	WEAPONTYPE Weapontype;

}UINFO;



#include "Player.h"
#include "Monster.h"

enum class OBJECTORDER
{
	TileMap,
	MainCamera,
	MouseUI,
	BackGround,
	Player,
	PlayerAtt,
	PlayerHook,
	PlayerHookTrail,
	Monster,
	MonsterAtt,
	NPC,
	StaticMesh,
	CrowBullet,
	UI = 1000,
};

//enum class COLLISIONORDER
//{
//	Player,
//	Monster,
//	UI = 1000,
//};




// Ό³Έν :
class GlobalContentsValue
{
public:
	class Enums 
	{
	};

	class Actors 
	{
	public:
	//	static Monster* TestMonster;

	private:
		Actors() {		}
		~Actors() {		}
	};

private:
	GlobalContentsValue()	{	}

	~GlobalContentsValue()	{	}
};

enum
{
	emcHall = 409,
	emcROOM_Enter_1 = 23,
	emcGrave = 17,
	emcLantern = 3,
	eEnd,
};

enum
{
	False = 0,
	True = 1,
};

enum BlurType
{
	eNoBlur = 0,
	eVertical = 1,
	eHorizontal = 2,
	eVerticalAndHorizontal = 3,
};

enum ResourceType
{
	None = 0,
	UI = 1,
	Static = 2,
	Animator = 3
};

enum ShaderBitFlag : unsigned long
{
	eNone = 0x00,
	eFade = 0x01,
	eBlur = 0x02,
	eBloom = 0x04,
};
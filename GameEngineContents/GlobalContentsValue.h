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
	UI = 1000,
};

//enum class COLLISIONORDER
//{
//	Player,
//	Monster,
//	UI = 1000,
//};




// ���� :
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
	eVertical,
	eHorizontal,
	eVerticalAndHorizontal,
};

enum ResourceType
{
	None,
	UI,
	Static,
	Animator
};

enum ShaderBitFlag : unsigned long
{
	eNone = 0x00,
	eFade = 0x01,
	eBlur = 0x02,
	eBloom = 0x04,
};
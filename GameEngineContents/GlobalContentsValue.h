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
	float Dammage;
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
	Monster,
	NPC,
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


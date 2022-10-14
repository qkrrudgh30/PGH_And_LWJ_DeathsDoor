#pragma once
#include "Player.h"
#include "Monster.h"

enum class OBJECTORDER
{
	TileMap,
	MainCamera,
	BackGround,
	Player,
	Monster,
	UI = 1000,
};

//enum class COLLISIONORDER
//{
//	Player,
//	Monster,
//	UI = 1000,
//};


typedef struct UnitInfo
{
	float m_Hp;
	float m_MaxHp;
	int Gold;
	float Dammage;


}UINFO;



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
		static Monster* TestMonster;

	private:
		Actors() {		}
		~Actors() {		}
	};

private:
	GlobalContentsValue()	{	}

	~GlobalContentsValue()	{	}
};


#pragma once
#include "GameEngineCore.h"

// 설명 : 절대로 GameEngineCore의 클래스들은 GEngine을 사용하지 않아야 한다.
//        이유 => 이 클래스의 기능들은 철저하게 컨텐츠들에게 공개되는 겁니다.
class GEngine
{
	static bool CollisionDebug;

public:
	static void ChangeLevel(std::string _Name);
	static void CollisionDebugOn();
	static void CollisionDebugOff();
	static void CollisionDebugSwitch();

	static bool IsCollisionDebug();

	static GameEngineLevel* GetCurrentLevel();
	

protected:

private:
	// constrcuter destructer
	GEngine();
	virtual ~GEngine() = 0;
	// delete Function
	GEngine(const GEngine& _Other) = delete;
	GEngine(GEngine&& _Other) noexcept = delete;
	GEngine& operator=(const GEngine& _Other) = delete;
	GEngine& operator=(GEngine&& _Other) noexcept = delete;

};


#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// 자신이 맨처음 서있던 위치를 기억
// 업데이트에서 DeathUpdate에서 death 애니메이션이 종료되면 자신의 모든 랜더러를 off
// LiveTime = 5.0f
// // dj

// 설명 :

//enum class TowerAttType
//{
//	Jump = ,
//	Laser,
//	Meteo,
//	None
//};



class Spike;
class Player;
class TowerLaser;

class LaserTarget;
class Tower : public UnitBase
{
public:
	// constrcuter destructer
	Tower();
	~Tower();

	// delete Function
	Tower(const Tower& _Other) = delete;
	Tower(Tower&& _Other) noexcept = delete;
	Tower& operator=(const Tower& _Other) = delete;
	Tower& operator=(Tower&& _Other) noexcept = delete;

	void HittedSound() override { m_structSoundPlayer.Stop(); m_structSoundPlayer = GameEngineSound::SoundPlayControl("20_MiddleBossHitted.mp3"); }

	
protected:
	void Start() override;


	float4 StartPostion;
	float4 DirPower;



	void StateStart(const StateInfo& _Info);
	void StateStartUpdate(float _DeltaTime, const StateInfo& _Info);


	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleStart(const StateInfo& _Info);


	void MoveStart(const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);


	void LaserStart(const StateInfo& _Info);
	void LaserEnd(const StateInfo& _Info);
	void LaserUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttStart(const StateInfo& _Info);
	void AttEnd(const StateInfo& _Info);
	void AttUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
		 

	void End() {}

	virtual void Update(float _DeltaTime) override;

private:
	float4 Pos;
	std::shared_ptr < GameEngineCollision> StartCollision;

	bool m_bStartPause = false;
	bool m_bIdleUpDown = false;
	float m_fUpDownTime = 0.f;
	float m_fAttCTime = 0.f;
	int AttType = 0;


	bool ShakeOneCheck = false;
	bool m_bLaserUP = false;
	bool m_bLaserDown = false;
	float m_fLaserMoveTime = 0.f;
public : 
	bool m_bstart = false;
	std::weak_ptr<Spike> m_cSpike;
	std::weak_ptr < LaserTarget> m_CLaserTarget;
	std::weak_ptr < TowerLaser> m_CLaser;


private:
	void AniSlamFrame(const GameEngineRenderingEvent& _Data);
	void AniSlamEnd(const GameEngineRenderingEvent& _Data);
	void AniLaserEnd(const GameEngineRenderingEvent& _Data);
	void AniLaserFrame(const GameEngineRenderingEvent& _Data);
	void AniLaserEEnd(const GameEngineRenderingEvent& _Data);
	void AniSnapEnd(const GameEngineRenderingEvent& _Data);
	void AniJumpEnd(const GameEngineRenderingEvent& _Data);
	void AniJumpFrame(const GameEngineRenderingEvent& _Data);


};


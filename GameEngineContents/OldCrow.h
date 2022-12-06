
#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// 자신이 맨처음 서있던 위치를 기억
// 업데이트에서 DeathUpdate에서 death 애니메이션이 종료되면 자신의 모든 랜더러를 off
// LiveTime = 5.0f
// // dj

// 설명 :
class Player;
class DashBullet;
class OldCrow : public UnitBase
{
public:
	// constrcuter destructer
	OldCrow();
	~OldCrow();

	// delete Function
	OldCrow(const OldCrow& _Other) = delete;
	OldCrow(OldCrow&& _Other) noexcept = delete;
	OldCrow& operator=(const OldCrow& _Other) = delete;
	OldCrow& operator=(OldCrow&& _Other) noexcept = delete;




public:
	void Start() override;

	std::weak_ptr<DashBullet> m_cHook;
	float AttAngle = 0.f;


	float m_fJumpSpeed = 0.f;



	float4 m_vMovePlayerPos = {};
	float4 m_vMoveMyPos = {};

	float4 m_vMoveTarGetDir = {};

	float4 m_vMoveGoPos = {};
	float4 m_vMoveGoDir = {};

	float MoveLen = 0.f;



	float4 StartPostion = {};
	float4 DirPower = {};


	float m_fAttCTime = 0.f;
	int AttType = 0;

	int AttCount = 0;


	bool DashStartCheck = false;
	bool DashEndCheck = false;


	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleStart(const StateInfo& _Info);


	void StartActStart(const StateInfo& _Info);
	void StartActEnd(const StateInfo& _Info);
	void StartActUpdate(float _DeltaTime, const StateInfo& _Info);



	void MoveReadyStart(const StateInfo& _Info);
	void MoveReadyEnd(const StateInfo& _Info);
	void MoveReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);


	void TurnLStart(const StateInfo& _Info);
	void TurnLEnd(const StateInfo& _Info);
	void TurnLUpdate(float _DeltaTime, const StateInfo& _Info);

	void TurnRStart(const StateInfo& _Info);
	void TurnREnd(const StateInfo& _Info);
	void TurnRUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashReadyStart(const StateInfo& _Info);
	void DashReadyEnd(const StateInfo& _Info);
	void DashReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashStart(const StateInfo& _Info);
	void DashEnd(const StateInfo& _Info);
	void DashUpdate(float _DeltaTime, const StateInfo& _Info);


	void DashReady2Start(const StateInfo& _Info);
	void DashReady2End(const StateInfo& _Info);
	void DashReady2Update(float _DeltaTime, const StateInfo& _Info);


	void Dash2Start(const StateInfo& _Info);
	void Dash2End(const StateInfo& _Info);
	void Dash2Update(float _DeltaTime, const StateInfo& _Info);

	void DashReady3Start(const StateInfo& _Info);
	void DashReady3End(const StateInfo& _Info);
	void DashReady3Update(float _DeltaTime, const StateInfo& _Info);


	void Dash3Start(const StateInfo& _Info);
	void Dash3End(const StateInfo& _Info);
	void Dash3Update(float _DeltaTime, const StateInfo& _Info);



	void JumpStart(const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpReadyStart(const StateInfo& _Info);
	void JumpReadyEnd(const StateInfo& _Info);
	void JumpReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpEndStart(const StateInfo& _Info);
	void JumpEndEnd(const StateInfo& _Info);
	void JumpEndUpdate(float _DeltaTime, const StateInfo& _Info);


	void ScreamStart(const StateInfo& _Info);
	void ScreamEnd(const StateInfo& _Info);
	void ScreamUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashDeathStart(const StateInfo& _Info);
	void DashDeathEnd(const StateInfo& _Info);
	void DashDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	
	void StandDeathStart(const StateInfo& _Info);
	void StandDeathEnd(const StateInfo& _Info);
	void StandDeathUpdate(float _DeltaTime, const StateInfo& _Info);




	void End() {}

	virtual void Update(float _DeltaTime) override;

private:
	float4 Pos;
	bool StartAnicheck = false;
	bool ScreamAnicheck = false;

	float m_fStartTime = 0.f;
private:
	void AniDashEnd(const GameEngineRenderingEvent& _Data);
	void AniDashStartEnd(const GameEngineRenderingEvent& _Data);
	void AniDeathRunEnd(const GameEngineRenderingEvent& _Data);
	void AniDeathStandEnd(const GameEngineRenderingEvent& _Data);
	void AniIdleEnd(const GameEngineRenderingEvent& _Data);
	void AniJumpStartEnd(const GameEngineRenderingEvent& _Data);
	void AniRunEnd(const GameEngineRenderingEvent& _Data);
	void AniRunStartEnd(const GameEngineRenderingEvent& _Data);
	void AniScreamEnd(const GameEngineRenderingEvent& _Data);
	void AniSlamEnd(const GameEngineRenderingEvent& _Data);
	void AniSlamEndEnd(const GameEngineRenderingEvent& _Data);
	void AniTurnLeftEnd(const GameEngineRenderingEvent& _Data);
	void AniTurnRightEnd(const GameEngineRenderingEvent& _Data);


};


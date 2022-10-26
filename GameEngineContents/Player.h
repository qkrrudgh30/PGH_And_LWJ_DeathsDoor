#pragma once
//#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"




// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class PlayerSWAtt1;
class PlayerSWAtt2;
class PlayerSWAtt3;
class PlayerSWAttSlide;
class PlayerMainUI;
class PlayerUpgradeUI;
class PlayerHookAtt;

class Player : public UnitBase
{
private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	CollisionReturn MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End()  {}

	
	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void SworldAttStart(const StateInfo& _Info);
	void SworldAttEnd(const StateInfo& _Info);
	void SworldAttUpdate(float _DeltaTime, const StateInfo& _Info);

	void SworldAttStart2(const StateInfo& _Info);
	void SworldAttEnd2(const StateInfo& _Info);
	void SworldAttUpdate2(float _DeltaTime, const StateInfo& _Info);



	void SworldAttStart3(const StateInfo& _Info);
	void SworldAttEnd3(const StateInfo& _Info);
	void SworldAttUpdate3(float _DeltaTime, const StateInfo& _Info);




	void SlideStart(const StateInfo& _Info);
	void SlideEnd(const StateInfo& _Info);
	void SlideUpdate(float _DeltaTime, const StateInfo& _Info);


	void SlideAttStart(const StateInfo& _Info);
	void SlideAttEnd(const StateInfo& _Info);
	void SlideAttUpdate(float _DeltaTime, const StateInfo& _Info);

	void ArrowAttStart(const StateInfo& _Info);
	void ArrowAttEnd(const StateInfo& _Info);
	void ArrowAttUpdate(float _DeltaTime, const StateInfo& _Info);


	void HookAttStart(const StateInfo& _Info);
	void HookAttEnd(const StateInfo& _Info);
	void HookAttUpdate(float _DeltaTime, const StateInfo& _Info);




	// void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
public:

	void UIOff();
	void UIOn();


	bool	m_bHookEndcheck = false;
	bool	m_bHookHitcheck = false;
	float4 m_fHookPoint;


	PlayerUpgradeUI* UpgradeUI;
	PlayerMainUI* MainUI;
private:
	bool m_bSWAcheck;
	bool m_bSWA2check;
	bool m_bSWA3check;
	bool m_bSWASlidecheck;


	float Speed;
	float m_fAttTestTime;
	float4 ResultColor;


	float m_fSlideTime;
	float m_fSlideSpeed;
	float m_fSlideMaxSpeed;


	bool m_bSlideCCheck;
	float m_fSlideCTime;
	float m_fSlideCTimeMax;


	bool m_bSAttccheck;
	float m_fAttCTime;
	float m_fAttCTimeMax;

	bool m_bArrowCCheck;
	float m_fArrowCTime;
	float m_fArrowCTimeMax;


	bool m_bUpgradeUIcheck;
	bool m_bUpgradeUICoolcheck;



	bool m_bArrowCameraCheck;
	float4 m_fArrowCameraActionPos;

	float m_fCameraLenZ;
	float m_fCameraLenY;



	WEAPONTYPE	m_eBeforeType;


private:
	void ChangeRendererRotation(float _DeltaTime, int _Ratate);
	
	CollisionReturn CollisionNPC(GameEngineCollision* _This, GameEngineCollision* _Other);



private:
	PlayerSWAtt1* m_CSWAtt1;
	PlayerSWAtt2* m_CSWAtt2;
	PlayerSWAtt3* m_CSWAtt3;
	PlayerSWAttSlide* m_CSWAttSlide;
	PlayerHookAtt* m_CHookAtt;
};


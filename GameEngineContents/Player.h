#pragma once
//#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"




// ���� :
class GameEngineCollision;
class GameEngineTextureRenderer;
class PlayerSWAtt1;
class PlayerSWAtt2;
class PlayerSWAtt3;
class PlayerSWAttSlide;
class PlayerMainUI;
class PlayerUpgradeUI;


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




	// void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
public:

	
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



private:
	void ChangeRendererRotation(float _DeltaTime, int _Ratate);
	



private:
	PlayerSWAtt1* m_CSWAtt1;
	PlayerSWAtt2* m_CSWAtt2;
	PlayerSWAtt3* m_CSWAtt3;
	PlayerSWAttSlide* m_CSWAttSlide;



	PlayerUpgradeUI* UpgradeUI;
	PlayerMainUI* MainUI;
};


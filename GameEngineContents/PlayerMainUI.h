#pragma once


#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player;
// Ό³Έν :
class PlayerMainUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerMainUI();
	~PlayerMainUI();

	// delete Function
	PlayerMainUI(const PlayerMainUI& _Other) = delete;
	PlayerMainUI(PlayerMainUI&& _Other) noexcept = delete;
	PlayerMainUI& operator=(const PlayerMainUI& _Other) = delete;
	PlayerMainUI& operator=(PlayerMainUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}


	void PlayerInfoCheck();
	void PlayerInfoHPCheck();
	void PlayerInfoWeaponCheck();
	void PlayerInfoArrowCheck();

	GameEngineUIRenderer* RendererArrowSet;
	GameEngineUIRenderer* RendererFireSet;
	GameEngineUIRenderer* RendererHookSet;
	GameEngineUIRenderer* RendererSwordSet;

	GameEngineUIRenderer* RendererArrow;
	GameEngineUIRenderer* RendererFire;
	GameEngineUIRenderer* RendererHook;
	GameEngineUIRenderer* RendererSword;




	GameEngineUIRenderer* RendererHp1;
	GameEngineUIRenderer* RendererHp2;
	GameEngineUIRenderer* RendererHp3;
	GameEngineUIRenderer* RendererHp4;

	GameEngineUIRenderer* RendererHp5;
	GameEngineUIRenderer* RendererHp6;
	GameEngineUIRenderer* RendererHp7;
	GameEngineUIRenderer* RendererHp8;


	GameEngineUIRenderer* RendererArrow1;
	GameEngineUIRenderer* RendererArrow2;
	GameEngineUIRenderer* RendererArrow3;
	GameEngineUIRenderer* RendererArrow4;



	public:
		Player* m_Player;

};


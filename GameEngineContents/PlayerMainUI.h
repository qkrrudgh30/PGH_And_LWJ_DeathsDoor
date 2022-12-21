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

	std::shared_ptr <GameEngineUIRenderer> RendererArrowSet;
	std::shared_ptr <GameEngineUIRenderer> RendererFireSet;
	std::shared_ptr <GameEngineUIRenderer> RendererHookSet;
	std::shared_ptr <GameEngineUIRenderer> RendererSwordSet;

	std::shared_ptr <GameEngineUIRenderer> RendererArrow;
	std::shared_ptr <GameEngineUIRenderer> RendererFire;
	std::shared_ptr <GameEngineUIRenderer> RendererHook;
	std::shared_ptr <GameEngineUIRenderer> RendererSword;

	std::shared_ptr <GameEngineUIRenderer> RendererHp1;
	std::shared_ptr <GameEngineUIRenderer> RendererHp2;
	std::shared_ptr <GameEngineUIRenderer> RendererHp3;
	std::shared_ptr <GameEngineUIRenderer> RendererHp4;
	std::shared_ptr <GameEngineUIRenderer> RendererHp5;
	std::shared_ptr <GameEngineUIRenderer> RendererHp6;
	std::shared_ptr <GameEngineUIRenderer> RendererHp7;
	std::shared_ptr <GameEngineUIRenderer> RendererHp8;

	std::shared_ptr <GameEngineUIRenderer> RendererArrow1;
	std::shared_ptr <GameEngineUIRenderer> RendererArrow2;
	std::shared_ptr <GameEngineUIRenderer> RendererArrow3;
	std::shared_ptr <GameEngineUIRenderer> RendererArrow4;


	std::shared_ptr <GameEngineUIRenderer> FogRender;


	public:
		//std::weak_ptr < Player> m_Player;

};


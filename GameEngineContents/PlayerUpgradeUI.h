

#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player;
// Ό³Έν :
class PlayerUpgradeUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerUpgradeUI();
	~PlayerUpgradeUI();

	// delete Function
	PlayerUpgradeUI(const PlayerUpgradeUI& _Other) = delete;
	PlayerUpgradeUI(PlayerUpgradeUI&& _Other) noexcept = delete;
	PlayerUpgradeUI& operator=(const PlayerUpgradeUI& _Other) = delete;
	PlayerUpgradeUI& operator=(PlayerUpgradeUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}




	GameEngineUIRenderer* RendererArrowBack;
	GameEngineUIRenderer* RendererFireBack;
	GameEngineUIRenderer* RendererHookBack;
	GameEngineUIRenderer* RendererSwordBack;

	GameEngineUIRenderer* RendererArrow;
	GameEngineUIRenderer* RendererFire;
	GameEngineUIRenderer* RendererHook;
	GameEngineUIRenderer* RendererSword;


	GameEngineUIRenderer* RendererArrowUpBack[5];
	GameEngineUIRenderer* RendererFireUpBack[5];
	GameEngineUIRenderer* RendererHookUpBack[5];
	GameEngineUIRenderer* RendererSwordUpBack[5];

	GameEngineUIRenderer* RendererArrowUp[5];
	GameEngineUIRenderer* RendererFireUp[5];
	GameEngineUIRenderer* RendererHookUp[5];
	GameEngineUIRenderer* RendererSwordUp[5];


public:
	Player* m_Player;

};


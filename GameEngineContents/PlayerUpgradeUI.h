

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


	GameEngineCollision* CollisionArrowUp[5];
	GameEngineCollision* CollisionFireUp[5];
	GameEngineCollision* CollisionHookUp[5];
	GameEngineCollision* CollisionSwordUp[5];



	CollisionReturn CollisionArrowUp1(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionArrowUp2(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionArrowUp3(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionArrowUp4(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionArrowUp5(GameEngineCollision* _This, GameEngineCollision* _Other);

	CollisionReturn CollisionFireUp1(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionFireUp2(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionFireUp3(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionFireUp4(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionFireUp5(GameEngineCollision* _This, GameEngineCollision* _Other);


	CollisionReturn CollisionHookUp1(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionHookUp2(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionHookUp3(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionHookUp4(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionHookUp5(GameEngineCollision* _This, GameEngineCollision* _Other);


	CollisionReturn CollisionSword1(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionSword2(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionSword3(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionSword4(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionSword5(GameEngineCollision* _This, GameEngineCollision* _Other);





public:
	Player* m_Player;

};


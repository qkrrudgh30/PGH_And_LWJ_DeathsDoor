

#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player;
// Ό³Έν :
class PlayerUpgradeUI : public GameEngineActor
	//, public std::enable_shared_from_this<PlayerUpgradeUI>
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




	std::shared_ptr <GameEngineUIRenderer> RendererArrowBack;
	std::shared_ptr <GameEngineUIRenderer> RendererFireBack;
	std::shared_ptr <GameEngineUIRenderer> RendererHookBack;
	std::shared_ptr <GameEngineUIRenderer> RendererSwordBack;

	std::shared_ptr <GameEngineUIRenderer> RendererArrow;
	std::shared_ptr <GameEngineUIRenderer> RendererFire;
	std::shared_ptr <GameEngineUIRenderer> RendererHook;
	std::shared_ptr <GameEngineUIRenderer> RendererSword;

	std::shared_ptr <GameEngineUIRenderer> RendererArrowUpBack[5];
	std::shared_ptr <GameEngineUIRenderer> RendererFireUpBack[5];
	std::shared_ptr <GameEngineUIRenderer> RendererHookUpBack[5];
	std::shared_ptr <GameEngineUIRenderer> RendererSwordUpBack[5];

	std::shared_ptr <GameEngineUIRenderer> RendererArrowUp[5];
	std::shared_ptr <GameEngineUIRenderer> RendererFireUp[5];
	std::shared_ptr <GameEngineUIRenderer> RendererHookUp[5];
	std::shared_ptr <GameEngineUIRenderer> RendererSwordUp[5];


	std::shared_ptr <GameEngineCollision> CollisionArrowUp[5];
	std::shared_ptr <GameEngineCollision> CollisionFireUp[5];
	std::shared_ptr <GameEngineCollision> CollisionHookUp[5];
	std::shared_ptr <GameEngineCollision> CollisionSwordUp[5];



	CollisionReturn CollisionArrowUp1(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionArrowUp2(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionArrowUp3(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionArrowUp4(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionArrowUp5(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);

	CollisionReturn CollisionFireUp1(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionFireUp2(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionFireUp3(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionFireUp4(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionFireUp5(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);


	CollisionReturn CollisionHookUp1(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionHookUp2(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionHookUp3(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionHookUp4(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionHookUp5(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);


	CollisionReturn CollisionSword1(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionSword2(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionSword3(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionSword4(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);
	CollisionReturn CollisionSword5(std::shared_ptr <GameEngineCollision> _This, std::shared_ptr <GameEngineCollision> _Other);





public:
	std::weak_ptr < Player> m_Player;

};


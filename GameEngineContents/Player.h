#pragma once
#include <GameEngineCore/CoreMinimal.h>

// 설명 :
class GameEngineCollision;
class GameEngineTextureRenderer;
class Player : public GameEngineActor
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

	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* HPRenderer;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	// void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	float Speed;

	float4 ResultColor;

	GameEngineStateManager StateManager;
};


//class 잔상 : public GameEngineActor
//{
//	std::vector<GameEngineTextureRenderer*> AllPartsRenderer;
//
//public:
//	void Start() 
//	{
//		Death(0.2f);
//
//		// 
//		//HPRenderer->renderOption.Option00 = 1;
//	}
//
//	텍스처세팅(Player* _Player) 
//	{
//		for (size_t i = 0; i < _Player->AllPartsRenderer.size(); i++)
//		{
//			AllPartsRenderer[i]->SetTexture(_Player->AllPartsRenderer[i]->GetCurTexture());
//		}
//	}
//
//	업데이트() 
//	{
//		for (size_t i = 0; i < _Player->AllPartsRenderer.size(); i++)
//		{
//			AllPartsRenderer[i]->GetPixelData().PlusColor.a -= 델타타임;
//		}
//
//		// 점점 
//	}
//};
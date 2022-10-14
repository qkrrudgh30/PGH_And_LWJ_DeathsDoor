#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 자신이 맨처음 서있던 위치를 기억
// 업데이트에서 DeathUpdate에서 death 애니메이션이 종료되면 자신의 모든 랜더러를 off
// LiveTime = 5.0f
// // dj

// 설명 :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	void Start() override;

	GameEngineActor* NewActor;
	float4 StartPostion;
	float4 DirPower;

	//void Update(float _DeltaTime) 
	//{
	//	if (hp가 0이라면)
	//	{
	//		LiveTime -= 델타타임
	//		if (0.0 >= LiveTime)
	//		{
	//			랜더러를 다시 다 켜고
	//			GetTransform()->worldpostition(StartPostion);
	//			Renderer->ChangeAnimation(idle);
	//		}
	//		return;
	//	}
	//	// 일반적인 코드
	//}

	void End() {}

	virtual void Update(float _DeltaTime) override;

private:
	float4 Pos;

};


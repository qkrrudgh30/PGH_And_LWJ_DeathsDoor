#include "PreCompile.h"
#include "Player.h"

#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include <GameEngineCore/GameEngineFont.h>


Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed(50.0f)
	, Renderer(nullptr)
{
	MainPlayer = this;
}

Player::~Player()
{
}


void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_NUMPAD4);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_NUMPAD6);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_NUMPAD9);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_NUMPAD7);
		GameEngineInput::GetInst()->CreateKey("PlayerF", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("PlayerB", VK_NUMPAD2);
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::Player);

	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);

	int MyValue = 10;

	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info)
		{
			int Test = MyValue;
			Renderer->ChangeFrameAnimation("Move");

		});

	StateManager.ChangeState("Idle");


	{
		GameEngineDefaultRenderer* Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });

		Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);
	}

	{
		// GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		// Renderer->GetTransform().SetLocalScale({100.0f, 100.0f ,100.0f });
		// Renderer->ScaleToTexture();
	}

}

void Player::IdleStart(const StateInfo& _Info)
{
	// Renderer->ChangeFrameAnimation("Idle");
}

void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerUp") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{

	}
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
		Renderer->GetTransform().PixLocalNegativeX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
		Renderer->GetTransform().PixLocalPositiveX();
		// Renderer->GetColorData().MulColor.a -= _DeltaTime;
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}
}

CollisionReturn Player::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn::Break;
}

void Player::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);


	// StateManager 기능으로 
	StateManager.Update(_DeltaTime);
	//Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::UI, CollisionType::CT_OBB2D,
	//	std::bind(&Player::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2)
	//);
}
#include "PreCompile.h"
#include "Player.h"

#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include <GameEngineCore/GameEngineFont.h>


Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed(200.0f)
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

		GameEngineInput::GetInst()->CreateKey("PlayerF", 'W' );
		GameEngineInput::GetInst()->CreateKey("PlayerB", 'S');
		GameEngineInput::GetInst()->CreateKey("PlayerUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("PlayerDown", 'E');
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("PlayerRight", 'D');

		GameEngineInput::GetInst()->CreateKey("PlayerCamera", VK_LSHIFT);

		GameEngineInput::GetInst()->CreateKey("PlayerSlide", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("PlayerSworldAtt", VK_LBUTTON);


	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::Player);


	AttCollision = CreateComponent<GameEngineCollision>();
	AttCollision->GetTransform().SetLocalScale({ 150.0f, 50.0f, 50.0f });
	AttCollision->ChangeOrder(OBJECTORDER::Player);
	AttCollision->Off();

	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("SworldAtt"
		, std::bind(&Player::SworldAttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart, this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info){});

	StateManager.ChangeState("Idle");


	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({100.0f, 100.0f ,100.0f });
		// Renderer->ScaleToTexture();
	}
	

}

void Player::IdleStart(const StateInfo& _Info)
{

}

void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerUp") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerDown") ||
			true == GameEngineInput::GetInst()->IsPress("PlayerF") ||
			true == GameEngineInput::GetInst()->IsPress("PlayerB"))
	{
		StateManager.ChangeState("Move");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerSworldAtt"))
	{
		StateManager.ChangeState("SworldAtt");

	}


}

void Player::SworldAttStart(const StateInfo& _Info)
{

	AttCollision->On();

	float4 RenderFoward = Renderer->GetTransform().GetForwardVector();

	AttCollision->GetTransform().SetLocalPosition(RenderFoward * 100.f);
	AttCollision->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());

	int a = 0;
}

void Player::SworldAttEnd(const StateInfo& _Info)
{
	AttCollision->GetTransform().SetLocalPosition({0.f,0.f, 0.f, });
	AttCollision->Off();

	int a = 0;
}

void Player::SworldAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;

	if (m_fAttTestTime >= 1.f)
	{
		m_fAttTestTime = 0.f;
		StateManager.ChangeState("Idle");
	}
}


void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerF") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerB"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
		
		Renderer->GetTransform().SetLocalRotation({0.f,270.f,0.f});
		
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
		Renderer->GetTransform().SetLocalRotation({ 0.f,90.f,0.f });
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
		
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
		
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerF"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
		Renderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerB"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
		Renderer->GetTransform().SetLocalRotation({ 0.f,180.f,0.f });
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerSworldAtt"))
	{
		StateManager.ChangeState("SworldAtt");

	}



}

void Player::ChangeRendererRotation(float _DeltaTime, int _Ratate)
{


}

CollisionReturn Player::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn::Break;
}

void Player::Update(float _DeltaTime)
{
	


	StateManager.Update(_DeltaTime);

}
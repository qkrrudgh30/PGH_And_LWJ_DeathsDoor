#include "PreCompile.h"
#include "Player.h"


#include "PlayerSWAtt1.h"
#include "PlayerSWAtt2.h"
#include "PlayerSWAtt3.h"





#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include <GameEngineCore/GameEngineFont.h>


Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed(200.0f)
	, m_fSlideSpeed(700.f)
	, m_fSlideMaxSpeed(900.f)
	, m_fSlideCTime(0.f)
	, m_fSlideCTimeMax(2.f)
	, m_bSlideCCheck(false)
	, m_CSWAtt1(nullptr)
	, m_bSWAcheck(false)
	, m_bSWA2check(false)
	, m_bSWA3check(false)

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



	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("SworldAtt"
		, std::bind(&Player::SworldAttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart, this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("SworldAtt2"
		, std::bind(&Player::SworldAttUpdate2, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart2, this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd2, this, std::placeholders::_1)
	);



	StateManager.CreateStateMember("SworldAtt3"
		, std::bind(&Player::SworldAttUpdate3, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart3, this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd3, this, std::placeholders::_1)
	);




	StateManager.CreateStateMember("Slide"
		, std::bind(&Player::SlideUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SlideStart, this, std::placeholders::_1)
		, std::bind(&Player::SlideEnd, this, std::placeholders::_1)
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




//소드 공격 1번 
void Player::SworldAttStart(const StateInfo& _Info)
{

	//AttCollision->On();


	float4 MyWorldPos = GetTransform().GetWorldPosition();
	float4 RenderFoward = Renderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;
	


	RenderFoward = MyWorldPos + RenderFoward;

	m_CSWAtt1 = GetLevel()->CreateActor<PlayerSWAtt1>(OBJECTORDER::PlayerAtt);
	m_CSWAtt1->GetTransform().SetLocalPosition(RenderFoward);
	m_CSWAtt1->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());
	
	
	//AttCollision->GetTransform().SetLocalPosition(RenderFoward * 100.f);
//	AttCollision->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());

	
}

void Player::SworldAttEnd(const StateInfo& _Info)
{
	//AttCollision->GetTransform().SetLocalPosition({0.f,0.f, 0.f, });
	//AttCollision->Off();


	m_CSWAtt1->Death();

	m_bSWA2check = false;




}

void Player::SworldAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	//2타격 체크

	if (m_fAttTestTime >= 0.2f)
	{

		if (true == GameEngineInput::GetInst()->IsPress("PlayerSworldAtt"))
		{
			m_bSWA2check = true;

		}

	}


	if (m_fAttTestTime >= 0.5f)
	{
		m_fAttTestTime = 0.f;

		if (m_bSWA2check)
		{
			StateManager.ChangeState("SworldAtt2");
		}
		else
		{
			StateManager.ChangeState("Idle");
		}
		
	}
}









//소드 공격 2번 
void Player::SworldAttStart2(const StateInfo& _Info)
{

	//AttCollision->On();


	m_bSWA2check = false;

	float4 MyWorldPos = GetTransform().GetWorldPosition();
	float4 RenderFoward = Renderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;



	RenderFoward = MyWorldPos + RenderFoward;

	m_CSWAtt2 = GetLevel()->CreateActor<PlayerSWAtt2>(OBJECTORDER::PlayerAtt);
	m_CSWAtt2->GetTransform().SetLocalPosition(RenderFoward);
	m_CSWAtt2->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());


	//AttCollision->GetTransform().SetLocalPosition(RenderFoward * 100.f);
//	AttCollision->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());


}

void Player::SworldAttEnd2(const StateInfo& _Info)
{
	//AttCollision->GetTransform().SetLocalPosition({0.f,0.f, 0.f, });
	//AttCollision->Off();


	m_CSWAtt2->Death();
	m_bSWA3check = false;
}

void Player::SworldAttUpdate2(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	//3타격 체크

	if (m_fAttTestTime >= 0.2f)
	{
		if (true == GameEngineInput::GetInst()->IsPress("PlayerSworldAtt"))
		{
			m_bSWA3check = true;

		}
	}




	if (m_fAttTestTime >= 0.5f)
	{
		m_fAttTestTime = 0.f;

		if (m_bSWA3check)
		{
			StateManager.ChangeState("SworldAtt3");

		}
		else
		{
			StateManager.ChangeState("Idle");
		}

	}
}











//소드 공격 3번 
void Player::SworldAttStart3(const StateInfo& _Info)
{

	//AttCollision->On();

	m_bSWA3check = false;

	float4 MyWorldPos = GetTransform().GetWorldPosition();
	float4 RenderFoward = Renderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;



	RenderFoward = MyWorldPos + RenderFoward;

	m_CSWAtt3 = GetLevel()->CreateActor<PlayerSWAtt3>(OBJECTORDER::PlayerAtt);
	m_CSWAtt3->GetTransform().SetLocalPosition(RenderFoward);
	m_CSWAtt3->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());



}

void Player::SworldAttEnd3(const StateInfo& _Info)
{
	
	m_CSWAtt3->Death();

}

void Player::SworldAttUpdate3(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	if (m_fAttTestTime >= 0.5f)
	{
		m_fAttTestTime = 0.f;
		StateManager.ChangeState("Idle");
	}
}






















void Player::SlideStart(const StateInfo& _Info)
{
	m_fSlideSpeed = 700.f;
	
}

void Player::SlideEnd(const StateInfo& _Info)
{
	m_bSlideCCheck = true;
	m_fSlideSpeed = 700.f;
}

void Player::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir = Renderer->GetTransform().GetForwardVector();

	m_fSlideSpeed += _DeltaTime * 2000;

	if (m_fSlideSpeed >= m_fSlideMaxSpeed)
	{
		m_fSlideSpeed = m_fSlideMaxSpeed;
	}




	GetTransform().SetWorldMove(MoveDir * m_fSlideSpeed * _DeltaTime);

	m_fAttTestTime += _DeltaTime;

	if (m_fAttTestTime >= 0.3f)
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

	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);

	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);

	}
	

	//키 같이 입력
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerRight")  && true == GameEngineInput::GetInst()->IsPress("PlayerF"))
	{
		
		Renderer->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);



	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerRight") && true == GameEngineInput::GetInst()->IsPress("PlayerB"))
	{
		
		Renderer->GetTransform().SetLocalRotation({ 0.f,135.f,0.f });


		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);
	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") && true == GameEngineInput::GetInst()->IsPress("PlayerF"))
	{
		Renderer->GetTransform().SetLocalRotation({ 0.f,315.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);
	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") && true == GameEngineInput::GetInst()->IsPress("PlayerB"))
	{
		
		Renderer->GetTransform().SetLocalRotation({ 0.f,225.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);
	}
	
	
	
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
	

		Renderer->GetTransform().SetLocalRotation({ 0.f,270.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);

	}

	else if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		
		Renderer->GetTransform().SetLocalRotation({ 0.f,90.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);

	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerF"))
	{
		
		Renderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);

	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerB"))
	{
		
		Renderer->GetTransform().SetLocalRotation({ 0.f,180.f,0.f });

		float4 MoveDir = Renderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * Speed * _DeltaTime);

	}




	if (true == GameEngineInput::GetInst()->IsPress("PlayerSworldAtt"))
	{
		StateManager.ChangeState("SworldAtt");

	}


	if (true == GameEngineInput::GetInst()->IsPress("PlayerSlide"))
	{

		if (!m_bSlideCCheck)
		{
			StateManager.ChangeState("Slide");
		}
			

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
	if (m_bSlideCCheck)
	{
		m_fSlideCTime += _DeltaTime;

		if (m_fSlideCTime >= m_fSlideCTimeMax)
		{
			m_fSlideCTime = 0.f;
			m_bSlideCCheck = false;
		}
	}

	StateManager.Update(_DeltaTime);




	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	//float4 WorldPos = GetTransform().GetWorldPosition();
	//float4 CameraWorldPos = WorldPos;



	//CameraWorldPos.y += 1700.f;
	//CameraWorldPos.z -= 1700.f;


	//GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);




	float4 CameraWorldPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 WorldPos = GetTransform().GetWorldPosition();
	WorldPos.y += 1700.f;
	WorldPos.z -= 1700.f;


	float4 LerpPos = float4::Lerp(CameraWorldPos, WorldPos, _DeltaTime * 10.f);
	
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(LerpPos);




}
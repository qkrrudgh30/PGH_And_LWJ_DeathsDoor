#include "PreCompile.h"
#include "Player.h"


#include "PlayerSWAtt1.h"
#include "PlayerSWAtt2.h"
#include "PlayerSWAtt3.h"
#include "PlayerSWAttSlide.h"
#include "PlayerArrowAtt.h"
#include "PlayerHookAtt.h"


#include "PlayerMainUI.h"
#include "PlayerUpgradeUI.h"



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
	, m_CSWAttSlide(nullptr)
	, m_bSWASlidecheck(false)
	, m_bSAttccheck(false)
	, m_fAttCTime(0.f)
	, m_fAttCTimeMax(0.5f)
	, m_bUpgradeUIcheck(false)
	, m_bUpgradeUICoolcheck(false)
	, m_fArrowCTime(0.f)
	, m_fArrowCTimeMax(1.f)
	, m_bArrowCCheck(false)
	, m_bArrowCameraCheck(false)
	, m_fCameraLenZ(0.f)
	,m_fCameraLenY(0.f)
	, m_fArrowCameraActionPos(0.f)
{
	MainPlayer = this;
}

Player::~Player()
{
}


void Player::Start()
{

	MainUI = GetLevel()->CreateActor<PlayerMainUI>(OBJECTORDER::UI);
	MainUI->m_Player = this;



	UpgradeUI = GetLevel()->CreateActor<PlayerUpgradeUI>(OBJECTORDER::UI);
	UpgradeUI->m_Player = this;
	UpgradeUI->Off();

	UpgradeUI->SetLevelOverOn();
	MainUI->SetLevelOverOn();
	//UpgradeUI->SetParent(this);
	//MainUI->SetParent(this);

	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{

		GameEngineInput::GetInst()->CreateKey("PlayerF", 'W' );
		GameEngineInput::GetInst()->CreateKey("PlayerB", 'S');
		GameEngineInput::GetInst()->CreateKey("PlayerUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("PlayerDown", 'E');
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("PlayerRight", 'D');


		GameEngineInput::GetInst()->CreateKey("NPCClick", 'V');


		GameEngineInput::GetInst()->CreateKey("PlayerCamera", VK_LSHIFT);

		GameEngineInput::GetInst()->CreateKey("PlayerSlide", VK_SPACE);

		GameEngineInput::GetInst()->CreateKey("PlayerSworldAtt", VK_LBUTTON);

		GameEngineInput::GetInst()->CreateKey("PlayerArrowAtt", VK_RBUTTON);

		GameEngineInput::GetInst()->CreateKey("PlayerWeapomSwap", VK_TAB);


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



	StateManager.CreateStateMember("SlideAtt"
		, std::bind(&Player::SlideAttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SlideAttStart, this, std::placeholders::_1)
		, std::bind(&Player::SlideAttEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("ArrowAtt"
		, std::bind(&Player::ArrowAttUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ArrowAttStart, this, std::placeholders::_1)
		, std::bind(&Player::ArrowAttEnd, this, std::placeholders::_1)
	);


	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info){});

	StateManager.ChangeState("Idle");


	{
	

		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetPipeLine("Color");
		Renderer->GetRenderUnit().SetMesh("Box");
		ResultColor = {1.f,1.f,1.f,1.f};

		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f ,100.0f });
		Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	}




	m_Info.Weapontype = WEAPONTYPE::Arrow;

	m_eBeforeType = m_Info.Weapontype;
	

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

	if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
	{
		if (!m_bSAttccheck)
		{
			StateManager.ChangeState("SworldAtt");
		}

	}



	if (true == GameEngineInput::GetInst()->IsDown("PlayerSlide"))
	{

		if (!m_bSlideCCheck)
		{
			StateManager.ChangeState("Slide");
		}


	}


	if (true == GameEngineInput::GetInst()->IsDown("PlayerArrowAtt"))
	{

		if (!m_bArrowCCheck)
		{
			if (m_Info.Weapontype == WEAPONTYPE::Arrow)
			{
				if (m_Info.ArrowCount > 0)
				{
					StateManager.ChangeState("ArrowAtt");
				}
			}
		}


	}



	if (true == GameEngineInput::GetInst()->IsDown("PlayerWeapomSwap"))
	{
		// 무기 변경
		if (m_Info.Weapontype == WEAPONTYPE::Arrow)
		{
			m_Info.Weapontype = WEAPONTYPE::Fire;
			m_eBeforeType = m_Info.Weapontype;
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Fire)
		{
			m_Info.Weapontype = WEAPONTYPE::Hook;
			m_eBeforeType = m_Info.Weapontype;
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Hook)
		{
			m_Info.Weapontype = WEAPONTYPE::Arrow;
			m_eBeforeType = m_Info.Weapontype;
		}


	}





}




//소드 공격 1번 
void Player::SworldAttStart(const StateInfo& _Info)
{

	m_Info.Weapontype = WEAPONTYPE::Sword;


	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	MousePos.z = 0.f;

	float4 MyPos = GetLevel()->GetMainCamera()->GetWorldPositionToScreenPosition(GetTransform().GetWorldPosition());
	MyPos.z = 0.f;



	float4 RenderDir = (MousePos - MyPos);
	RenderDir.Normalize();
	RenderDir.z = 0;


	float m_fAngle = float4::VectorXYtoDegree(MyPos, MousePos);
	m_fAngle += 90.f;

	if (m_fAngle >= 360.f)
	{
		m_fAngle -= 360.f;
	}


	Renderer->GetTransform().SetLocalRotation({ 0.f,m_fAngle,0.f });




	m_Info.ArrowCount += 1;
	//m_Info.Weapontype = WEAPONTYPE::Sword;


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


	m_Info.Weapontype = m_eBeforeType;


}

void Player::SworldAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	//2타격 체크

	if (m_fAttTestTime >= 0.05f)
	{

		if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
		{
			m_bSWA2check = true;

		}

	}


	if (m_fAttTestTime >= 0.2f)
	{
		m_fAttTestTime = 0.f;

		if (m_bSWA2check)
		{
			StateManager.ChangeState("SworldAtt2");
		}
		else
		{
			StateManager.ChangeState("Idle");
			m_bSAttccheck = true;
		}
		
	}
}









//소드 공격 2번 
void Player::SworldAttStart2(const StateInfo& _Info)
{
	m_Info.Weapontype = WEAPONTYPE::Sword;

	//AttCollision->On();
	m_Info.ArrowCount += 1;

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
	

	m_Info.Weapontype = m_eBeforeType;


	m_CSWAtt2->Death();
	m_bSWA3check = false;
}

void Player::SworldAttUpdate2(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	//3타격 체크

	if (m_fAttTestTime >= 0.05f)
	{
		if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
		{
			m_bSWA3check = true;

		}
	}




	if (m_fAttTestTime >= 0.2f)
	{
		m_fAttTestTime = 0.f;

		if (m_bSWA3check)
		{
			StateManager.ChangeState("SworldAtt3");

		}
		else
		{
			StateManager.ChangeState("Idle");
			m_bSAttccheck = true;
		}

	}
}











//소드 공격 3번 
void Player::SworldAttStart3(const StateInfo& _Info)
{

	m_Info.Weapontype = WEAPONTYPE::Sword;

	m_Info.ArrowCount += 1;
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


	m_Info.Weapontype = m_eBeforeType;

	m_CSWAtt3->Death();

}

void Player::SworldAttUpdate3(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	if (m_fAttTestTime >= 0.2f)
	{
		m_fAttTestTime = 0.f;
		StateManager.ChangeState("Idle");
		m_bSAttccheck = true;
	}
}










void Player::ArrowAttStart(const StateInfo& _Info)
{

	m_Info.Weapontype = WEAPONTYPE::Arrow;

	m_bArrowCameraCheck = true;


}

void Player::ArrowAttEnd(const StateInfo& _Info)
{
	//화살 생성


	PlayerArrowAtt* m_ArrowAtt = GetLevel()->CreateActor<PlayerArrowAtt>(OBJECTORDER::PlayerAtt);
	m_ArrowAtt->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	m_ArrowAtt->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());




	m_bArrowCameraCheck = false;

	m_Info.ArrowCount -= 1;
	//m_Info.Weapontype = WEAPONTYPE::Sword;
}

void Player::ArrowAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//카메라 줌 + 플레이어 로테이션

	if (true == GameEngineInput::GetInst()->IsPress("PlayerArrowAtt"))
	{

		//m_fCameraLenY += 600.f * _DeltaTime;
	//	m_fCameraLenZ += 600.f * _DeltaTime;
		//if (m_fCameraLenY >= 2100.f)
		{
			m_fCameraLenY = 2100.f;
		}

	//	if (m_fCameraLenZ >= 2100.f)
		{
			m_fCameraLenZ = 2100.f;
		}

	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerArrowAtt"))
	{
		StateManager.ChangeState("Idle");

	}
	else if (true == GameEngineInput::GetInst()->IsFree("PlayerArrowAtt"))
	{
		StateManager.ChangeState("Idle");
	}



	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	MousePos.z = 0.f;

	float4 MyPos = GetLevel()->GetMainCamera()->GetWorldPositionToScreenPosition(GetTransform().GetWorldPosition());
	MyPos.z = 0.f;



	float4 RenderDir = (MousePos - MyPos);
	
	float Len = RenderDir.Length();
	RenderDir.Normalize();
	RenderDir.z = 0;
	
	if (Len >= 500.f)
	{
		Len = 500.f;
	}



	float m_fAngle = float4::VectorXYtoDegree(MyPos, MousePos);
	m_fAngle += 90.f;

	if (m_fAngle >= 360.f)
	{
		m_fAngle -= 360.f;
	}
	std::string A2 = std::to_string(m_fAngle);
	

	A2 += " : ANGLE";

	GameEngineDebug::OutPutString(A2);





	Renderer->GetTransform().SetLocalRotation({ 0.f,m_fAngle,0.f });

	m_fArrowCameraActionPos = Renderer->GetTransform().GetWorldPosition() + Renderer->GetTransform().GetForwardVector() * Len;


	


}







//후크 공격


void Player::HookAttStart(const StateInfo& _Info)
{

	m_Info.Weapontype = WEAPONTYPE::Arrow;

	m_bArrowCameraCheck = true;


}

void Player::HookAttEnd(const StateInfo& _Info)
{
	//화살 생성


	PlayerArrowAtt* m_ArrowAtt = GetLevel()->CreateActor<PlayerArrowAtt>(OBJECTORDER::PlayerAtt);
	m_ArrowAtt->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	m_ArrowAtt->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());




	m_bArrowCameraCheck = false;

	m_Info.ArrowCount -= 1;
	//m_Info.Weapontype = WEAPONTYPE::Sword;
}

void Player::HookAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//카메라 줌 + 플레이어 로테이션

	if (true == GameEngineInput::GetInst()->IsPress("PlayerArrowAtt"))
	{

		//m_fCameraLenY += 600.f * _DeltaTime;
	//	m_fCameraLenZ += 600.f * _DeltaTime;
		//if (m_fCameraLenY >= 2100.f)
		{
			m_fCameraLenY = 2100.f;
		}

		//	if (m_fCameraLenZ >= 2100.f)
		{
			m_fCameraLenZ = 2100.f;
		}

	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerArrowAtt"))
	{
		StateManager.ChangeState("Idle");

	}
	else if (true == GameEngineInput::GetInst()->IsFree("PlayerArrowAtt"))
	{
		StateManager.ChangeState("Idle");
	}



	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	MousePos.z = 0.f;

	float4 MyPos = GetLevel()->GetMainCamera()->GetWorldPositionToScreenPosition(GetTransform().GetWorldPosition());
	MyPos.z = 0.f;



	float4 RenderDir = (MousePos - MyPos);

	float Len = RenderDir.Length();
	RenderDir.Normalize();
	RenderDir.z = 0;

	if (Len >= 500.f)
	{
		Len = 500.f;
	}



	float m_fAngle = float4::VectorXYtoDegree(MyPos, MousePos);
	m_fAngle += 90.f;

	if (m_fAngle >= 360.f)
	{
		m_fAngle -= 360.f;
	}
	std::string A2 = std::to_string(m_fAngle);


	A2 += " : ANGLE";

	GameEngineDebug::OutPutString(A2);





	Renderer->GetTransform().SetLocalRotation({ 0.f,m_fAngle,0.f });

	m_fArrowCameraActionPos = Renderer->GetTransform().GetWorldPosition() + Renderer->GetTransform().GetForwardVector() * Len;





}













void Player::SlideStart(const StateInfo& _Info)
{
	m_fSlideSpeed = 700.f;
	m_bSWASlidecheck = false;
}

void Player::SlideEnd(const StateInfo& _Info)
{


	//슬라이드 끝나자 마자 공격 불가
	m_bSAttccheck = true;


	m_bSlideCCheck = true;
	m_fSlideSpeed = 700.f;
}

void Player::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir = Renderer->GetTransform().GetForwardVector();


//	if (m_fAttTestTime >= 0.2f)
	{
		if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
		{
			m_bSWASlidecheck = true;

		}
	}




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


		if (m_bSWASlidecheck)
		{
			StateManager.ChangeState("SlideAtt");
		}
		else
		{
			StateManager.ChangeState("Idle");
		}
		
	}



}





void Player::SlideAttStart(const StateInfo& _Info)
{

	float4 MyWorldPos = GetTransform().GetWorldPosition();
	float4 RenderFoward = Renderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;


	RenderFoward = MyWorldPos + RenderFoward;

	m_CSWAttSlide = GetLevel()->CreateActor<PlayerSWAttSlide>(OBJECTORDER::PlayerAtt);
	m_CSWAttSlide->GetTransform().SetLocalPosition(RenderFoward);
	m_CSWAttSlide->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());

}

void Player::SlideAttEnd(const StateInfo& _Info)
{

	m_CSWAttSlide->Death();

	
}

void Player::SlideAttUpdate(float _DeltaTime, const StateInfo& _Info)
{


	m_fAttTestTime += _DeltaTime;


	if (m_fAttTestTime >= 0.3f)
	{
		m_fAttTestTime = 0.f;
		StateManager.ChangeState("Idle");
	}


	float4 MoveDir = Renderer->GetTransform().GetForwardVector();

	GetTransform().SetWorldMove(MoveDir * m_fSlideSpeed * _DeltaTime);
	m_CSWAttSlide->GetTransform().SetWorldMove(MoveDir * m_fSlideSpeed * _DeltaTime);

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




	if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
	{

		if (!m_bSAttccheck)
		{
			StateManager.ChangeState("SworldAtt");
		}
	}


	if (true == GameEngineInput::GetInst()->IsDown("PlayerSlide"))
	{

		if (!m_bSlideCCheck)
		{
			StateManager.ChangeState("Slide");
		}
			

	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayerArrowAtt"))
	{

		if (!m_bArrowCCheck)
		{
			if (m_Info.Weapontype == WEAPONTYPE::Arrow)
			{
				if (m_Info.ArrowCount > 0)
				{
					StateManager.ChangeState("ArrowAtt");
				}
			}
			
		}


	}


	if (true == GameEngineInput::GetInst()->IsDown("PlayerWeapomSwap"))
	{
		// 무기 변경
		if (m_Info.Weapontype == WEAPONTYPE::Arrow)
		{
			m_Info.Weapontype = WEAPONTYPE::Fire;
			m_eBeforeType = m_Info.Weapontype;
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Fire)
		{
			m_Info.Weapontype = WEAPONTYPE::Hook;
			m_eBeforeType = m_Info.Weapontype;
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Hook)
		{
			m_Info.Weapontype = WEAPONTYPE::Arrow;
			m_eBeforeType = m_Info.Weapontype;
		}


	}




}

void Player::ChangeRendererRotation(float _DeltaTime, int _Ratate)
{


}

CollisionReturn Player::CollisionNPC(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	if (!m_bUpgradeUICoolcheck)
	{
		if (m_bUpgradeUIcheck)
		{
			m_bUpgradeUIcheck = false;


			UpgradeUI->Off();

		}
		else
		{
			m_bUpgradeUIcheck = true;

			UpgradeUI->On();
		}

	}
	
		
	


	return CollisionReturn::ContinueCheck;
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


	if (m_bSAttccheck)
	{
		m_fAttCTime += _DeltaTime;

		if (m_fAttCTime >= m_fAttCTimeMax)
		{
			m_fAttCTime = 0.f;
			m_bSAttccheck = false;
		}
	}


	if (m_Info.ArrowCount >= 4)
	{
		m_Info.ArrowCount = 4;
	}
	else if (m_Info.ArrowCount <= 0)
	{
		m_Info.ArrowCount = 0;
	}







	/// <summary>
	/// 
	/// 
	/// 

	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();




	std::string A = std::to_string(MousePos.x);
	std::string B = std::to_string(MousePos.y);

	A += " : X";
	B += " : Y";
	GameEngineDebug::OutPutString(A);
	GameEngineDebug::OutPutString(B);


	MousePos.z = 0.f;
	//	MousePos.x -= 640.f;
		//MousePos.y = -MousePos.y;
	//	MousePos.y += 360.f;



	float4 MyPos = GetLevel()->GetMainCamera()->GetWorldPositionToScreenPosition(GetTransform().GetWorldPosition());
	MyPos.z = 0.f;



	std::string A2 = std::to_string(MyPos.x);
	std::string B2 = std::to_string(MyPos.y);

	A2 += " : PX";
	B2 += " : PY";
	GameEngineDebug::OutPutString(A2);
	GameEngineDebug::OutPutString(B2);





	//

	Collision->GetTransform().SetLocalRotation(Renderer->GetTransform().GetLocalRotation());
	
	float4 WoprldPos = GetTransform().GetWorldPosition();

	float4 ScreenPos = GetLevel()->GetMainCameraActor()->GetCameraComponent()->GetWorldPositionToScreenPosition(WoprldPos);

	

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
	
	if (true == GameEngineInput::GetInst()->IsPress("NPCClick"))
	{
		Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::NPC, CollisionType::CT_OBB,
			std::bind(&Player::CollisionNPC, this, std::placeholders::_1, std::placeholders::_2)
		);

		m_bUpgradeUICoolcheck = true;
	}
	if (true == GameEngineInput::GetInst()->IsUp("NPCClick"))
	{
		m_bUpgradeUICoolcheck = false;
	}





	if (m_bUpgradeUIcheck)
	{
		return;
	}
	//float4 WorldPos = GetTransform().GetWorldPosition();
	//float4 CameraWorldPos = WorldPos;



	//CameraWorldPos.y += 1700.f;
	//CameraWorldPos.z -= 1700.f;


	//GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);


	StateManager.Update(_DeltaTime);
	float4 WorldPos;
	if (!m_bArrowCameraCheck)
	{

		m_fCameraLenZ = 1700.f;
		m_fCameraLenY = 1700.f;
		WorldPos = GetTransform().GetWorldPosition();
	}
	else
	{
		WorldPos = m_fArrowCameraActionPos; //* -1.f;
	}


//	WorldPos = GetTransform().GetWorldPosition();
	float4 CameraWorldPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();

	//WorldPos.x -= 1200.f;
	WorldPos.y += m_fCameraLenY;
	WorldPos.z -= m_fCameraLenZ;


	//if (CameraWorldPos.x != WorldPos.x || CameraWorldPos.y != WorldPos.y || CameraWorldPos.z != WorldPos.z)
	{

		float4 LerpPos = float4::Lerp(CameraWorldPos, WorldPos, _DeltaTime * 10.f);

		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(LerpPos);

	}

	



}

void Player::UIOff()
{
	MainUI->Off();
	
}
void Player::UIOn()
{
	MainUI->On();

}

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
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>




Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed(200.0f)
	, m_fSlideSpeed(700.f)
	, m_fSlideMaxSpeed(900.f)
	, m_fSlideCTime(0.f)
	, m_fSlideCTimeMax(2.f)
	, m_bSlideCCheck(false)
	, m_CSWAtt1()
	, m_bSWAcheck(false)
	, m_bSWA2check(false)
	, m_bSWA3check(false)
	, m_CSWAttSlide()
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
	, m_fCameraLenY(0.f)
	, m_fAccTime(0.f)
	, m_fArrowCameraActionPos(0.f)
	//, UpgradeUI()
	//, MainUI()
	, m_fStaticCollDir()
	, m_fAttTestTime()
	, ResultColor()
	, m_fSlideTime()
	, m_eBeforeType()
	, m_CSWAtt3()
	, m_CHookAtt()
	, m_CSWAtt2()
{
	MainPlayer = this;
}

Player::~Player()
{
}
// comment

void Player::Start()
{


	FBXAnimationRenderer = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXAnimationRenderer->GetTransform().SetLocalScale(float4{ 15.f, 15.f, 15.f });
	FBXAnimationRenderer->GetTransform().SetLocalRotation(float4{ 0.f, 45.f, 0.f });
	FBXAnimationRenderer->SetFBXMesh("Player.fbx", "TextureAnimation");
	//Renderer->SetParent(FBXAnimationRenderer);



	//Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//Renderer->SetPipeLine("Color");
	//Renderer->GetRenderUnit().SetMesh("Box");
	//float4 ResultColor = { 1.f,1.f,1.f,1.f };
	//Renderer->GetTransform().SetLocalScale({ 10.0f, 10.0f, 10.0f });
	//Renderer->GetTransform().SetLocalPosition(GetTransform().GetForwardVector() * 500.f);
	//Renderer->GetShaderResources().SetConstantBufferNew("ResultColor", ResultColor);



	{
		FBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
		FBXStaticRenderer->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, 0.f });
		FBXStaticRenderer->GetTransform().SetLocalScale(float4{ 1.f, 1.f, 1.f });
		FBXStaticRenderer->SetFBXMesh("Arrow.FBX", "Texture");
		FBXStaticRenderer->Off();

	}




	Event.ResourcesName = "Player_Idle.FBX";
	Event.Loop = true;
	Event.Inter = 0.02f;
	FBXAnimationRenderer->CreateFBXAnimation("Player_Idle", Event);



	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Walk_S.FBX";
		Event2.Loop = true;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Walk", Event2);
	}



	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Arrow.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Arrow", Event2);
		
	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Att_Left.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.01f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Att_Left", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_Att_Left", std::bind(&Player::AniPlayer_Att_Left, this, std::placeholders::_1));
	}


	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Att_R.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.01f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Att_Right", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_Att_Right", std::bind(&Player::AniPlayer_Att_R, this, std::placeholders::_1));

	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Att1.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.01f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Att1", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_Att1", std::bind(&Player::AniPlayer_Att1, this, std::placeholders::_1));

	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Att2.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.01f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Att2", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_Att2", std::bind(&Player::AniPlayer_Att2, this, std::placeholders::_1));

	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Roll.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Roll", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_Roll", std::bind(&Player::AniPlayer_Roll, this, std::placeholders::_1));

	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Hook.FBX";
		Event2.Loop = true;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Hook", Event2);

	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Hook_Fly.FBX";
		Event2.Loop = true;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Hook_Fly", Event2);
	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_Idle2.FBX";
		Event2.Loop = true;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_Idle2", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_Idle2", std::bind(&Player::AniPlayer_Idle2, this, std::placeholders::_1));
	}

	{
		GameEngineRenderingEvent Event2;
		Event2.ResourcesName = "Player_SlideAtt.FBX";
		Event2.Loop = false;
		Event2.Inter = 0.02f;
		FBXAnimationRenderer->CreateFBXAnimation("Player_SlideAtt", Event2);
		FBXAnimationRenderer->AnimationBindEnd("Player_SlideAtt", std::bind(&Player::AniPlayer_SlideAtt, this, std::placeholders::_1));

	}





	
	

	
	FBXAnimationRenderer->ChangeAnimation("Player_Idle2");


	//ui주석 풀어야함
	MainUI = GetLevel()->CreateActor<PlayerMainUI>(OBJECTORDER::UI);
	
	UpgradeUI = GetLevel()->CreateActor<PlayerUpgradeUI>(OBJECTORDER::UI);
	UpgradeUI.lock()->Off();

	UpgradeUI.lock()->SetLevelOverOn();
	MainUI.lock()->SetLevelOverOn();
	 
	 
	 


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
	Collision->GetTransform().SetLocalScale({ 100.0f, 500.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::Player);

	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("SworldAtt"
		, std::bind(&Player::SworldAttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart,this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("SworldAtt2"
		, std::bind(&Player::SworldAttUpdate2,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart2,this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd2,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("SworldAtt3"
		, std::bind(&Player::SworldAttUpdate3,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SworldAttStart3,this, std::placeholders::_1)
		, std::bind(&Player::SworldAttEnd3,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Slide"
		, std::bind(&Player::SlideUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SlideStart,this, std::placeholders::_1)
		, std::bind(&Player::SlideEnd,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("SlideAtt"
		, std::bind(&Player::SlideAttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SlideAttStart,this, std::placeholders::_1)
		, std::bind(&Player::SlideAttEnd,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("ArrowAtt"
		, std::bind(&Player::ArrowAttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ArrowAttStart,this, std::placeholders::_1)
		, std::bind(&Player::ArrowAttEnd,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("HookAtt"
		, std::bind(&Player::HookAttUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::HookAttStart,this, std::placeholders::_1)
		, std::bind(&Player::HookAttEnd,this, std::placeholders::_1)
	);

	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate,this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info){});

	StateManager.ChangeState("Idle");

	m_Info.Weapontype = WEAPONTYPE::Arrow;

	m_eBeforeType = m_Info.Weapontype;




}

void Player::IdleStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Player_Idle2");
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

			if (m_Info.Weapontype != WEAPONTYPE::Sword)
			{

				if (m_Info.Weapontype == WEAPONTYPE::Arrow)
				{
					if (m_Info.ArrowCount > 0)
					{
						StateManager.ChangeState("ArrowAtt");
					}
				}
				else if (m_Info.Weapontype == WEAPONTYPE::Hook)
				{

					StateManager.ChangeState("ArrowAtt");
				}
				else if (m_Info.Weapontype == WEAPONTYPE::Fire)
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
	FBXAnimationRenderer->ChangeAnimation("Player_Att1");

	m_Info.Weapontype = WEAPONTYPE::Sword;


	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	MousePos.z = 0.f;

	float4 MyPos = GetLevel()->GetMainCamera()->GetWorldPositionToScreenPosition(GetTransform().GetWorldPosition());
	MyPos.z = 0.f;



	float4 RenderDir = (MousePos - MyPos);
	RenderDir.Normalize3D();
	RenderDir.z = 0;


	float m_fAngle = float4::VectorXYtoDegree(MyPos, MousePos);
	m_fAngle += 90.f;

	if (m_fAngle >= 360.f)
	{
		m_fAngle -= 360.f;
	}


	FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,m_fAngle,0.f });




	m_Info.ArrowCount += 1;
	//m_Info.Weapontype = WEAPONTYPE::Sword;


	float4 MyWorldPos = GetTransform().GetWorldPosition();
	/*float4 RenderFoward = FBXAnimationRenderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;
	


	RenderFoward = MyWorldPos + RenderFoward;*/
	MyWorldPos.y += 20.f;
	m_CSWAtt1 = GetLevel()->CreateActor<PlayerSWAtt1>(OBJECTORDER::PlayerAtt);
	m_CSWAtt1.lock()->GetTransform().SetLocalPosition(MyWorldPos);
	m_CSWAtt1.lock()->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());
	
	
	//AttCollision->GetTransform().SetLocalPosition(RenderFoward * 100.f);
//	AttCollision->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());

	
}

void Player::SworldAttEnd(const StateInfo& _Info)
{
	//AttCollision->GetTransform().SetLocalPosition({0.f,0.f, 0.f, });
	//AttCollision->Off();


	m_CSWAtt1.lock()->Death();
	m_CSWAtt1.lock() = nullptr;
	m_bSWA2check = false;


	m_Info.Weapontype = m_eBeforeType;


}

void Player::SworldAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	//2타격 체크

	if (m_fAttTestTime >= 0.1f)
	{

		if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
		{
			m_bSWA2check = true;

		}

	}



}









//소드 공격 2번 
void Player::SworldAttStart2(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Player_Att_Right");

	m_Info.Weapontype = WEAPONTYPE::Sword;

	//AttCollision->On();
	m_Info.ArrowCount += 1;

	m_bSWA2check = false;

	float4 MyWorldPos = GetTransform().GetWorldPosition();
	/*float4 RenderFoward = FBXAnimationRenderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;



	RenderFoward = MyWorldPos + RenderFoward;*/
	MyWorldPos.y += 20.f;
	m_CSWAtt2 = GetLevel()->CreateActor<PlayerSWAtt2>(OBJECTORDER::PlayerAtt);
	m_CSWAtt2.lock()->GetTransform().SetLocalPosition(MyWorldPos);
	m_CSWAtt2.lock()->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());




}

void Player::SworldAttEnd2(const StateInfo& _Info)
{


	m_Info.Weapontype = m_eBeforeType;


	m_CSWAtt2.lock()->Death();
	m_CSWAtt2.lock() = nullptr;
	m_bSWA3check = false;
}

void Player::SworldAttUpdate2(float _DeltaTime, const StateInfo& _Info)
{
	m_fAttTestTime += _DeltaTime;


	//3타격 체크

	if (m_fAttTestTime >= 0.1f)
	{
		if (true == GameEngineInput::GetInst()->IsDown("PlayerSworldAtt"))
		{
			m_bSWA3check = true;

		}
	}




	
}











//소드 공격 3번 
void Player::SworldAttStart3(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Player_Att_Left");
	m_Info.Weapontype = WEAPONTYPE::Sword;

	m_Info.ArrowCount += 1;
	//AttCollision->On();

	m_bSWA3check = false;

	float4 MyWorldPos = GetTransform().GetWorldPosition();
	/*float4 RenderFoward = FBXAnimationRenderer->GetTransform().GetForwardVector();
	RenderFoward = RenderFoward * 100.f;



	RenderFoward = MyWorldPos + RenderFoward;*/
	MyWorldPos.y += 20.f;
	m_CSWAtt3= GetLevel()->CreateActor<PlayerSWAtt3>(OBJECTORDER::PlayerAtt);
	m_CSWAtt3.lock()->GetTransform().SetLocalPosition(MyWorldPos);
	m_CSWAtt3.lock()->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());



}

void Player::SworldAttEnd3(const StateInfo& _Info)
{

	m_fAttTestTime = 0.f;
	m_Info.Weapontype = m_eBeforeType;
	m_bSAttccheck = true;
	m_CSWAtt3.lock()->Death();
	m_CSWAtt3.lock() = nullptr;
}

void Player::SworldAttUpdate3(float _DeltaTime, const StateInfo& _Info)
{
	
}










void Player::ArrowAttStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Player_Arrow");
	m_bArrowCameraCheck = true;

	if (m_Info.Weapontype == WEAPONTYPE::Arrow)
	{

	}
	else if (m_Info.Weapontype == WEAPONTYPE::Hook)
	{

	}
	else if (m_Info.Weapontype == WEAPONTYPE::Fire)
	{

	}

}

void Player::ArrowAttEnd(const StateInfo& _Info)
{
	//화살 생성
	float4 ArrowDir = FBXAnimationRenderer->GetTransform().GetLocalRotation();
	float4 RenderFront = FBXAnimationRenderer->GetTransform().GetForwardVector();
	float4 ArrowPos = GetTransform().GetWorldPosition() + (RenderFront.Normalize3DReturn() * 50.f);
	ArrowPos.y += 20.f;
	if (m_Info.Weapontype == WEAPONTYPE::Arrow)
	{
		std::weak_ptr < PlayerArrowAtt> m_ArrowAtt = GetLevel()->CreateActor<PlayerArrowAtt>(OBJECTORDER::PlayerAtt);

		
		m_ArrowAtt.lock()->GetTransform().SetWorldPosition(ArrowPos);
		m_ArrowAtt.lock()->GetTransform().SetLocalRotation(ArrowDir);
		m_bArrowCameraCheck = false;
		m_Info.ArrowCount -= 1;
	}
	else if (m_Info.Weapontype == WEAPONTYPE::Hook)
	{

		m_CHookAtt = GetLevel()->CreateActor<PlayerHookAtt>(OBJECTORDER::PlayerAtt);
		m_CHookAtt.lock()->GetTransform().SetWorldPosition(ArrowPos);
		m_CHookAtt.lock()->GetTransform().SetLocalRotation(ArrowDir);


		m_bArrowCameraCheck = false;
	}
	else if (m_Info.Weapontype == WEAPONTYPE::Fire)
	{


		m_bArrowCameraCheck = false;
	}
	
}

void Player::ArrowAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//카메라 줌 + 플레이어 로테이션



	if (true == GameEngineInput::GetInst()->IsPress("PlayerArrowAtt"))
	{


		{
			m_fCameraLenY = 2100.f;
		}

		{
			m_fCameraLenZ = 2100.f;
		}

	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerArrowAtt"))
	{
		
		if (m_Info.Weapontype == WEAPONTYPE::Arrow)
		{
			StateManager.ChangeState("Idle");
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Hook)
		{
			StateManager.ChangeState("HookAtt");
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Fire)
		{
			StateManager.ChangeState("Idle");
		}



	}
	else if (true == GameEngineInput::GetInst()->IsFree("PlayerArrowAtt"))
	{

		if (m_Info.Weapontype == WEAPONTYPE::Arrow)
		{
			StateManager.ChangeState("Idle");
		}
		else if (m_Info.Weapontype == WEAPONTYPE::Hook)
		{

		}
		else if (m_Info.Weapontype == WEAPONTYPE::Fire)
		{

		}


	}



	float4 MousePos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	MousePos.z = 0.f;

	float4 MyPos = GetLevel()->GetMainCamera()->GetWorldPositionToScreenPosition(GetTransform().GetWorldPosition());
	MyPos.z = 0.f;



	float4 RenderDir = (MousePos - MyPos);
	
	float Len = RenderDir.Length();
	RenderDir.Normalize3D();
	RenderDir.z = 0;
	
	if (Len >= 500.f)
	{
		Len = 500.f;
	}

	FBXStaticRenderer->GetTransform().SetLocalPosition(GetTransform().GetForwardVector() * Len);
	
	float m_fAngle = float4::VectorXYtoDegree(MyPos, MousePos);
	m_fAngle += 90.f;

	if (m_fAngle >= 360.f)
	{
		m_fAngle -= 360.f;
	}
	std::string A2 = std::to_string(m_fAngle);
	

	A2 += " : ANGLE";

	GameEngineDebug::OutPutString(A2);





	FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,m_fAngle,0.f });

	m_fArrowCameraActionPos = FBXAnimationRenderer->GetTransform().GetWorldPosition() + FBXAnimationRenderer->GetTransform().GetForwardVector() * Len;

	FBXStaticRenderer->GetTransform().SetLocalPosition(FBXAnimationRenderer->GetTransform().GetForwardVector() * Len);
	
	FBXStaticRenderer->GetTransform().SetLocalRotation({ 0.f,m_fAngle,0.f });

}







//후크 공격


void Player::HookAttStart(const StateInfo& _Info)
{

//애니메이션 변경
	FBXAnimationRenderer->ChangeAnimation("Player_Hook");


}

void Player::HookAttEnd(const StateInfo& _Info)
{
	//후크 삭제

	m_bHookEndcheck = false;
	m_bHookHitcheck = false;
}

void Player::HookAttUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (m_bHookEndcheck)
	{
		StateManager.ChangeState("Idle");
	}


	if (m_bHookHitcheck)
	{
		
	/*	Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::PlayerHookTrail, CollisionType::CT_OBB,
			std::bind(&Player::TrailCollision, this, std::placeholders::_1, std::placeholders::_2)
		);*/

		FBXAnimationRenderer->ChangeAnimation("Player_Hook_Fly");
		m_fSpeed = 1500.f;
		float4 MoveDir = FBXAnimationRenderer->GetTransform().GetForwardVector();
		GetTransform().SetWorldMove(MoveDir * m_fSpeed * _DeltaTime);
	}

	//대기 or  이동

}













void Player::SlideStart(const StateInfo& _Info)
{
	m_fSlideSpeed = 700.f;
	m_bSWASlidecheck = false;
	FBXAnimationRenderer->ChangeAnimation("Player_Roll");
}

void Player::SlideEnd(const StateInfo& _Info)
{


	//슬라이드 끝나자 마자 공격 불가
	m_bSAttccheck = true;

	m_bSWASlidecheck = false;
	m_bSlideCCheck = true;
	m_fSlideSpeed = 700.f;
}

void Player::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir = FBXAnimationRenderer->GetTransform().GetForwardVector();


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

	

}





void Player::SlideAttStart(const StateInfo& _Info)
{
	FBXAnimationRenderer->ChangeAnimation("Player_SlideAtt");
	float4 MyWorldPos = GetTransform().GetWorldPosition();
	//float4 RenderFoward = FBXAnimationRenderer->GetTransform().GetForwardVector();
	//RenderFoward = RenderFoward * 100.f;


	//RenderFoward = MyWorldPos + RenderFoward;
	MyWorldPos.y -= 20.f;
	m_CSWAttSlide = GetLevel()->CreateActor<PlayerSWAttSlide>(OBJECTORDER::PlayerAtt);
	m_CSWAttSlide.lock()->GetTransform().SetLocalPosition(MyWorldPos);
	m_CSWAttSlide.lock()->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());

}

void Player::SlideAttEnd(const StateInfo& _Info)
{

	m_CSWAttSlide.lock()->Death();

	
}

void Player::SlideAttUpdate(float _DeltaTime, const StateInfo& _Info)
{


	

	float4 MoveDir = FBXAnimationRenderer->GetTransform().GetForwardVector();

	GetTransform().SetWorldMove(MoveDir * m_fSlideSpeed * _DeltaTime);
	m_CSWAttSlide.lock()->GetTransform().SetWorldMove(MoveDir * m_fSlideSpeed * _DeltaTime);

}


void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{


	FBXAnimationRenderer->ChangeAnimation("Player_Walk");


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
	else
	{



			//키 같이 입력
		if (true == GameEngineInput::GetInst()->IsPress("PlayerRight") && true == GameEngineInput::GetInst()->IsPress("PlayerF"))
		{

			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });

		}
		else if (true == GameEngineInput::GetInst()->IsPress("PlayerRight") && true == GameEngineInput::GetInst()->IsPress("PlayerB"))
		{

			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,135.f,0.f });

		}
		else if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") && true == GameEngineInput::GetInst()->IsPress("PlayerF"))
		{
			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,315.f,0.f });

		}
		else if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") && true == GameEngineInput::GetInst()->IsPress("PlayerB"))
		{

			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,225.f,0.f });
		}



		else if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
		{
			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,270.f,0.f });

		}

		else if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
		{
			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,90.f,0.f });

		}
		else if (true == GameEngineInput::GetInst()->IsPress("PlayerF"))
		{

			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,0.f,0.f });


		}
		else if (true == GameEngineInput::GetInst()->IsPress("PlayerB"))
		{

			FBXAnimationRenderer->GetTransform().SetLocalRotation({ 0.f,180.f,0.f });



		}
		float4 MoveDir = FBXAnimationRenderer->GetTransform().GetForwardVector();
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

			if (m_Info.Weapontype != WEAPONTYPE::Sword )
			{

				if (m_Info.Weapontype == WEAPONTYPE::Arrow)
				{
					if (m_Info.ArrowCount > 0)
					{
						StateManager.ChangeState("ArrowAtt");
					}
				}
				else if(m_Info.Weapontype == WEAPONTYPE::Hook)
				{

					StateManager.ChangeState("ArrowAtt");
				}
				else if (m_Info.Weapontype == WEAPONTYPE::Fire)
				{

					StateManager.ChangeState("ArrowAtt");
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

CollisionReturn Player::CollisionNPC(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


	if (!m_bUpgradeUICoolcheck)
	{
		if (m_bUpgradeUIcheck)
		{
			m_bUpgradeUIcheck = false;


			UpgradeUI.lock()->Off();
			m_bShopCameraActionCheck = false;
		}
		else
		{
			m_bUpgradeUIcheck = true;
			m_bShopCameraActionCheck = true;
			UpgradeUI.lock()->On();
		}

	}
	
		
	


	return CollisionReturn::ContinueCheck;
}

CollisionReturn Player::MonsterCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{
	return CollisionReturn::Break;
}

void Player::Update(float _DeltaTime)
{


	m_fStaticCollDir = FBXAnimationRenderer->GetTransform().GetForwardVector();




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






	Collision->GetTransform().SetLocalRotation(FBXAnimationRenderer->GetTransform().GetLocalRotation());
	
	float4 WoprldPos = GetTransform().GetWorldPosition();

	float4 ScreenPos = GetLevel()->GetMainCameraActor()->GetCameraComponent()->GetWorldPositionToScreenPosition(WoprldPos);

	

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
	
	if (true == GameEngineInput::GetInst()->IsPress("NPCClick"))
	{
		Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::NPC, CollisionType::CT_OBB,
			std::bind(&Player::CollisionNPC,this, std::placeholders::_1, std::placeholders::_2)
		);

		m_bUpgradeUICoolcheck = true;
	}
	if (true == GameEngineInput::GetInst()->IsUp("NPCClick"))
	{
		m_bUpgradeUICoolcheck = false;
	}






	//float4 WorldPos = GetTransform().GetWorldPosition();
	//float4 CameraWorldPos = WorldPos;



	//CameraWorldPos.y += 1700.f;
	//CameraWorldPos.z -= 1700.f;


	//GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraWorldPos);


	if (m_bLogoLevelCheck)
	{
	
		return;
	}
	



	float4 WorldPos;
	if (!m_bArrowCameraCheck)
	{
		FBXStaticRenderer->Off();
		if (m_bShopCameraActionCheck)
		{
			m_fCameraLenZ = 700.f;
			m_fCameraLenY = 700.f;
			
			GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 35.f,0.f,0.f });
			

		}
		else
		{
			m_fCameraLenZ = 1700.f;
			m_fCameraLenY = 1700.f;
			
			GetLevel()->GetMainCameraActorTransform().SetWorldRotation({ 45.f,0.f,0.f });

		}


		WorldPos = GetTransform().GetWorldPosition();
	}
	else
	{
		FBXStaticRenderer->On();
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

	
	

	if (m_bUpgradeUIcheck)
	{
		return;
	}

	StateManager.Update(_DeltaTime);


}

void Player::AniIdleEnd(const GameEngineRenderingEvent& _Data)
{


	std::string A = " 아이들 끝 ";

	GameEngineDebug::OutPutString(A);



}
void Player::AniPlayer_Att_Left(const GameEngineRenderingEvent& _Data)
{

	std::string A = " 3타 끝 ";

	GameEngineDebug::OutPutString(A);


	
	StateManager.ChangeState("Idle");
//	FBXAnimationRenderer->ChangeAnimation("Player_Idle2");




}
void Player::AniPlayer_Att_R(const GameEngineRenderingEvent& _Data)
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
void Player::AniPlayer_Att1(const GameEngineRenderingEvent& _Data)
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
void Player::AniPlayer_Att2(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Idle");
}
void Player::AniPlayer_Roll(const GameEngineRenderingEvent& _Data)
{

	if (m_bSWASlidecheck)
	{
		StateManager.ChangeState("SlideAtt");
	}
	else
	{
		StateManager.ChangeState("Idle");
	}



}
void Player::AniPlayer_Idle2(const GameEngineRenderingEvent& _Data)
{

	std::string A = " 아이들 끝 ";

	GameEngineDebug::OutPutString(A);

}
void Player::AniPlayer_SlideAtt(const GameEngineRenderingEvent& _Data)
{
	StateManager.ChangeState("Idle");
}




void Player::UIOff()
{
	MainUI.lock()->Off();
	
}
void Player::UIOn()
{
	MainUI.lock()->On();

}


CollisionReturn Player::TrailCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other)
{


//	_Other->GetParent()->Death();


	return CollisionReturn::Break;
}


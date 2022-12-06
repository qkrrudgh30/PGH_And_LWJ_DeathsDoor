#include "PreCompile.h"
#include "UnitBase.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>
#include <GameEngineCore/GameEngineFBXAnimationRenderer.h>
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

#include <array>

UnitBase::UnitBase() :
	m_fLifeTime(0.f)
	,m_fSpeed(0.f)
	,Renderer()
	,FBXStaticRenderer()
	,Collision()
	,AttCollision()
	, StateManager()
	, m_Info()
	, m_fHitPos()
	, m_bHitCheck()
	, m_fHitDir()
	, hitTime()
	, m_fHitTime()
	, m_bhitCheck()
	, mfPaperburnDeathTime(2.f)
	, mPaperBurnInfo{}
	, mbOnce(false)
	, mbOnDeath(false)
{
	m_Info.Dammage = 3;
	m_Info.Gold = 1000;
	m_Info.m_Hp = 8;
	m_Info.ArrowCount = 4;
	m_Info.m_MaxHp = 8;
	m_Info.Weapontype = WEAPONTYPE::Sword;
}

UnitBase::~UnitBase() 
{
}


void UnitBase::BaseUpdate(float _DeltaTime)
{
	if (ShakeCheck)
	{
		ShakeTime += _DeltaTime;
		ShakeTCheck += _DeltaTime;


		float4 CamRot  = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();


		if (ShakeTCheck >= 0.07f)
		{
			ShakeTCheck -= 0.07f;
			ShakeDirCheck = !ShakeDirCheck;
		}

		if (ShakeDirCheck)
		{
			CamRot.x += ShakeForce * _DeltaTime;

		}
		else
		{
			CamRot.x -= ShakeForce * _DeltaTime;

		}
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CamRot);


		
		if (ShakeMaxTime <= ShakeTime)
		{
			ShakeCheck = false;
			ShakeTime = 0.f;
			ShakeMaxTime = 0.f;
			ShakeDirCheck = false;
			ShakeForce = 1000.f;
			ShakeTCheck = 0.f;
			//GetLevel()->GetMainCameraActorTransform().SetWorldRotation(CameraLastDir);
		}
	}

	
}


void UnitBase::CameraShake(float _Time)
{
	ShakeDirCheck = false;
	ShakeForce = 1000.f;
	ShakeTCheck = 0.f;
	ShakeMaxTime = _Time;
	ShakeTime = 0.f;
	ShakeCheck = true;
	//CameraLastDir = GetLevel()->GetMainCameraActorTransform().GetWorldRotation();

}

void UnitBase::InitializePaperBurn(std::shared_ptr<GameEngineFBXAnimationRenderer>& _sptrFBXAnimationRenderer)
{
	size_t uMeshCount = _sptrFBXAnimationRenderer->GetAllRenderUnit().size();
	std::vector<size_t> vuSubsetCount;
	vuSubsetCount.resize(uMeshCount, 0);
	for (size_t i = 0; i < uMeshCount; ++i)
	{
		vuSubsetCount[i] = _sptrFBXAnimationRenderer->GetAllRenderUnit()[i].size();
	}

	for (size_t i = 0; i < uMeshCount; ++i)
	{
		for (size_t j = 0; j < vuSubsetCount[i]; ++j)
		{
			_sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].ShaderResources.SetConstantBufferLink("PaperBurnInfo", mPaperBurnInfo);
			_sptrFBXAnimationRenderer->GetAllRenderUnit()[i][j].ShaderResources.SetTexture("CloudTexture", "CloudTexture.png");
		}
	}
}

void UnitBase::InitializePaperBurn(std::shared_ptr<GameEngineFBXStaticRenderer>& _sptrFBXStaticRenderer)
{
	size_t uMeshCount = _sptrFBXStaticRenderer->GetAllRenderUnit().size();
	std::vector<size_t> vuSubsetCount;
	vuSubsetCount.resize(uMeshCount, 0);
	for (size_t i = 0; i < uMeshCount; ++i)
	{
		vuSubsetCount[i] = _sptrFBXStaticRenderer->GetAllRenderUnit()[i].size();
	}

	for (size_t i = 0; i < uMeshCount; ++i)
	{
		for (size_t j = 0; j < vuSubsetCount[i]; ++j)
		{
			_sptrFBXStaticRenderer->GetAllRenderUnit()[i][j].ShaderResources.SetConstantBufferLink("PaperBurnInfo", mPaperBurnInfo);
			_sptrFBXStaticRenderer->GetAllRenderUnit()[i][j].ShaderResources.SetTexture("CloudTexture", "CloudTexture.png");
		}
	}
}

void UnitBase::SetPaperBurnInfo(unsigned int _uOnOffPaperBurn, float _fEffectTime)
{
	mPaperBurnInfo.muOnOffPaperBurn = _uOnOffPaperBurn;
	mPaperBurnInfo.mfEffectTime = _fEffectTime;
}

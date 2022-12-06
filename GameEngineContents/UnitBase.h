#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalContentsValue.h"

struct PaperBurnInfo
{
	unsigned int	muOnOffPaperBurn;
	float			mfEffectTime;
	float			mfPadding1;
	float			mfPadding2;
};



// Ό³Έν :
class GameEngineFBXStaticRenderer;
class UnitBase : public GameEngineActor
{
public:
	// constrcuter destructer
	UnitBase();
	~UnitBase();

	// delete Function
	UnitBase(const UnitBase& _Other) = delete;
	UnitBase(UnitBase&& _Other) noexcept = delete;
	UnitBase& operator=(const UnitBase& _Other) = delete;
	UnitBase& operator=(UnitBase&& _Other) noexcept = delete;

protected:
	void BaseUpdate(float _DeltaTime);

public:
	std::shared_ptr < GameEngineDefaultRenderer> Renderer;
	std::shared_ptr < GameEngineFBXStaticRenderer> FBXStaticRenderer;
	std::shared_ptr <GameEngineFBXAnimationRenderer> FBXAnimationRenderer;
	std::shared_ptr < GameEngineTextureRenderer> TexRenderer;
	std::shared_ptr < GameEngineCollision> Collision;
	std::shared_ptr < GameEngineCollision> AttCollision;
	GameEngineRenderingEvent Event;
public:
	GameEngineStateManager StateManager;



public :
	float4 GetDegree3D(const float4& _Left, const float4& _Right)
	{
		float4 v3 = _Right - _Left;
	
		float xAngle = atan2(v3.y, v3.z) * 180 / GameEngineMath::PI;
		float yAngle = atan2(v3.x, -v3.z) * 180 / GameEngineMath::PI;
		float zAngle = atan2(v3.y, -v3.x) * 180 / GameEngineMath::PI;


		if (_Right.z < _Left.z)
		{
			yAngle = 360.f - yAngle;
			xAngle = 360.f - xAngle;
		}
		if (_Right.x < _Left.x)
		{
			yAngle = 360.f - yAngle;
			zAngle = 360.f - zAngle;
		}




		float4 Result = { xAngle , yAngle, zAngle };

		
		return Result;
	}


	float DirToRot(float4 u, float4 v)
	{

		u.y = -u.z;
		v.y = -v.z;


		u.z = 0.f;
		u.w = 0.f;

		v.z = 0.f;
		v.w = 0.f;

		float Angle = float4::VectorXYtoDegree(v, u);

		Angle += 90.f;

		if (Angle >= 360.f)
		{
			Angle -= 360.f;
		}
		else if (Angle <= 0.f)
		{
			Angle += 360.f;
		}

		return Angle;

	}
	

public:
	UINFO	m_Info;
	float m_fLifeTime;
	float m_fSpeed;


	float4 m_fHitPos = {0};
	bool m_bHitCheck = false;
	float4 m_fHitDir = {0};
	float hitTime = 0.f;


	float m_fHitTime = 0.f;
	bool m_bhitCheck = false;

public:
	void CameraShake(float _Time);

	void InitializePaperBurn(std::shared_ptr <GameEngineFBXAnimationRenderer>& _sptrFBXAnimationRenderer);
	void SetPaperBurnInfo(unsigned int _uOnOffPaperBurn, float _fEffectTime);

	

private:
	float ShakeMaxTime = 0.f;
	float ShakeTime = 0.f;

	float ShakeForce = 1000.f;
	float ShakeTCheck = 0.f;
	bool ShakeDirCheck = false;


	bool ShakeCheck = false;

	float4 CameraLastDir = {};

protected:
	PaperBurnInfo mPaperBurnInfo;
	float mfPaperburnDeathTime;
	bool mbOnce;
	bool mbOnDeath;

	
	
};


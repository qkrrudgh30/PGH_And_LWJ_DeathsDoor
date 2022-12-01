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


	float4 fromtwovectors(float4 u, float4 v)
	{
		float norm_u_norm_v = sqrt((float4:: DotProduct3D(u, u)) * (float4::DotProduct3D(v, v)));
		float real_part = norm_u_norm_v + (float4::DotProduct3D(u, v));
		float4 w;

		if (real_part < 1.e-6f * norm_u_norm_v)
		{
		
			real_part = 0.0f;
			w = abs(u.x) > abs(u.z) ? float4(-u.y, u.x, 0.f)
				: float4(0.f, -u.z, u.y);
		}
		else
		{
		
			w = float4::Cross3D(u, v);
		}

		return (float4(real_part, w.x, w.y, w.z)).Normalize3DReturn();
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


private:
	float ShakeMaxTime = 0.f;
	float ShakeTime = 0.f;

	float ShakeForce = 1000.f;
	float ShakeTCheck = 0.f;
	bool ShakeDirCheck = false;


	bool ShakeCheck = false;

	float4 CameraLastDir = {};

	PaperBurnInfo mPaperBurnInfo;


};


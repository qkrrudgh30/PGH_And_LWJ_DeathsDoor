#pragma once
#include "GameEngineMath.h"
#include <DirectXCollision.h>
#include <GameEngineBase/GameEngineDebugObject.h>
#include <list>

enum class CollisionType
{
	CT_POINT2D,
	CT_SPHERE2D, 
	CT_AABB2D, 
	CT_OBB2D, 
	CT_POINT,
	CT_SPHERE, // 정방원
	CT_AABB, // 회전하지 않은 박스
	CT_OBB, // 회전한 박스
	CT_MAX
};

class CollisionData
{
	friend class GameEngineTransform;

	union 
	{
		DirectX::BoundingSphere SPHERE;
		DirectX::BoundingBox AABB;
		DirectX::BoundingOrientedBox OBB;
	};

	CollisionData() 
		: OBB()
	{

	}
};

struct TransformData
{
	float4 LocalPosition;
	float4 LocalRotation;
	float4 LocalScaling;

	float4 WorldPosition;
	float4 WorldRotation;
	float4 WorldScaling;

	float4x4 LocalPositionMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalScalingMatrix;

	float4x4 LocalWorldMatrix;
	float4x4 WorldWorldMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;

	float4x4 WorldViewMatrix;
	float4x4 WorldViewProjectionMatrix;

public:
	TransformData() :
		LocalScaling(float4::ONE)
		, LocalPosition(float4::ZERO)
		, LocalRotation(float4::ZERO)
		, WorldScaling(float4::ONE)
		, WorldPosition(float4::ZERO)
		, WorldRotation(float4::ZERO)
	{}
};


// 설명 :
class GameEngineTransform : public GameEngineDebugObject
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;


public:
	inline void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(Data.LocalScaling + _Value);
	}

	inline void SetLocalScale(const float4& _Value)
	{
		CalculateWorldScale(_Value);
	}

	inline void SetLocalRotation(const float4& _Value)
	{
		CalculateWorldRotation(_Value);
	}

	inline void SetLocalPosition(const float4& _Value)
	{
		CalculateWorldPosition(_Value);
	}

	inline void SetWorldScale(const float4& _World)
	{
		float4 Local = _World;
		if (nullptr != Parent)
		{
			Local = _World / Parent->Data.WorldScaling;
		}

		CalculateWorldScale(Local);
	}

	inline void SetAddWorldRotation(const float4& _World)
	{
		SetWorldRotation(Data.WorldRotation + _World);
	}

	inline void SetWorldRotation(const float4& _World)
	{
		float4 Local = _World;
		if (nullptr != Parent)
		{
			Local = _World - Parent->Data.WorldRotation;
		}

		CalculateWorldRotation(Local);
	}

	inline void SetWorldPosition(const float4& _World)
	{
		float4 Local = _World;
		if (nullptr != Parent)
		{
			// 부모의 역행렬을 곱해서 
			Local = _World * Parent->Data.WorldWorldMatrix.InverseReturn();
		}


		CalculateWorldPosition(Local);
	}

	inline void SetLocalRotate(const float4& _Value)
	{
		SetLocalRotation(Data.LocalRotation + _Value);
	}

	inline void SetLocalMove(const float4& _Value)
	{
		SetLocalPosition(Data.LocalPosition + _Value);
	}

	inline void SetWorldForwardMove(const float Speed, const float DeltaTime)
	{
		SetWorldPosition(Data.WorldPosition + (GetForwardVector() * Speed * DeltaTime));
	}

	inline void SetWorldBackMove(const float Speed, const float DeltaTime)
	{
		SetWorldPosition(Data.WorldPosition + (GetBackVector() * Speed * DeltaTime));
	}

	inline void SetWorldUpMove(const float Speed, const float DeltaTime)
	{
		SetWorldPosition(Data.WorldPosition + (GetUpVector() * Speed * DeltaTime));
	}

	inline void SetWorldDownMove(const float Speed, const float DeltaTime)
	{
		SetWorldPosition(Data.WorldPosition + (GetDownVector() * Speed * DeltaTime));
	}

	inline void SetWorldLeftMove(const float Speed, const float DeltaTime)
	{
		SetWorldPosition(Data.WorldPosition + (GetLeftVector() * Speed * DeltaTime));
	}

	inline void SetWorldRightMove(const float Speed, const float DeltaTime)
	{
		SetWorldPosition(Data.WorldPosition + (GetRightVector() * Speed * DeltaTime));
	}

	inline void SetWorldMove(const float4& _Value)
	{
		SetWorldPosition(Data.WorldPosition + _Value);
	}

	inline float4 GetWorldScale() const
	{
		return Data.WorldScaling;
	}

	inline float4 GetLocalScale() const
	{
		return Data.LocalScaling;
	}
	inline float4 GetLocalRotation() const
	{
		return Data.LocalRotation;
	}
	inline float4 GetLocalPosition() const
	{
		return Data.LocalPosition;
	}

	inline float4 GetWorldPosition() const
	{
		return Data.WorldPosition;
	}

	inline float4x4 GetLocalWorld() const
	{
		return Data.LocalWorldMatrix;
	}

	inline float4x4 GetWorldWorld() const
	{
		return Data.WorldWorldMatrix;
	}

	inline float4x4 GetWorldViewProjection() const
	{
		return Data.WorldViewProjectionMatrix;
	}

	inline float4 GetForwardVector() const
	{
		return Data.WorldWorldMatrix.ArrV[2].NormalizeReturn();
	}

	inline float4 GetBackVector() const
	{
		return -(Data.WorldWorldMatrix.ArrV[2].NormalizeReturn());
	}

	inline float4 GetUpVector() const
	{
		return Data.WorldWorldMatrix.ArrV[1].NormalizeReturn();
	}

	inline float4 GetDownVector() const
	{
		return -(Data.WorldWorldMatrix.ArrV[1].NormalizeReturn());
	}

	inline float4 GetRightVector() const
	{
		return Data.WorldWorldMatrix.ArrV[0].NormalizeReturn();
	}

	inline float4 GetLeftVector() const
	{
		return -(Data.WorldWorldMatrix.ArrV[0].NormalizeReturn());
	}

	void CalculateWorld();

	void CalculateWorldViewProjection();

	void DetachTransform();

	void SetParentTransform(GameEngineTransform& _Child);

	void PixLocalNegativeX();

	void PixLocalPositiveX();

	// void PushChild(GameEngineTransform* _Child);

	void SetView(const float4x4& _Mat)
	{
		Data.ViewMatrix = _Mat;
	}

	void SetProjection(const float4x4& _Mat)
	{
		Data.ProjectionMatrix = _Mat;
	}

	const TransformData& GetTransformData() const
	{
		return Data;
	}

	void Copy(const GameEngineTransform& _Trans);

protected:

private:
	GameEngineTransform* Parent;
	std::list<GameEngineTransform*> Childs;

	TransformData Data;

	void CalculateWorldScale(const float4& _Local)
	{
		Data.LocalScaling = _Local;
		Data.LocalScaling.w = 0.0f; // 이동을 적용받지 않기.
		// DirectX::XMVector3TransformCoord // 1로 곱하기
		// DirectX::XMVector3TransformNormal // 0넣고 곱하기

		if (nullptr != Parent)
		{
			Data.WorldScaling = Data.LocalScaling * Parent->Data.WorldScaling;
		}
		else
		{
			Data.WorldScaling = Data.LocalScaling;
		}


		Data.LocalScalingMatrix.Scale(Data.LocalScaling);
		CalculateWorld();

		for (GameEngineTransform* Child : Childs)
		{
			Child->CalculateWorldScale(Child->Data.LocalScaling);
			Child->CalculateWorldPosition(Child->Data.LocalPosition);
		}

		CollisionDataSetting();
	}
	void CalculateWorldRotation(const float4& _Local)
	{
		Data.LocalRotation = _Local;
		Data.LocalRotation.w = 0.0f; // 이동을 적용받지 않기.

		if (nullptr != Parent)
		{
			Data.WorldRotation = Data.LocalRotation + Parent->Data.WorldRotation;
		}
		else
		{
			Data.WorldRotation = Data.LocalRotation;
		}

		Data.LocalRotationMatrix.RotationDegree(Data.LocalRotation);
		CalculateWorld();

		for (GameEngineTransform* Child : Childs)
		{
			Child->CalculateWorldRotation(Child->Data.LocalRotation);
			Child->CalculateWorldPosition(Child->Data.LocalPosition);
		}

		CollisionDataSetting();
	}

	void CalculateWorldPosition(const float4& _Local)
	{
		Data.LocalPosition = _Local;
		Data.LocalPosition.w = 1.0f; // 이동을 적용받기 위해서.

		if (nullptr != Parent)
		{
			Data.WorldPosition = Data.LocalPosition * Parent->Data.WorldWorldMatrix;
		}
		else
		{
			Data.WorldPosition = Data.LocalPosition;
		}

		Data.LocalPositionMatrix.Position(Data.LocalPosition);
		CalculateWorld();

		for (GameEngineTransform* Child : Childs)
		{
			Child->CalculateWorldPosition(Child->Data.LocalPosition);
		}

		CollisionDataSetting();
	}

	CollisionData CollisionDataObject;

	void CollisionScaleSetting();
	void CollisionRotationSetting();
	void CollisionPositionSetting();
	void CollisionDataSetting();

	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}


/////////////////////////// 충돌관련
public:
	static bool SphereToSphere(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

	static bool AABBToAABB(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

	static bool OBBToOBB(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

	static bool Sphere2DToSphere2D(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

	static bool AABB2DToAABB2D(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

	static bool OBB2DToOBB2D(const GameEngineTransform& _Left, const GameEngineTransform& _Right);
};


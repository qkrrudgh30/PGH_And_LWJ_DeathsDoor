#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent(nullptr)
	, CollisionDataObject()
{
	CollisionDataSetting();
}

GameEngineTransform::~GameEngineTransform() 
{
}


void GameEngineTransform::CalculateWorld()
{
	//if (IsDebug())
	//{
	//	int a = 0;
	//}

	Data.LocalWorldMatrix = Data.LocalScalingMatrix * Data.LocalRotationMatrix * Data.LocalPositionMatrix;

	if (nullptr != Parent)
	{
		// Parent 컴포넌트일 경우에는 액터의 트랜스폼을 부모로 가지게 된다.
		Data.WorldWorldMatrix = Data.LocalWorldMatrix * Parent->GetWorldWorld();
	}
	else 
	{
		Data.WorldWorldMatrix = Data.LocalWorldMatrix;
	}

	for (GameEngineTransform* Child : Childs)
	{
		Child->CalculateWorld();
	}
}

void GameEngineTransform::CalculateWorldViewProjection()
{
	Data.WorldViewMatrix = Data.WorldWorldMatrix * Data.ViewMatrix;
	Data.WorldViewProjectionMatrix = Data.WorldViewMatrix * Data.ProjectionMatrix;

	//float4 Pos = { 0.5f, 0.5f, 0.0f, 1.0f };

	//Pos *= Data.WorldViewProjectionMatrix;

	//Pos /= Pos.w;

}

void GameEngineTransform::DetachTransform()
{
	if (nullptr == Parent)
	{
		return;
	}

	Parent->Childs.remove(this);
	Parent = nullptr;

}

void GameEngineTransform::SetParentTransform(GameEngineTransform& _Parent)
{
	if (nullptr != Parent)
	{
		// 나는 삭제되고
		Parent->Childs.remove(this);
		Parent = nullptr;
	}

	Parent = &_Parent;
	_Parent.Childs.push_back(this);

	SetLocalScale(Data.LocalScaling);
	SetLocalRotation(Data.LocalRotation);
	SetLocalPosition(Data.LocalPosition);
}


void GameEngineTransform::PixLocalNegativeX()
{
	if (0.0f > Data.LocalScaling.x)
	{
		return;
	}

	Data.LocalScaling.x = -Data.LocalScaling.x;
	
	SetLocalScale(Data.LocalScaling);
}

void GameEngineTransform::PixLocalPositiveX()
{
	if (0.0f < Data.LocalScaling.x)
	{
		return;
	}

	// abs 어떤 숫자를 넣으면 무조건 양수(절대값)으로 변경해주는 함수.
	Data.LocalScaling.x = abs(Data.LocalScaling.x);

	SetLocalScale(Data.LocalScaling);
}

void GameEngineTransform::Copy(const GameEngineTransform& _Trans)
{
	Data = _Trans.Data;
	CollisionDataObject = _Trans.CollisionDataObject;
	Parent = _Trans.Parent;
	Childs = _Trans.Childs;

	CalculateWorldRotation(Data.LocalRotation);
	CalculateWorldScale(Data.LocalScaling);
	CalculateWorldPosition(Data.LocalPosition);
	CalculateWorld();
}
#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"

GameEngineActor::GameEngineActor()
	: ParentLevel(nullptr)
	, IsLevelOver(false)
{

}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::Start() {}
void GameEngineActor::Update(float _DeltaTime) {}
void GameEngineActor::End() {}

void GameEngineActor::DetachObject()
{
	if (nullptr == GetParent())
	{
		return;
	}

	GameEngineUpdateObject::DetachObject();

	GetTransform().DetachTransform();

	if (false == IsDeath())
	{
		GetLevel()->PushActor(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()), this->GetOrder());
	}
}

void GameEngineActor::SetParent(std::shared_ptr<GameEngineUpdateObject> _Parent)
{
	if (nullptr == GetParent())
	{
		GetLevel()->RemoveActor(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
	}

	GameEngineUpdateObject::SetParent(_Parent);

	{
		std::shared_ptr<GameEngineTransformBase> Actor = nullptr;
		if (Actor = std::dynamic_pointer_cast<GameEngineTransformBase>(_Parent))
		{
			GetTransform().SetParentTransform(Actor->GetTransform());
			return;
		}
	}

	MsgBoxAssert("트랜스폼이 없는 컴포넌트에 트랜스폼이 있는 부모를 붙이려고 했습니다.");
}


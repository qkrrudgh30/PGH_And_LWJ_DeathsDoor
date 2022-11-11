#include "PreCompile.h"
#include "GameEngineTransformComponent.h"

GameEngineTransformComponent::GameEngineTransformComponent() 
{
}

GameEngineTransformComponent::~GameEngineTransformComponent() 
{
}

void GameEngineTransformComponent::DetachObject() 
{
	// 오브젝트에서 떼내고
	GameEngineUpdateObject::DetachObject();

	// 트랜스폼에서 떼낸다.
	GetTransform().DetachTransform();
}

void GameEngineTransformComponent::SetParent(std::shared_ptr<GameEngineUpdateObject> _Object)
{
	GameEngineUpdateObject::SetParent(_Object);

	{
		std::shared_ptr<GameEngineTransformBase> Actor = nullptr;
		if (Actor = std::dynamic_pointer_cast<GameEngineTransformBase>(_Object))
		{
			GetTransform().SetParentTransform(Actor->GetTransform());
			return;
		}
	}

	MsgBoxAssert("트랜스폼이 없는 컴포넌트에 트랜스폼이 있는 부모를 붙이려고 했습니다.");
}
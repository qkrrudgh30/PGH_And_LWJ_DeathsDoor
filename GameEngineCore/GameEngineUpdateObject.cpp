#include "PreCompile.h"
#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: IsUpdate_(true)
	, IsDeath_(false)
	, IsReleaseUpdate_(false)
	, AccTime_(0.0f)
	, DeathTime_(0.0f)
	, Order_(0)
	, Parent(nullptr)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}

void GameEngineUpdateObject::ReleaseHierarchy()
{
	//std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator StartIter = Childs.begin();
	//std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator EndIter = Childs.end();

	//for (; StartIter != EndIter; ++StartIter)
	//{
	//	(*StartIter)->ReleaseHierarchy();
	//}

	// delete this;
}

void GameEngineUpdateObject::SetParent(GameEngineUpdateObject* _Parent) 
{
	DetachObject();

	Parent = _Parent;
	Parent->Childs.push_back(shared_from_this());
}

void GameEngineUpdateObject::DetachObject()
{
	if (nullptr != Parent)
	{
		Parent->Childs.remove(shared_from_this());
	}
}


void GameEngineUpdateObject::AllUpdate(float _DeltaTime)
{
	AddAccTime(_DeltaTime);
	ReleaseUpdate(_DeltaTime);
	Update(GameEngineTime::GetInst()->GetTimeScale(GetOrder()) * _DeltaTime);

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		//Com->AddAccTime(_DeltaTime);
		//Com->ReleaseUpdate(_DeltaTime);
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllUpdate(_DeltaTime);
	}
}

void GameEngineUpdateObject::AllLevelStartEvent()
{
	/*this->*/LevelStartEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllLevelStartEvent();
	}
}
void GameEngineUpdateObject::AllLevelEndEvent()
{
	/*this->*/LevelEndEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllLevelEndEvent();
	}
}

void GameEngineUpdateObject::AllOnEvent()
{
	/*this->*/OnEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllOnEvent();
	}
}

void GameEngineUpdateObject::AllOffEvent()
{
	/*this->*/OffEvent();

	for (std::shared_ptr<GameEngineUpdateObject> Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllOffEvent();
	}
}


void GameEngineUpdateObject::ReleaseObject(
	std::list<std::shared_ptr<GameEngineUpdateObject>>& _RelaseList)
{
	if (true == IsDeath())
	{
		DetachObject();
		_RelaseList.push_back(shared_from_this());
		return;
	}

	std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator StartIter = Childs.begin();
	std::list<std::shared_ptr<GameEngineUpdateObject>>::iterator EndIter = Childs.end();

	for ( ; StartIter != EndIter;)
	{
		if (true == (*StartIter)->IsDeath())
		{
			_RelaseList.push_back((*StartIter));

			std::shared_ptr<GameEngineUpdateObject> DeleteObject = (*StartIter);
			++StartIter;
			DeleteObject->DetachObject();
			continue;
		}

		(*StartIter)->ReleaseObject(_RelaseList);
		++StartIter;
	}
}
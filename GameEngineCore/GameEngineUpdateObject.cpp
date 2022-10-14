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
	std::list<GameEngineUpdateObject*>::iterator StartIter = Childs.begin();
	std::list<GameEngineUpdateObject*>::iterator EndIter = Childs.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->ReleaseHierarchy();
	}

	delete this;
}

void GameEngineUpdateObject::SetParent(GameEngineUpdateObject* _Parent) 
{
	DetachObject();

	Parent = _Parent;
	Parent->Childs.push_back(this);
}

void GameEngineUpdateObject::DetachObject()
{
	if (nullptr != Parent)
	{
		Parent->Childs.remove(this);
	}
}


void GameEngineUpdateObject::AllUpdate(float _DeltaTime)
{
	AddAccTime(_DeltaTime);
	ReleaseUpdate(_DeltaTime);
	Update(GameEngineTime::GetInst()->GetTimeScale(GetOrder()) * _DeltaTime);

	for (GameEngineUpdateObject* Com : Childs)
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

	for (GameEngineUpdateObject* Com : Childs)
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

	for (GameEngineUpdateObject* Com : Childs)
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

	for (GameEngineUpdateObject* Com : Childs)
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

	for (GameEngineUpdateObject* Com : Childs)
	{
		if (false == Com->IsUpdate())
		{
			continue;
		}

		Com->AllOffEvent();
	}
}


void GameEngineUpdateObject::ReleaseObject(
	std::list<GameEngineUpdateObject*>& _RelaseList)
{
	if (true == IsDeath())
	{
		DetachObject();
		_RelaseList.push_back(this);
		return;
	}

	std::list<GameEngineUpdateObject*>::iterator StartIter = Childs.begin();
	std::list<GameEngineUpdateObject*>::iterator EndIter = Childs.end();

	for ( ; StartIter != EndIter;)
	{
		if (true == (*StartIter)->IsDeath())
		{
			_RelaseList.push_back((*StartIter));

			GameEngineUpdateObject* DeleteObject = (*StartIter);
			++StartIter;
			DeleteObject->DetachObject();
			continue;
		}

		(*StartIter)->ReleaseObject(_RelaseList);
		++StartIter;
	}
}
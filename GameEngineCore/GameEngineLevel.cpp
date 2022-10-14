#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineCameraActor.h"
#include "GameEngineCollision.h"
#include "GameEngineGUI.h"
#include "GameEngineCoreDebug.h"
#include "GEngine.h"

GameEngineLevel::GameEngineLevel() 
{
	Cameras.resize(static_cast<unsigned int>(CAMERAORDER::UICAMERA));

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::MAINCAMERA);
	}

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::UICAMERA);
	}
}

GameEngineLevel::~GameEngineLevel() 
{
	for (GameEngineUpdateObject* Object : DeleteObject)
	{
		Object->ReleaseHierarchy();
	}

	DeleteObject.clear();

	// 게임이 끝나거나 이 레벨이 완전히 파괴되는 경우이기 때문에.
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		for (GameEngineActor* Actor : Group.second)
		{
			if (nullptr == Actor)
			{
				continue;
			}

			Actor->ReleaseHierarchy();
		}
	}
}


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		// float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineActor* const Actor : Group.second)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->AllUpdate(_DeltaTime);
		}
	}
}

void GameEngineLevel::ActorLevelStartEvent() 
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineActor* const Actor : Group.second)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}
			// 루트 액터만 뭔가를 하는거죠?
			Actor->AllLevelStartEvent();
		}
	}
}

void GameEngineLevel::ActorLevelEndEvent()
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineActor* const Actor : Group.second)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}
			Actor->AllLevelEndEvent();
		}
	}
}

void GameEngineLevel::PushRenderer(GameEngineRenderer* _Renderer, int _CameraOrder)
{
	// 기존 자신이 있던 자리에서 지우고

	GameEngineCamera* PrevCamera = Cameras[static_cast<UINT>(_Renderer->CameraOrder)];

	PrevCamera->AllRenderer_[_Renderer->GetRenderingOrder()].remove(_Renderer);

	_Renderer->CameraOrder = static_cast<CAMERAORDER>(_CameraOrder);

	GameEngineCamera* NextCamera = Cameras[_CameraOrder];
	// 다른 카메라로 들어갈수도 있습니다.
	Cameras[_CameraOrder]->PushRenderer(_Renderer);
	_Renderer->Camera = NextCamera;
}

void GameEngineLevel::PushCamera(GameEngineCamera* _Camera, int _CameraOrder)
{
	Cameras.resize(_CameraOrder + 1);

	Cameras[_CameraOrder] = _Camera;
}

GameEngineTransform& GameEngineLevel::GetMainCameraActorTransform()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)]->GetActor()->GetTransform();
}


GameEngineCameraActor* GameEngineLevel::GetMainCameraActor()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetUICameraActorTransform()
{
	return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)]->GetActor()->GetTransform();
}


GameEngineCameraActor* GameEngineLevel::GetUICameraActor()
{
	return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)]->GetActor<GameEngineCameraActor>();
}



void GameEngineLevel::Render(float _DelataTime)
{
	{
		if (true == GEngine::IsCollisionDebug())
		{
			std::map<int, std::list<GameEngineCollision*>>::iterator StartGroupIter = AllCollisions.begin();
			std::map<int, std::list<GameEngineCollision*>>::iterator EndGroupIter = AllCollisions.end();
			for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
			{
				std::list<GameEngineCollision*>& Group = StartGroupIter->second;
				std::list<GameEngineCollision*>::iterator GroupStart = Group.begin();
				std::list<GameEngineCollision*>::iterator GroupEnd = Group.end();
				for (; GroupStart != GroupEnd; ++GroupStart)
				{
					if (true == (*GroupStart)->IsUpdate())
					{
						(*GroupStart)->DebugRender();
					}
				}
			}
		}
	}

	GameEngineDevice::RenderStart();

	// 이 사이에서 무언가를 해야 합니다.
	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->Render(_DelataTime);
	}

	// 포스트 이펙트 처리.
	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->GetCameraRenderTarget()->EffectProcess();
	}

	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		GameEngineDevice::GetBackBuffer()->Merge(Cameras[i]->CameraRenderTarget, 0);
	}

	GameEngineDevice::GetBackBuffer()->EffectProcess();


	// 여기서 그려져야 합니다.
	GameEngineDebug::Debug3DRender();

	GameEngineGUI::GUIRender(this, _DelataTime);

	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::PushActor(GameEngineActor* _Actor, int _ObjectGroupIndex)
{
	if (nullptr != _Actor->GetParent())
	{
		MsgBoxAssert("부모가 존재하는 오브젝트는 루트가 될수 없습니다.");
	}

	std::list<GameEngineActor*>& Group = AllActors[_ObjectGroupIndex];

	Group.push_back(_Actor);
}


void GameEngineLevel::Release(float _DelataTime)
{
	// std::shared_ptr <>

	for (GameEngineUpdateObject* Object : DeleteObject)
	{
		Object->ReleaseHierarchy();
	}

	DeleteObject.clear();

	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->Release(_DelataTime);
	}
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator StartGroupIter = AllCollisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator EndGroupIter = AllCollisions.end();

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineCollision*>& Group = StartGroupIter->second;

			std::list<GameEngineCollision*>::iterator GroupStart = Group.begin();
			std::list<GameEngineCollision*>::iterator GroupEnd = Group.end();
			for (; GroupStart != GroupEnd; )
			{
				if (true == (*GroupStart)->IsDeath())
				{
					GroupStart = Group.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}
			}
		}
	}
	std::map<int, std::list<GameEngineActor*>>::iterator StartGroupIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator EndGroupIter = AllActors.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineActor*>& Group = StartGroupIter->second;

		std::list<GameEngineActor*>::iterator GroupStart = Group.begin();
		std::list<GameEngineActor*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseObject(DeleteObject);

			if (true == (*GroupStart)->IsDeath())
			{
				GroupStart = Group.erase(GroupStart);
			}
			else 
			{
				++GroupStart;
			}
			
		}
	}
}

void GameEngineLevel::LevelUpdate(float _DeltaTime)
{
	AddAccTime(_DeltaTime);
	Update(_DeltaTime);
	ActorUpdate(_DeltaTime);
	Render(_DeltaTime);
	Release(_DeltaTime);
}

// 레벨을 이동하는 액터
// 루트인애가 지우려고 여기로 온다고 생각할 겁니다.
void GameEngineLevel::RemoveActor(GameEngineActor* _Actor)
{
	if (AllActors.end() == AllActors.find(_Actor->GetOrder()))
	{
		MsgBoxAssert("이액터를 루트가 아닙니다 삭제할수 없습니다.");
	}

	AllActors[_Actor->GetOrder()].remove(_Actor);
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _Order)
{
	// 기존에 자신이 존재하는 그룹에서 삭제한다.
	AllCollisions[_Collision->GetOrder()].remove(_Collision);

	// 나의 오더를 바꾸고.
	_Collision->SetOrder(_Order);

	// 새로운 그룹에 편입된다.
	AllCollisions[_Collision->GetOrder()].push_back(_Collision);
}

void GameEngineLevel::OverChildMove(GameEngineLevel* _NextLevel)
{
	if (this == _NextLevel)
	{
		return;
	}

	// 플레이 레벨
	
	// 로그인 레벨
	// _NextLevel
	{
		std::map<int, std::list<GameEngineActor*>>::iterator StartGroupIter = AllActors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator EndGroupIter = AllActors.end();

		std::list<GameEngineActor*> OverList;

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineActor*>& Group = StartGroupIter->second;

			std::list<GameEngineActor*>::iterator GroupStart = Group.begin();
			std::list<GameEngineActor*>::iterator GroupEnd = Group.end();
			for (; GroupStart != GroupEnd; )
			{
				if (true == (*GroupStart)->IsLevelOver)
				{
					// 내쪽에서는 삭제되고
					OverList.push_back((*GroupStart));
					GroupStart = Group.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}

			}
		}

		// 오브젝트를 넘기고
		for (GameEngineActor* OverActor : OverList)
		{
			// 이녀석의 부모레벨은
			OverActor->SetLevel(_NextLevel);
			_NextLevel->AllActors[OverActor->GetOrder()].push_back(OverActor);
		}
	}

	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->OverRenderer(_NextLevel->Cameras[i]);
	}

	{
		std::map<int, std::list<GameEngineCollision*>>::iterator StartGroupIter = AllCollisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator EndGroupIter = AllCollisions.end();

		std::list<GameEngineCollision*> OverList;

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineCollision*>& Group = StartGroupIter->second;

			std::list<GameEngineCollision*>::iterator GroupStart = Group.begin();
			std::list<GameEngineCollision*>::iterator GroupEnd = Group.end();
			for (; GroupStart != GroupEnd; )
			{
				if (true == (*GroupStart)->GetRoot<GameEngineActor>()->IsLevelOver)
				{
					// 내쪽에서는 삭제되고
					OverList.push_back((*GroupStart));
					GroupStart = Group.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}

			}
		}

		// 오브젝트를 넘기고
		for (GameEngineCollision* OverActor : OverList)
		{
			_NextLevel->AllCollisions[OverActor->GetOrder()].push_back(OverActor);
		}
	}
}

void GameEngineLevel::AllClear() 
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator StartGroupIter = AllActors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator EndGroupIter = AllActors.end();

		std::list<GameEngineActor*> OverList;

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineActor*>& Group = StartGroupIter->second;
			std::list<GameEngineActor*>::iterator GroupStart = Group.begin();
			std::list<GameEngineActor*>::iterator GroupEnd = Group.end();
			for (; GroupStart != GroupEnd; ++GroupStart)
			{
				delete *GroupStart;
			}
		}
	}

	AllActors.clear();

	Cameras.clear();

	AllCollisions.clear();
}


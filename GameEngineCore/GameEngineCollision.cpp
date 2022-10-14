#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineCoreDebug.h"
#include "GameEngineCore.h"

bool (*GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_MAX)][static_cast<int>(CollisionType::CT_MAX)])(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

class GameEngineCollisionFunctionInit
{
public:
	GameEngineCollisionFunctionInit() 
	{
		memset(GameEngineCollision::CollisionFunction, 0, sizeof(GameEngineCollision::CollisionFunction));

		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_SPHERE)][static_cast<int>(CollisionType::CT_SPHERE)] = &GameEngineTransform::SphereToSphere;
		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_AABB)][static_cast<int>(CollisionType::CT_AABB)] = &GameEngineTransform::AABBToAABB;
		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_OBB)][static_cast<int>(CollisionType::CT_OBB)] = &GameEngineTransform::OBBToOBB;

		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_SPHERE2D)][static_cast<int>(CollisionType::CT_SPHERE2D)] = &GameEngineTransform::Sphere2DToSphere2D;
		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_AABB2D)][static_cast<int>(CollisionType::CT_AABB2D)] = &GameEngineTransform::AABB2DToAABB2D;
		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::CT_OBB2D)][static_cast<int>(CollisionType::CT_OBB2D)] = &GameEngineTransform::OBB2DToOBB2D;
	}

	~GameEngineCollisionFunctionInit() 
	{

	}
};

GameEngineCollisionFunctionInit Inst;

GameEngineCollision::GameEngineCollision() 
	: DebugType(CollisionType::CT_SPHERE)
	, Color(1.0f, 0.0f, 0.0f, 0.5f)
	, eCollisionMode(CollisionMode::Normal)
{
}

GameEngineCollision::~GameEngineCollision() 
{
}


void GameEngineCollision::Start()
{
	DebugCameraOrder = CAMERAORDER::MAINCAMERA;

	GetActor()->GetLevel()->PushCollision(this, GetOrder());
}

void GameEngineCollision::SetUIDebugCamera()
{
	DebugCameraOrder = CAMERAORDER::UICAMERA;
}

void GameEngineCollision::ChangeOrder(int _Order)
{
	GetActor()->GetLevel()->PushCollision(this, _Order);
}

bool GameEngineCollision::IsCollision(CollisionType _ThisType, int _GroupOrder
	, CollisionType _OtherType
	, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Update /*= nullptr*/
	, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Enter /*= nullptr*/
	, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Exit /*= nullptr*/)
{
	if (false == IsUpdate())
	{
		return false;
	}

	int ThisType = static_cast<int>(_ThisType);
	int OtherType = static_cast<int>(_OtherType);

	if (nullptr == GameEngineCollision::CollisionFunction[ThisType][OtherType])
	{
		MsgBoxAssert("아직 만들어지지 않은 콜리전 처리입니다");
	}

	std::map<int, std::list<GameEngineCollision*>>& AllCollisions = GetActor()->GetLevel()->AllCollisions;

	std::list<GameEngineCollision*>& Collisions = AllCollisions[_GroupOrder];

	bool Check = false;

	// [][][]

	for (GameEngineCollision* Collision : Collisions)
	{
		if (Collision == this)
		{
			continue;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		// 충돌 체크를 했다.
		if (true == GameEngineCollision::CollisionFunction[ThisType][OtherType](GetTransform(), Collision->GetTransform()))
		{
			Check = true;
			// 이 충돌체와 충돌했다.
			if (eCollisionMode == CollisionMode::Ex)
			{
				if (CollisionCheck.end() == CollisionCheck.find(Collision))
				{
					// 이 충돌체와는 처음 충돌했다.
					CollisionCheck.insert(Collision);

					if (nullptr != _Enter && CollisionReturn::Break == _Enter(this, Collision))
					{
						return true;
					}

				}
				else 
				{
					if (nullptr != _Update && CollisionReturn::Break == _Update(this, Collision))
					{
						return true;
					}
				}
			}
			else  if (eCollisionMode == CollisionMode::Normal)
			{
				if (nullptr != _Update)
				{
					// 넣어줘야 한다를 명시하는 겁니다.
					if (CollisionReturn::Break == _Update(this, Collision))
					{
						return true;
					}
				}
				else {
					return true;
				}
				// return true; 이부분 잘못됐어요.
			}
		}
		else 
		{
			if (eCollisionMode == CollisionMode::Ex)
			{
				if (CollisionCheck.end() != CollisionCheck.find(Collision))
				{
					if (nullptr != _Exit && CollisionReturn::Break == _Exit(this, Collision))
					{
						return false;
					}

					CollisionCheck.erase(Collision);
				}
			}

		}
	}

	return Check;
}

void GameEngineCollision::DebugRender()
{
	GameEngineCamera* DebugRenderCamera = GetActor()->GetLevel()->Cameras[static_cast<UINT>(DebugCameraOrder)];

	switch (DebugType)
	{
	case CollisionType::CT_POINT2D:
		break;
	case CollisionType::CT_SPHERE2D:
		GameEngineDebug::DrawSphere(GetTransform(), DebugRenderCamera, Color);
		break;
	case CollisionType::CT_AABB2D:
		GameEngineDebug::DrawBox(GetTransform(), DebugRenderCamera, Color);
		break;
	case CollisionType::CT_OBB2D:
		GameEngineDebug::DrawBox(GetTransform(), DebugRenderCamera, Color);
		break;
	case CollisionType::CT_POINT:
		break;
	case CollisionType::CT_SPHERE:
		GameEngineDebug::DrawSphere(GetTransform(), DebugRenderCamera, Color);
		break;
	case CollisionType::CT_AABB:
		GameEngineDebug::DrawBox(GetTransform(), DebugRenderCamera, Color);
		break;
	case CollisionType::CT_OBB:
		GameEngineDebug::DrawBox(GetTransform(), DebugRenderCamera, Color);
		break;
	case CollisionType::CT_MAX:
		break;
	default:
		break;
	}

}
#include "PreCompile.h"
#include "GameEngineTransform.h"
// #include <DirectXCollision.inl>


void GameEngineTransform::CollisionScaleSetting() 
{
	CollisionDataObject.OBB.Extents = (Data.WorldScaling.ABS3DReturn() * 0.5f);
}
void GameEngineTransform::CollisionRotationSetting() {
	CollisionDataObject.OBB.Orientation = Data.WorldRotation.DegreeRotationToQuaternionReturn();
}
void GameEngineTransform::CollisionPositionSetting() {
	CollisionDataObject.OBB.Center = Data.WorldPosition;
}

void GameEngineTransform::CollisionDataSetting()
{
	CollisionScaleSetting();
	CollisionRotationSetting();
	CollisionPositionSetting();
}


bool GameEngineTransform::SphereToSphere(const GameEngineTransform& _Left, const GameEngineTransform& _Right)
{
	return _Left.CollisionDataObject.SPHERE.Intersects(_Right.CollisionDataObject.SPHERE);
}

bool GameEngineTransform::AABBToAABB(const GameEngineTransform& _Left, const GameEngineTransform& _Right)
{
	return _Left.CollisionDataObject.AABB.Intersects(_Right.CollisionDataObject.AABB);
}

bool GameEngineTransform::OBBToOBB(const GameEngineTransform& _Left, const GameEngineTransform& _Right)
{
	return _Left.CollisionDataObject.OBB.Intersects(_Right.CollisionDataObject.OBB);
}

bool GameEngineTransform::Sphere2DToSphere2D(const GameEngineTransform& _Left, const GameEngineTransform& _Right) 
{
	DirectX::BoundingSphere LEFTOBB2D = _Left.CollisionDataObject.SPHERE;
	DirectX::BoundingSphere RIGHTOBB2D = _Right.CollisionDataObject.SPHERE;
	LEFTOBB2D.Center.z = 0.0f;
	RIGHTOBB2D.Center.z = 0.0f;
	return LEFTOBB2D.Intersects(RIGHTOBB2D);
}

bool GameEngineTransform::AABB2DToAABB2D(const GameEngineTransform& _Left, const GameEngineTransform& _Right) 
{
	DirectX::BoundingBox LEFTOBB2D = _Left.CollisionDataObject.AABB;
	DirectX::BoundingBox RIGHTOBB2D = _Right.CollisionDataObject.AABB;
	LEFTOBB2D.Center.z = 0.0f;
	RIGHTOBB2D.Center.z = 0.0f;
	return LEFTOBB2D.Intersects(RIGHTOBB2D);
}

bool GameEngineTransform::OBB2DToOBB2D(const GameEngineTransform& _Left, const GameEngineTransform& _Right) 
{
	DirectX::BoundingOrientedBox LEFTOBB2D = _Left.CollisionDataObject.OBB;
	DirectX::BoundingOrientedBox RIGHTOBB2D = _Right.CollisionDataObject.OBB;
	LEFTOBB2D.Center.z = 0.0f;
	RIGHTOBB2D.Center.z = 0.0f;
	return LEFTOBB2D.Intersects(RIGHTOBB2D);
}
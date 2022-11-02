#include "PreCompile.h"
#include "StaticMesh.h"

#include <GameEngineCore/GameEngineFBXRenderer.h>

StaticMesh::StaticMesh() 
	: mpFBXRenderer(nullptr)
	, mbPriorityInitialzed(true)
	, mbWithCollision(true)
{
}

StaticMesh::~StaticMesh() 
{
}

void StaticMesh::Start()
{
	mpFBXRenderer = CreateComponent<GameEngineFBXRenderer>();
}

void StaticMesh::Update(float _DeltaTime)
{
	if (false == mbPriorityInitialzed)
	{
		if (true == mbWithCollision)
		{
			mpCollider = CreateComponent<GameEngineCollision>();
			mpCollider->GetTransform().SetLocalScale(GetTransform().GetLocalScale());
			mpCollider->ChangeOrder(OBJECTORDER::StaticMesh);
		}
		
		mbPriorityInitialzed = true;
	}
}


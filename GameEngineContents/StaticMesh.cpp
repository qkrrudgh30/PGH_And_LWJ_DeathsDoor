#include "PreCompile.h"
#include "StaticMesh.h"

#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

StaticMesh::StaticMesh() 
	: mpFBXStaticRenderer(nullptr)
	, mbPriorityInitialzed(true)
	, mbWithCollision(true)
{
}

StaticMesh::~StaticMesh() 
{
}

void StaticMesh::Start()
{
	mpFBXStaticRenderer = CreateComponent<GameEngineFBXStaticRenderer>();
	mpCollider = CreateComponent<GameEngineCollision>();
	mpCollider->ChangeOrder(OBJECTORDER::StaticMesh);
}

void StaticMesh::Update(float _DeltaTime)
{
	if (false == mbPriorityInitialzed)
	{
		if (true == mbWithCollision)
		{
			
			// mpCollider->GetTransform().SetLocalScale(GetTransform().GetLocalScale());
			
		}
		
		mbPriorityInitialzed = true;
	}
}


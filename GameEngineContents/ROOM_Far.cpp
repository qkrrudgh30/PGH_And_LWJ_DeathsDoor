#include "PreCompile.h"
#include "ROOM_Far.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>

ROOM_Far::ROOM_Far()
	: ResultColor()
{
}

ROOM_Far::~ROOM_Far()
{
}

void ROOM_Far::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f };
	GameEngineFBXStaticRenderer* Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
	Renderer->GetTransform().SetLocalRotation({ 0.f,45.f,0.f });
	// Renderer->SetFBXMesh("ROOM_Far.fbx", "Texture");
	for (int i = 0; i < 5; ++i)
	{
		if (3 == i)
		{
			// Renderer->SetFBXMesh("ROOM_Far.fbx", "Color", i);
			// Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLUE);
			continue;
		}
		Renderer->SetFBXMesh("ROOM_Far.fbx", "Texture", i);
	}

}

void ROOM_Far::Update(float _DeltaTime)
{

}


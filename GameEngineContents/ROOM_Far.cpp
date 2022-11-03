#include "PreCompile.h"
#include "ROOM_Far.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>

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
	GameEngineFBXRenderer* Renderer = CreateComponent<GameEngineFBXRenderer>();


#pragma region ROOM_Enter (1).FBX


	for (int i = 0; i < 409; ++i)
	{
		if (62 == i)
		{
			Renderer->SetFBXMesh("ROOM_Far.fbx", "Color", i);

			Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
			continue;
		}

		Renderer->SetFBXMesh("ROOM_Far.fbx", "Texture", i);

	}



#pragma endregion

#pragma region crow_player (fbx)



#pragma endregion



}

void ROOM_Far::Update(float _DeltaTime)
{

}


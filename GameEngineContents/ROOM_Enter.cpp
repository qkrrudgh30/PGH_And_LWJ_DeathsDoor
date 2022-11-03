

#include "PreCompile.h"
#include "ROOM_Enter.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

ROOM_Enter::ROOM_Enter()
	: ResultColor()
{
}

ROOM_Enter::~ROOM_Enter()
{
}

void ROOM_Enter::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f };
	GameEngineFBXRenderer* Renderer = CreateComponent<GameEngineFBXRenderer>();


#pragma region ROOM_Enter (1).FBX


	for (int i = 0; i < 409; ++i)
	{
		if (62 == i)
		{
			Renderer->SetFBXMesh("ROOM_Enter.fbx", "Color", i);

			Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
			continue;
		}

		Renderer->SetFBXMesh("ROOM_Enter.fbx", "Texture", i);

	}



#pragma endregion

#pragma region crow_player (fbx)



#pragma endregion



}

void ROOM_Enter::Update(float _DeltaTime)
{

}


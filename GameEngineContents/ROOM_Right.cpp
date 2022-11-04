

#include "PreCompile.h"
#include "ROOM_Right.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

ROOM_Right::ROOM_Right()
	: ResultColor()
{
}

ROOM_Right::~ROOM_Right()
{
}

void ROOM_Right::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f };
	GameEngineFBXStaticRenderer* Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->SetFBXMesh("ROOM_Right.fbx", "Texture");

#pragma region ROOM_Enter (1).FBX


	/*for (int i = 0; i < 409; ++i)
	{
		if (62 == i)
		{
			Renderer->SetFBXMesh("ROOM_Right.fbx", "Color", i);

			Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
			continue;
		}

		Renderer->SetFBXMesh("ROOM_Right.fbx", "Texture", i);

	}*/



#pragma endregion

#pragma region crow_player (fbx)



#pragma endregion



}

void ROOM_Right::Update(float _DeltaTime)
{

}


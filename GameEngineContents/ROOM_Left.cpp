

#include "PreCompile.h"
#include "ROOM_Left.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

ROOM_Left::ROOM_Left()
	: ResultColor()
{
}

ROOM_Left::~ROOM_Left()
{
}

void ROOM_Left::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f };
	GameEngineFBXStaticRenderer* Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->GetTransform().SetLocalScale(float4{ 0.5f, 0.5f, 0.5f });
	Renderer->SetFBXMesh("ROOM_Left.fbx", "Texture");

#pragma region ROOM_Left (1).FBX


	/*for (int i = 0; i < 409; ++i)
	{
		if (62 == i)
		{
			Renderer->SetFBXMesh("ROOM_Left.fbx", "Color", i);

			Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
			continue;
		}

		Renderer->SetFBXMesh("ROOM_Left.fbx", "Texture", i);

	}*/



#pragma endregion

#pragma region crow_player (fbx)



#pragma endregion



}

void ROOM_Left::Update(float _DeltaTime)
{

}


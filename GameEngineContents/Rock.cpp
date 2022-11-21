

#include "PreCompile.h"
#include "Hall.h"
#include <GameEngineCore/GameEngineFBXStaticRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

Hall::Hall()
	: ResultColor()
{
}

Hall::~Hall()
{
}

void Hall::Start()
{
	GameEngineTransformBase* aAAAAA = dynamic_cast<GameEngineTransformBase*>(this);

	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f };
	std::shared_ptr < GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	

#pragma region ROOM_Enter (1).FBX


	 for (int i = 0; i < 409; ++i)
	 {
	 	if (62 == i)
	 	{
	 		Renderer->SetFBXMesh("Hall.fbx", "Color", i);
	 		
	 		Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
	 		continue;
	 	}
	 
	 	Renderer->SetFBXMesh("Hall.fbx", "Texture", i);
	 
	 }

	

#pragma endregion

#pragma region crow_player (fbx)

	

#pragma endregion



}

void Hall::Update(float _DeltaTime)
{

}


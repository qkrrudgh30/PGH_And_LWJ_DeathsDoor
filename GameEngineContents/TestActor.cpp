#include "PreCompile.h"
#include "TestActor.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>
//#include "GameEngineCore/GameEngineDefaultRenderer.h"

TestActor::TestActor()
	: ResultColor()
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	ResultColor = float4{ 1.f, 1.f, 0.f, 1.f};
	GameEngineFBXRenderer* Renderer = CreateComponent<GameEngineFBXRenderer>();
	// Renderer->GetTransform().SetLocalRotate(float4{20.f, -20.f, 180.f});
	Renderer->GetTransform().SetLocalPosition(float4{0.f, 0.f, 0.f});
	Renderer->GetTransform().SetLocalScale(float4{1.f, 1.f, 1.f});
	
	// Renderer->SetFBXMesh("Hall.fbx", "Texture"); // 62

#pragma region ROOM_Enter (1).FBX


	 for (int i = 0; i < emcROOM_Enter_1; ++i)
	 {
		// Renderer->SetFBXMesh("ROOM_Enter (1).FBX", "Color", i);
		// Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::RED);
	 	
		if (6 == i || 3 == i) 
	 	{ 
	 		Renderer->SetFBXMesh("ROOM_Enter (1).fbx", "Color", i);
	 		Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
	 		continue; 
	 	}
	 
	 	Renderer->SetFBXMesh("ROOM_Enter (1).fbx", "Texture", i);
	 
	 }

	//GameEngineFBXRenderer* RendererWithoutMaterial1 = CreateComponent<GameEngineFBXRenderer>();
	//RendererWithoutMaterial1->SetFBXMesh("ROOM_Enter (1).FBX", "Color", 6);
	//RendererWithoutMaterial1->GetAllRenderUnit()[6][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::RED); // 6번의 경우, 날릭
	//

#pragma endregion

#pragma region crow_player (fbx)
	
	/*for (int i = 2; i < 17; ++i)
	{
		

		if ((2 <= i && i <= 9) ||  i == 13 ) { continue; }

		if (14 == i || 15 == i)
		{
			Renderer->SetFBXMesh("crow_player (fbx).FBX", "Color", i);
			Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::RED);
			continue;
		}

		Renderer->SetFBXMesh("crow_player (fbx).FBX", "Texture", i);
	}*/
	
#pragma endregion



}

void TestActor::Update(float _DeltaTime)
{
	// Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);
}


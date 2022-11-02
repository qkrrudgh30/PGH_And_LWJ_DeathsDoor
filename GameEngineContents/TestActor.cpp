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
	// GameEngineFBXRenderer* Renderer2 = CreateComponent<GameEngineFBXRenderer>();
	// GameEngineFBXRenderer* Renderer3 = CreateComponent<GameEngineFBXRenderer>();
	// Renderer->GetTransform().SetLocalRotate(float4{20.f, -20.f, 180.f});
	// Renderer->GetTransform().SetLocalPosition(float4{0.f, 0.f, 0.f});
	// Renderer->GetTransform().SetLocalScale(float4{1.f, 1.f, 1.f});
	
	// Renderer->SetFBXMesh("ROOM_Elevator.fbx", "Texture"); // 62
	// Renderer1->SetFBXMesh("ROOM_MainHall.fbx", "Texture", 0, 1);
	// Renderer2->SetFBXMesh("ROOM_MainHall.fbx", "Texture", 0, 1);
	// Renderer3->SetFBXMesh("ROOM_MainHall.fbx", "Color", 0, 2);
	// Renderer3->GetAllRenderUnit()[0][2].ShaderResources.SetConstantBufferLink("ResultColor", float4::YELLOW);

#pragma region ROOM_Enter (1).FBX
	/*for (int i = 0; i < 1; ++i)
	{
		if (0 == i)
		{
			Renderer->SetFBXMesh("Lantern.fbx", "Color", 0, 2);
			Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::YELLOW);
		}
		else
		{
			Renderer->SetFBXMesh("Lantern.fbx", "Texture", i);
		}
	}*/

	 for (int i = 0; i < emcROOM_Enter_1; ++i)
	 {
		if (1 == i) 
	 	{ 
	 		Renderer->SetFBXMesh("ROOM_Enter.fbx", "Color", i);
	 		Renderer->GetAllRenderUnit()[i][0].ShaderResources.SetConstantBufferLink("ResultColor", float4::BLACK);
	 		continue; 
	 	}
	 
	 	Renderer->SetFBXMesh("ROOM_Enter.fbx", "Texture", i);
	 
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


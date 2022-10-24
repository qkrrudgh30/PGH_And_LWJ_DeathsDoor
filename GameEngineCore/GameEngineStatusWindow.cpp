#include "PreCompile.h"
#include "GameEngineStatusWindow.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineCameraActor.h"
#include "GEngine.h"

std::map<std::string, GameEngineRenderTarget*> GameEngineStatusWindow::DebugRenderTarget;

void GameEngineImageShotWindow::RenderTextureSetting(ImTextureID _RenderTexture, ImVec2 _Size) 
{
	RenderTexture = _RenderTexture;
	Size = _Size;
}

void GameEngineImageShotWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::ImageButton(RenderTexture, { Size.x, Size.y }))
	{
		Off();
	}

}


GameEngineStatusWindow::GameEngineStatusWindow() 
{
}

GameEngineStatusWindow::~GameEngineStatusWindow() 
{
}


void GameEngineStatusWindow::Initialize(class GameEngineLevel* _Level)
{

}

void GameEngineStatusWindow::AddDebugRenderTarget(const std::string& _DebugName, GameEngineRenderTarget* _RenderTarget)
{
	if (DebugRenderTarget.end() != DebugRenderTarget.find(_DebugName))
	{
		MsgBoxAssert("이미 존재하는 디버그 랜더타겟입니다.");
	}

	DebugRenderTarget.insert(std::make_pair(_DebugName, _RenderTarget));
}

void GameEngineStatusWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime) 
{
	int FPS = static_cast<int>(1.0f / _DeltaTime);
	// printf 형식인데 안씀.

	std::string Name = "FPS : " + std::to_string(GameEngineTime::GetFPS());
	ImGui::Text(Name.c_str());

	if (true == ImGui::Button("Thread깨우기"))
	{
		for (size_t i = 0; i < 100; i++)
		{
			// GameEngineTexture::Load

			//GameEngineCore::EngineThreadPool.Work(
			//	[]
			//	{
			//		GameEngineDebug::OutPutString("쓰레드입니다.");
			//	}
			//);
		}
	}

	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}

	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		// ;
		GEngine::GetCurrentLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::Text("Level Select");
	for (std::pair<std::string, GameEngineLevel*> Pair : GameEngineCore::AllLevels)
	{
		if (true == ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}

		ImGui::SameLine();
	}

	ImGui::NewLine();
	std::string AllRenderTarget = "AllRenderTarget";
	ImGui::Text(AllRenderTarget.c_str());

	for (std::pair<std::string, GameEngineRenderTarget*> RenderTargetPair : DebugRenderTarget)
	{
		// ImGui::Text(RenderTarget.first.c_str());

		if (true == ImGui::TreeNodeEx(RenderTargetPair.first.c_str(), 0))
		{
			GameEngineRenderTarget* RenderTarget = RenderTargetPair.second;

			for (ID3D11ShaderResourceView* _View : RenderTarget->ShaderResourceViews)
			{
				float4 Scale = GameEngineWindow::GetScale() * 0.2f;

				if (true == ImGui::ImageButton(static_cast<ImTextureID>(_View), { Scale.x, Scale.y }))
				{
					GameEngineImageShotWindow* NewWindow = GameEngineGUI::CreateGUIWindow<GameEngineImageShotWindow>("ImageShot", nullptr);
					NewWindow->RenderTextureSetting(static_cast<ImTextureID>(_View), { GameEngineWindow::GetScale().x ,GameEngineWindow::GetScale().y } );
				}
			}

			ImGui::TreePop();
		}
	}

	DebugRenderTarget.clear();

}
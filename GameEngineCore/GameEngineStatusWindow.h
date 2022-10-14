#pragma once
#include "GameEngineGUI.h"

class GameEngineImageShotWindow : public GameEngineGUIWindow
{
public:
	ImTextureID RenderTexture;
	ImVec2 Size;

public:
	void RenderTextureSetting(ImTextureID RenderTexture, ImVec2 Size);

public:
	void Initialize(class GameEngineLevel* _Level) {}
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

// Ό³Έν :
class GameEngineStatusWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	GameEngineStatusWindow();
	~GameEngineStatusWindow();

	// delete Function
	GameEngineStatusWindow(const GameEngineStatusWindow& _Other) = delete;
	GameEngineStatusWindow(GameEngineStatusWindow&& _Other) noexcept = delete;
	GameEngineStatusWindow& operator=(const GameEngineStatusWindow& _Other) = delete;
	GameEngineStatusWindow& operator=(GameEngineStatusWindow&& _Other) noexcept = delete;

	static void AddDebugRenderTarget(const std::string& _DebugName, GameEngineRenderTarget* _RenderTarget);

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	std::list<GameEngineImageShotWindow*> Window;

	static std::map<std::string, GameEngineRenderTarget*> DebugRenderTarget;
};


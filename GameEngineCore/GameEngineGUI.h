#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineString.h>

class GameEngineGUIWindow : public GameEngineNameObject, public GameEngineUpdateObject
{
	friend class GameEngineGUI;

	void Start() override {}
	void Update(float _DeltaTime) override { };


private:
	void Begin() 
	{
		std::string Name = GameEngineString::AnsiToUTF8Return(GetNameConstPtr());
		ImGui::Begin(Name.c_str(), &IsUpdateRef());
	}

	void End() 
	{
		ImGui::End();
	}

public:
	virtual void Initialize(class GameEngineLevel* _Level) = 0;
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;
};

// Ό³Έν :
class GameEngineCore;
class GameEngineLevel;
class GameEngineGUI
{
	friend GameEngineCore;

public:
	// constrcuter destructer
	GameEngineGUI();
	~GameEngineGUI();

	// delete Function
	GameEngineGUI(const GameEngineGUI& _Other) = delete;
	GameEngineGUI(GameEngineGUI&& _Other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _Other) = delete;
	GameEngineGUI& operator=(GameEngineGUI&& _Other) noexcept = delete;

	static void Initialize();
	static void GUIRender(GameEngineLevel* _Level, float _DeltaTime);

	template<typename GUIWindowType>
	static GUIWindowType* CreateGUIWindow(const std::string& _Name, GameEngineLevel* _Level)
	{
		GUIWindowType* Window = new GUIWindowType();
		GameEngineGUIWindow* InitWindow = Window;
		InitWindow->SetName(_Name);
		InitWindow->Initialize(_Level);
		Windows.push_back(Window);
		return Window;
	}

	static std::string OpenFileDlg(const std::string& _Title, const std::string& _StartPath);

	static std::string OpenFolderDlg(const std::string& _Title, const std::string& _StartPath);

protected:

private:
	static std::list<GameEngineGUIWindow*> Windows;

	static void GUIDestroy();
};


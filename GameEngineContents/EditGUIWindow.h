#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class EditGUIWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	EditGUIWindow();
	~EditGUIWindow();

	// delete Function
	EditGUIWindow(const EditGUIWindow& _Other) = delete;
	EditGUIWindow(EditGUIWindow&& _Other) noexcept = delete;
	EditGUIWindow& operator=(const EditGUIWindow& _Other) = delete;
	EditGUIWindow& operator=(EditGUIWindow&& _Other) noexcept = delete;

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

};


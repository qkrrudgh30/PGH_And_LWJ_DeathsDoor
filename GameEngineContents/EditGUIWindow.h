#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :

enum
{
	AnimatorPannel,
	StaticPannel,
	END,
};

struct EditItem
{
	
};

class EditLevel;
class GameEngineActor;
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

	void Save();
	void SaveTileData(const std::string& _strTitle);
	// void SaveTileData(const std::wstring& _strFilePath, const std::string& _strTitle);

	void Load();
	void LoadTileData(const std::string& _strFilePath);

	static std::vector<std::string>& GetLoadedFromAnimatorVector(void) { return m_vLoadedFromAnimator; }
	static std::vector<std::string>& GetLoadedFromStaticVector(void) { return m_vLoadedFromStatic; }

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	bool CheckChanges(int _iSelectedActor);

	// void CreateMultiple(int _XCount, int Y);

	GameEngineDirectory m_CurrentDirectory;
	GameEngineDirectory m_ProjectDirectory;
	static std::vector<std::string> m_vLoadedFromAnimator;
	static std::vector<std::string> m_vLoadedFromStatic;

	EditLevel* m_ptrEditLevel;
	std::vector<std::pair<std::string, class StaticMesh*>> m_vCreatedActors;

	static float s_farrScaleOnEditGUI[3];
	static float s_farrRotationOnEditGUI[3];
	static float s_farrPositionOnEditGUI[3];

};


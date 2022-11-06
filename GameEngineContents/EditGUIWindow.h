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

	void PrepareForSaving();
	void SaveData(const std::string& _strTitle);
	// void SaveTileData(const std::wstring& _strFilePath, const std::string& _strTitle);

	void PrepareForLoading();
	void LoadData(const std::string& _strFilePath);

	static std::set<std::string>& GetLoadedFromAnimatorSet(void) { return m_setLoadedFromAnimator; }
	static std::set<std::string>& GetLoadedFromStaticSet(void) { return m_setLoadedFromStatic; }

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	bool CheckChangesAboutCreature(int _iSelectedActor);
	bool CheckChangesAboutCurrStaticValue(int _iSelectedActor);

	// void CreateMultiple(int _XCount, int Y);

	GameEngineDirectory m_CurrentDirectory;
	GameEngineDirectory m_ProjectDirectory;
	static std::set<std::string> m_setLoadedFromAnimator;
	static std::set<std::string> m_setLoadedFromStatic;

	std::vector<std::pair<std::string, class StaticMesh*>> m_vCreatedActors;

	static float s_farrCurrScaleOnEditGUI[3];
	static float s_farrPrevScaleOnEditGUI[3];
	static float s_farrCurrRotationOnEditGUI[3];
	static float s_farrPrevRotationOnEditGUI[3];
	static float s_farrCurrPositionOnEditGUI[3];
	static float s_farrPrevPositionOnEditGUI[3];

	static float s_farrCurrColliderScaleOnEditGUI[3];
	static float s_farrCurrColliderRotationOnEditGUI[3];
	static float s_farrCurrColliderPositionOnEditGUI[3];



};


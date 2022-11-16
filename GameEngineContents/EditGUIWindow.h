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
	friend class ContentsLevel;

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
	static std::map<std::string, std::vector<std::pair<std::string, std::weak_ptr<class StaticMesh>>>>& GetCreatureMap(void) { return m_vCreatedActors; }

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	bool CheckChangesAboutCreature(size_t _uSelectedActor);
	bool CheckChangesAboutCurrStaticValue(size_t _uSelectedActor);
	bool CheckChangesAboutCreatureCollider(size_t _uSelectedActor);
	bool CheckChangesAboutCurrStaticValueCollider(size_t _uSelectedActor);

	// void CreateMultiple(int _XCount, int Y);

	static size_t uSelectedPannel;
	static size_t uSelectedObject;
	static size_t uSelectedActor;

	GameEngineDirectory m_ProjectDirectory;
	static std::set<std::string> m_setLoadedFromAnimator;
	static std::set<std::string> m_setLoadedFromStatic;

	std::string mstrCurrLevelName;
	std::string mstrNextLevelName;
	static std::map<std::string, std::vector<std::pair<std::string, std::weak_ptr<class StaticMesh>>>> m_vCreatedActors;

	static float s_farrCurrScaleOnEditGUI[3];
	static float s_farrPrevScaleOnEditGUI[3];
	static float s_farrCurrRotationOnEditGUI[3];
	static float s_farrPrevRotationOnEditGUI[3];
	static float s_farrCurrPositionOnEditGUI[3];
	static float s_farrPrevPositionOnEditGUI[3];

	static float s_farrCurrColliderScaleOnEditGUI[3];
	static float s_farrPrevColliderScaleOnEditGUI[3];
	static float s_farrCurrColliderRotationOnEditGUI[3];
	static float s_farrPrevColliderRotationOnEditGUI[3];
	static float s_farrCurrColliderPositionOnEditGUI[3];
	static float s_farrPrevColliderPositionOnEditGUI[3];



};


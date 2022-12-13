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

	void SavePostEffectInfo();
	static void LoadPostEffectInfo();
	static void OffStartingLevel() { s_mbStartingLevel = false; }

	void PrepareForLoading();
	void LoadData(const std::string& _strFilePath);

	static std::set<std::string>& GetLoadedFromAnimatorSet(void) { return m_setLoadedFromAnimator; }
	static std::set<std::string>& GetLoadedFromStaticSet(void) { return m_setLoadedFromStatic; }
	static std::map<std::string, std::vector<std::pair<std::string, std::weak_ptr<class StaticMesh>>>>& GetCreatureMap(void) { return m_vCreatedActors; }

	void SaveLightData();
	static void LoadLightData();

	static bool IsLightOn() { return s_bOnOffLight; }

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	bool CheckChangesAboutCreature(size_t _uSelectedActor);
	bool CheckChangesAboutCurrStaticValue(size_t _uSelectedActor);
	bool CheckChangesAboutCreatureCollider(size_t _uSelectedActor);
	bool CheckChangesAboutCurrStaticValueCollider(size_t _uSelectedActor);

	bool CheckChangesAboutLight();
	bool CheckChangesAboutCurrLightStaticValue();

	// void CreateMultiple(int _XCount, int Y);

	static size_t uSelectedPannel;
	static size_t uSelectedObject;
	static size_t uSelectedActor;

	static GameEngineDirectory m_ProjectDirectory;
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

	static float s_farrCurrLightScaleOnEditGUI[3];
	static float s_farrPrevLightScaleOnEditGUI[3];
	static float s_farrCurrLightRotationOnEditGUI[3];
	static float s_farrPrevLightRotationOnEditGUI[3];
	static float s_farrCurrLightPositionOnEditGUI[3];
	static float s_farrPrevLightPositionOnEditGUI[3];
	static float s_farrCurrLightColorOnEditGUI[3];
	static float s_farrPrevLightColorOnEditGUI[3];

	static bool s_bAnyChanges;
	static bool s_bOnOffBlur;
	static unsigned int s_uOnOffBlur;
	static int s_iCurrAppliedArea;
	static float s_fCurrIntence;

	static bool s_bAnyChangesForBloom;
	static bool s_bOnOffBloom;
	static unsigned int s_uOnOffBloom;
	static int s_iAppliedAreaForBloom;
	static float s_fLuminanceForBloom;
	static float s_fIntenceForBloom;

	static bool s_bAnyChangesForLight;
	static bool s_bOnOffLight;
	static unsigned int s_uOnOffLight;
	static float s_fDiffuseLightIntensity;
	static float s_fAmbientLightIntensity;
	static float s_fSpecularLightIntensity;
	static float s_fSpecularLightPower;

	static bool s_mbStartingLevel;
};


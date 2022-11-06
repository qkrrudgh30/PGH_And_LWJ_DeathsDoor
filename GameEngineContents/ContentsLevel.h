#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum
{
	eAnimatorDir,
	eStaticDir,
	eEndDir
};

// Ό³Έν :
class GameEngineDirectory;
class ContentsLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ContentsLevel();
	~ContentsLevel();

	// delete Function
	ContentsLevel(const ContentsLevel& _Other) = delete;
	ContentsLevel(ContentsLevel&& _Other) noexcept = delete;
	ContentsLevel& operator=(const ContentsLevel& _Other) = delete;
	ContentsLevel& operator=(ContentsLevel&& _Other) noexcept = delete;

	static std::string mstrNextLevelName;
	static std::string mstrPrevLevelName;
	static std::map<std::string, bool> mmapPrimitiveInitialized;

protected:
	void DirectPathAt(const std::string& _strFolderName);
	void LoadFBXFiles();

	void LoadCreaturesFromFile(const std::string& _strFolderName);

	static std::atomic<unsigned int> muFBXLoadedCount;
	std::vector<GameEngineDirectory> mvecDirectories;
	bool mbPrimitiveInitialized;
	class LoadingUI* mpLoadingUI;

private:
	void LoadFBXMesiesOfAnimator();
	void LoadFBXMesiesOfStatic();
	void LoadAnimationsOfAnimator();
	std::vector<std::string> mstrvecAnimatorMeshFileNames;
	std::vector<std::string> mstrvecAnimatorMeshFileNamesForEdit;
	std::vector<std::string> mstrvecStaticMeshFileNames;
	std::vector<std::string> mstrvecStaticMeshFileNamesForEdit;
	std::vector<std::string> mstrvecAnimationFileNames;

};


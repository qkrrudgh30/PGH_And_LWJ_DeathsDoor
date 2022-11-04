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
	

protected:
	void DirectPathAt(const std::string& _strFolderName);
	void LoadFBXFiles();
	void LoadTextureInAnimator();
	void LoadTextureInStatic();

	void LoadCreaturesFromFile(const std::string& _strFolderName);

	std::vector<GameEngineDirectory> mvecDirectories;
	static std::atomic<int> muFBXFolderCount;
	bool mbPrimitiveInitialized;

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


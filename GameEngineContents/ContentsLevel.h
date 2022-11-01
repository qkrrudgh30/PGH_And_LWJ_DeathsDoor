#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum
{
	eAnimatorDir,
	eStaticDir,
	eEndDir
};

// 설명 :
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
	void LoadFBXFiles();			// 클라 분들이 이 함수만 호출하면 알아서 해당 레벨의 모든 FBXFile들이 로드 되게끔함.
									// 이 함수 내에서 세 가지 로드가 진행되고, 각 단계마다 폴더 수를 체크 후 폴더 수 / 스레드 개수로 나눔.
									// 
	void LoadTextureInAnimator();
	void LoadTextureInStatic();

	std::vector<GameEngineDirectory> mvecDirectories;
	static std::atomic<int> muFBXFolderCount;
	// bool mb

private:
	void LoadFBXMesiesOfAnimator();
	void LoadFBXMesiesOfStatic();
	void LoadAnimationsOfAnimator();
	std::vector<std::string> mstrvecAnimatorMeshFileNames;
	std::vector<std::string> mstrvecStaticMeshFileNames;
	std::vector<std::string> mstrvecAnimationFileNames;

};

